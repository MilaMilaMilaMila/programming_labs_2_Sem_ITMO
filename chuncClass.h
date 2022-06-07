#pragma once
#include <vector>
#include <deque>
#include <iostream>
#include <array>
#include <algorithm>
#include <set>
#include <list>
#include <map>
#include <utility>
#include <unordered_map>
#include <unordered_set>

namespace chunkTools {
    // считаем сколько нам нужно доп мусорных байт для выравнивание до кратности alignment - в данном случае == HEADER_SIZE,
    // аргументы: адрес на последний байт без выравнивания, кратность выравнивания
    std::size_t countBytesForAlignment(std::size_t not_aligned_address, std::size_t alignment) {

        if ((alignment != 0u) && (not_aligned_address % alignment != 0u)) { // если кратность не 0 и данные нуждаются
                                                                            // в выравнивании...

            const std::size_t multiplier = (not_aligned_address / alignment) + 1u; // сколько полных сегментов блока
                                                                                   // размера alignment нужно
            const std::size_t aligned_address = multiplier * alignment; // выровненный адресс
            return aligned_address - not_aligned_address; // разность адресов -> количество мусорных байтов
        }

        return 0u; // если выравнивания не требуется - количество мусорных байт == 0
    }

    // сейчас выравнивнивание идет на 4 байта - размер заголовка и разбиения участка памяти на блоки
    // но этот размер можно изменить - это параметр. Ничего не сломается

    // шаблонный класс "участок памяти"
    // шаблонизируется по размеру участков(chunks) CHUNK_SIZE
    template<std::size_t CHUNK_SIZE>
    class Chunk {

        static constexpr std::size_t HEADER_SIZE = 4u; // размер заголовка - параметризуется
        using HEADER_TYPE = std::uint32_t *; // тоже параметризуется
        using SEGMENT_SIZE = std::uint32_t;  // тоже параметризуется
        static_assert(CHUNK_SIZE % HEADER_SIZE == 0, "CHUNK_SIZE must be multiple of the HEADER_SIZE"); // детали реализации
                                                                                                        // чтобы дегче было делать расчеты
        static_assert(CHUNK_SIZE > HEADER_SIZE, "CHUNK_SIZE must be more than HEADER_SIZE"); // размер участка не может быть меньше заголовка
                                                                                              // + хоть какое-то место под данные
    public:
        std::vector<std::uint8_t *> m_blocks; // все сегменты - вся память данного участка по 1 байту шаг
        std::set<HEADER_TYPE> m_free_blocks; // адреса заголовков свободных блоков
        std::uint32_t *m_max_block; // адрес свободного блока маскимального размера

    public:
        // конструктор
        Chunk() {
            m_blocks.resize(CHUNK_SIZE); // создаем стартовый блок максимального размера CHUNK_SIZE

            // reinterpret_cast — непосредственное указание компилятору. Применяется только в случае
            // полной уверенности программиста в собственных действиях. Не снимает константность и volatile.
            // применяется для приведения указателя к указателю, указателя к целому и наоборот.

            // m_blocks.data() - указатель на первый элемент
            // init_header - указатель на ячейки памяти, где хранится размер блока для этого заголовка
            auto *init_header = reinterpret_cast<HEADER_TYPE>(m_blocks.data()); // кастим uint8_t -> uint32_t
                                                                                // четыре штуки uint8 за шаг обрабатывать

            // кладем по указателю размер блока (сейчас это вечсь участок памяти)
            *init_header = CHUNK_SIZE - HEADER_SIZE;

            m_max_block = init_header; // сейчас максимальный свободный блок - это первый и единственный
            m_free_blocks.insert(init_header); // добавляем адрес заголовока на свободный полный блок в set адресов на
                                               // заголовки свободных блоков
        }

        // проверяем находится ли ячейка по данному адресу в этом участке памяти
        // аргументы: адрес на ячейку памяти
        bool isInside(const std::uint8_t *address) const noexcept {

            // находим граничные адреса
            const auto *start_chunk_address = reinterpret_cast<const std::uint8_t *>(m_blocks.data()); // кастим на всякий случай
            const std::uint8_t *end_chunk_address = start_chunk_address + CHUNK_SIZE;
            // смотрим внутри ли адресс
            return (start_chunk_address <= address) && (address <= end_chunk_address);
        }

        // пробуем найти и отдать память
        // аргументы: количество байт для выделения
        std::uint8_t *tryReserveBlock(std::size_t allocation_size) {

            // адрес последнего байта памяти без выравнивания, если бы мы заняли эту память
            const std::size_t not_aligned_address = reinterpret_cast<std::size_t>(m_max_block) + allocation_size;

            // количество мусорных байтов для выравнивания
            const std::size_t alignment_padding = countBytesForAlignment(not_aligned_address, HEADER_SIZE);

            // количество сегментов в блоке памяти на выделение (кастим чтобы получить количество сегментов)
            const auto allocation_size_with_alignment = static_cast<SEGMENT_SIZE>(allocation_size + alignment_padding);

            // проверяем, хватит ли нам хотя бы максимального блока И есть ли вообще свободные блоки
            if ((!m_max_block) || (allocation_size_with_alignment > *m_max_block))
            {
                return nullptr;
            }

            // ищем минимальный подходящий по размеру блок(итератор на него), чтобы оставлять свободные блоки максимальных размеров
            const auto min_it = std::min_element(m_free_blocks.cbegin(), m_free_blocks.cend(),
                                                 [allocation_size_with_alignment](const SEGMENT_SIZE *lhs,   // просто лямбда функция,
                                                                                  const SEGMENT_SIZE *rhs) { // чтобы искать Min, но >= alloc_size
                                                     if (*rhs < allocation_size_with_alignment) {
                                                         return true;
                                                     }

                                                     return (*lhs < *rhs) && (*lhs >= allocation_size_with_alignment);
                                                 });

            //assert(min_it != m_free_blocks.cend() && "Internal logic error with reserve block, something wrong in implementation...");
            //assert(**min_it >= allocation_size_with_alignment && "Internal logic error with reserve block, something wrong in implementation...");

            std::uint32_t *header_address = *min_it; // берем адрес заголовка(разыменовывая итератор)

            // потенциальный заголовок нового блока
            // кастим к 1 байту, чтобы в байтиках посчитать, потом кастим к 4 байтам, чтобы взять сколько сегментов перешагнули
            auto *new_header_address =
                    reinterpret_cast<HEADER_TYPE>(reinterpret_cast<std::uint8_t *>(header_address) + HEADER_SIZE +
                                                      allocation_size_with_alignment);

            // проверяем, есть ли новый блок памяти, который мы отщипнули в списке свободных блоков
            // если нет, то...
            if (m_free_blocks.find(new_header_address) == m_free_blocks.cend())
            {
                const SEGMENT_SIZE old_block_size = *header_address; // старый свободный размер с заголовком
                const SEGMENT_SIZE difference = old_block_size - HEADER_SIZE; // старый свободный размер без заголовка (чистый)
                if (difference >= allocation_size_with_alignment) // есть ли место для новго блока
                {
                    const SEGMENT_SIZE new_block_size = difference - allocation_size_with_alignment; // считаем размер нового блока
                    *new_header_address = new_block_size; // записываем размер нового свободного блока
                    m_free_blocks.insert(new_header_address); // добавляем новый блок в список свободных блоков
                }
            }

            m_free_blocks.erase(header_address); // удаляем из свободных блоков блок, из которого отдали память

            *header_address = static_cast<SEGMENT_SIZE>(allocation_size); // записали размер отданой памяти

            // если мы отдали максимальный свободный блок, нужно найти новый блок максимального размера
            if (header_address == m_max_block)
            {
                // ищем новый блок максимального размера из свободных
                const auto max_it = std::max_element(m_free_blocks.cbegin(), m_free_blocks.cend(),
                                                     [](const SEGMENT_SIZE *lhs, const SEGMENT_SIZE *rhs) { // кастим до 4 байт
                                                         return (*lhs) < (*rhs);
                                                     });

                // либо назначем новый адрес, либо наш участок памяти пуст и max_block адрес это nullptr
                m_max_block = (max_it != m_free_blocks.cend()) ? (*max_it) : (nullptr);
            }

            // возвращаем адрес байтика, с которого можно записывать данные
            return reinterpret_cast<std::uint8_t *>(header_address) + HEADER_SIZE;
        }

        // освобождаем блок от данных
        // аргументы: указатель на блок
        void releaseBlock(std::uint8_t *block_ptr) {

            // приходим к заголовку блока
            std::uint8_t *header_address = block_ptr - HEADER_SIZE;

            // получаем размер блока
            const std::uint32_t size_relized_block = *header_address;

            // если можем, обновляем максимальный свободный блок
            if ((!m_max_block) || (size_relized_block > *m_max_block))
            {
                m_max_block = reinterpret_cast<HEADER_TYPE>(header_address);
            }

            // добавляем блок в список свободных
            m_free_blocks.insert(reinterpret_cast<HEADER_TYPE>(header_address));

            // получаем итератор на освобожденный блок в списке
            auto forward_it = m_free_blocks.find(reinterpret_cast<HEADER_TYPE>(header_address));

            // пытаемся объединть с соседним правым свободными блоком, если они соседние
            auto backward_it = defragment(forward_it, m_free_blocks.end()); // если объединили, то у нас новый итератор
            // пытаемся объединть с соседним левым свободными блоком, если они соседние
            defragment(std::make_reverse_iterator(backward_it), m_free_blocks.rend());
        }

    private:

        template<typename DstIterator, typename SrcIterator>
        constexpr DstIterator getIterator(SrcIterator it) const {

            using iterator = std::set<HEADER_TYPE>::iterator;
            using reverse_iterator = std::set<HEADER_TYPE>::reverse_iterator;
            if constexpr ((std::is_same_v<SrcIterator, iterator>) && (std::is_same_v<DstIterator, reverse_iterator>)) {

                return std::make_reverse_iterator(it);

            } else if constexpr ((std::is_same_v<SrcIterator, reverse_iterator>) &&
                                 (std::is_same_v<DstIterator, iterator>)) {
                return it.base();

            } else {
                return it;
            }
        }

        // объединяем два свободных блока, если они соседние
        template<typename Iterator>
        Iterator defragment(Iterator start, Iterator end) {

            auto fixed_it = start++; // итератор на освобожденный блок

            std::uint32_t *prev_header_address = *fixed_it; // адрес на освобожденный блок

            for (auto it = start; (fixed_it != end) && (it != end);) {

                std::uint32_t *current_header_address = *it; // адрес на рассматриваемый блок

                const std::uint32_t prev_block_size = *prev_header_address; // размер освобожденного блока
                const std::uint32_t *available_current_block_address =
                        reinterpret_cast<HEADER_TYPE>(reinterpret_cast<std::uint8_t *>(prev_header_address) +
                                                          HEADER_SIZE + prev_block_size); // размер осовбожденного блока с заголовком
                // если освобожденный блок с текущим рассматриваемым соседние, то ...
                if (available_current_block_address == current_header_address) {

                    const std::uint32_t current_block_size = *current_header_address; // размер рассматриваемого блока
                    const std::uint32_t new_prev_block_size = prev_block_size + HEADER_SIZE + current_block_size; // размер объединения

                    *prev_header_address = new_prev_block_size; // обновили размер освобожденного блока

                    // обновили максимальный свободный блок, если нужно
                    if (new_prev_block_size > *m_max_block) {
                        m_max_block = reinterpret_cast<std::uint32_t *>(prev_header_address);
                    }

                    // удаляем слитый блок по итератору
                    auto it_for_delete = getIterator<std::set<HEADER_TYPE>::iterator>(it); // находим корректный итератор
                    it = getIterator<Iterator>(m_free_blocks.erase(it_for_delete));

                } else {
                    return fixed_it;
                }
            }

            return fixed_it;
        }

    };

}


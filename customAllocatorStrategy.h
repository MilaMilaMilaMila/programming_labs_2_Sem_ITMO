#pragma once
#include "chuncClass.h"
#include <exception>

const std::size_t CHUNK_SIZE_PARAMETER = 32'768u; // параметр

template<std::size_t CHUNK_SIZE = CHUNK_SIZE_PARAMETER>
class CustomAllocationStrategy {

    static_assert(CHUNK_SIZE != 0u, "Chunk size must be more, than zero");
    static_assert(CHUNK_SIZE <= std::numeric_limits<std::uint32_t>::max(),
                  "Chunk size must be less or equal max value of the uint32_t");

private:
    std::deque<chunkTools::Chunk<CHUNK_SIZE>> m_chunks{1u}; // задаем какойто размер

public:
    // выдаем память
    void *allocate(std::size_t size) {

        //assert(size < CHUNK_SIZE && "Incorrect chunk size for future usage");

        if (size == 0u) {
            return nullptr;
        }

        // ищем участок, где есть подходящий по размеру блок
        for (auto &chunk: m_chunks) {

            // пробуем забрать свободную память
            // получаем адрес на блок
            void *allocated_block = chunk.tryReserveBlock(size);
            if (allocated_block) // если адрес не nullptr то мы отдаем адрес на память
            {
                return allocated_block;
            }
        }

        try
        {
            throw std::runtime_error("There is not free memory");
        }
        catch (const std::runtime_error &err) {
            std::cerr << err.what() << std::endl;
        }
        return nullptr;
    }

    // освобождаем память
    void deallocate(void *memory_ptr, std::size_t size) {
        // если адрес nullptr или нужно освободить 0 элементов, то ничего не делаем
        if ((!memory_ptr) || (size == 0u)) {
            return;
        }

        // адрес на байтик должен быть следующим после заголовка байтиком
        auto *deallocation_ptr = static_cast<std::uint8_t *>(memory_ptr);

        // ищем в каком участке памяти этот адрес
        for (auto &chunk: m_chunks) {

            // если находим, то освобождаем
            if (chunk.isInside(deallocation_ptr)) {
                chunk.releaseBlock(deallocation_ptr);
            }
        }
    }
};

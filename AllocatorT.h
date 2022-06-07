#pragma once
#include "customAllocatorStrategy.h"

template<typename T, class AllocationStrategy>
class Allocator {

    static_assert(!std::is_same_v<T, void>, "Type of the allocator can not be void");

private:
    AllocationStrategy *m_allocation_strategy = nullptr;

public:
    using value_type = T;

    template<typename U, class AllocStrategy>
    friend class Allocator;

    template<typename U>
    struct rebind
    {
        using other = Allocator<U, AllocationStrategy>;
    };

public:

    // конструктор
    Allocator() = default; // стратегии нет

    // конструктор
    explicit Allocator(AllocationStrategy &strategy) noexcept // задаем стратегию напрямую
            : m_allocation_strategy(&strategy) {}

    // конструктор копирования
    Allocator(const Allocator &other) noexcept // задаем стратегию от другого аллокатора
            : m_allocation_strategy(other.m_allocation_strategy) {}

    // конструктор от аллокатора другого типа данных
    template<typename U>
    Allocator(const Allocator<U, AllocationStrategy> &other) noexcept
            : m_allocation_strategy(other.m_allocation_strategy) {}

    // выдаем память
    value_type *allocate(std::size_t count_objects) {
        //assert(m_allocation_strategy && "Not initialized allocation strategy");
        return static_cast<T *>(m_allocation_strategy->allocate(count_objects * sizeof(T)));
    }

    // возвращаем память аллокатору
    void deallocate(void *memory_ptr, std::size_t count_objects) {
        //assert(m_allocation_strategy && "Not initialized allocation strategy");
        m_allocation_strategy->deallocate(memory_ptr, count_objects * sizeof(T));
    }

    template<typename U>
    bool operator==(const Allocator<U, AllocationStrategy>& rhs) {
        return this->m_allocation_strategy == rhs.m_allocation_strategy;
    }

};

//template<typename T, typename U, class AllocationStrategy>
//bool operator==(const Allocator<T, AllocationStrategy> &lhs, const Allocator<U, AllocationStrategy> &rhs) {
//    return lhs.m_allocation_strategy == rhs.m_allocation_strategy;
//}
//
//template<typename T, typename U, class AllocationStrategy>
//bool operator!=(const Allocator<T, AllocationStrategy> &lhs, const Allocator<U, AllocationStrategy> &rhs) {
//    return !(lhs == rhs);
//}
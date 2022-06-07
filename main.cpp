#include <chrono>
#include "AllocatorT.h"

template<typename T, std::size_t CHUNK_SIZE = CHUNK_SIZE_PARAMETER>
using CustomAllocator = Allocator<T, CustomAllocationStrategy<CHUNK_SIZE>>;

template<typename T>
using custom_vector = std::vector<T, CustomAllocator<T>>;

int main() {
    CustomAllocationStrategy allocation_area{};

    CustomAllocator<int> custom_int_allocator{allocation_area};

    custom_vector<int> vector{custom_int_allocator};

    std::vector<int> v;

    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    for (int i = 0u; i < 100; ++i) {
        vector.push_back(i);
    }
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "Time difference 1 = " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[ms]" << std::endl;

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    for (int i = 0u; i < 100; ++i) {
        v.push_back(i);
    }
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "Time difference 2 = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[ms]" << std::endl;

    vector.resize(16u);
    for (int val: vector) {
        std::cout << val << " ";
    }
    return 0;
}
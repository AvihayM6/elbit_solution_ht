#include <chrono>
#include <iostream>
#include <vector>

constexpr size_t ELEMENT_COUNT = 1000 * 10000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
    std::vector<uint64_t> vec;
    for (size_t i = 0; i < elementCount; ++i) {
        vec.emplace_back(i);
        //Changed push_back method to emplace_back method.
        // Because on emplace_back the new element insertion is insert to the end of the container, right after its current last element.
        // The new element is constructed in place.
    }
    return vec;
}

/// This function should return the total elements in all of the vectors
size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
    return vecOfVec.size() * vecOfVec[0].size();
}

/// This function should return a single vector that contain all of the elements of the vectors in vecOfVec
std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
    std::vector<uint64_t> mergedVec;
    for (int i = 0; i < vecOfVec.size(); ++i) {
        for (int j = 0; j < vecOfVec[i].size(); ++j) {
            mergedVec.emplace_back(vecOfVec[i][j]);
        }
    }
    return mergedVec;
}


int main(int argc, char** argv)
{
    //Create vector of vectors
    std::vector<std::vector<uint64_t>> vecOfVec;
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < ITERATIONS; i++) {
        std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);
        vecOfVec.emplace_back(vec);
    }
    auto end = std::chrono::steady_clock::now();
    size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
    std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;

    //Count elements
    size_t totalElements = count_total_elements(vecOfVec);
    std::cout << "Total elements in vecOfVec: " << totalElements <<  " " << std::endl;

    //Merge vector of vectors
    std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
    std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

    std::cout << "Press enter to exit" << std::endl;

    getchar();
    return 0;
}
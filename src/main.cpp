#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include "Tools/Benchmarks.hpp"
#include "Tools/Utils.hpp"
#include "Tools/DataExporter.hpp"

int main(int argc, char* argv[]) {
    std::map<
        std::string,
        std::function<void(IPriorityQueue* queue, TestingValue testingData)>
    > tests;

    tests["Insert"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->insert(testingData);
    };

    tests["ExtractMax"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->extractMax();
    };

    tests["Peek"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->peek();
    };

    tests["ModifyKey"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->modifyKey(testingData, testingData.newPriority);
    };

    const int maxSize = Benchmark::TESTING_SIZES.back();
    PriorityValue fillData[maxSize];
    for (int i = 0; i < maxSize; ++i){
        fillData[i].priority = Utils::generateNumber();
        fillData[i].value = Utils::generateNumber();
    }
    TestingValue testingData[Benchmark::TESTING_REPETITIONS];

    for (const auto& test : tests) {
        std::cout << "Method: " << test.first << std::endl;
        std::vector<Results> results = Benchmark::run(test.second, fillData, testingData);

        for (auto& benchmark : results) {
            float average = benchmark.average();
            std::cout << "Class: " << benchmark.className;
            std::cout << " Size: " << benchmark.stack;
            std::cout << " Average: " << average << " ns";
            std::cout << std::endl;
        }

        DataExporter exporter(test.first, results);
        exporter.generate();

        std::cout << std::endl;
    }

    return 0;
}

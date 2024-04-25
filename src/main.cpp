#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include "Tools/Benchmarks.hpp"
#include "Tools/DataExporter.hpp"

int main(int argc, char* argv[]) {
    int max_size = 32768;
    std::map<
        std::string,
        std::function<void(IPriorityQueue* queue)>
    > tests;

    tests["Insert"] = [](IPriorityQueue* queue) {
        const int priority = Benchmark::generateNumber();
        const int value = Benchmark::generateNumber();
        queue->insert(PriorityValue(priority, value));
    };

    tests["ExtractMax"] = [](IPriorityQueue* queue) {
        queue->extractMax();
    };

    tests["Peek"] = [](IPriorityQueue* queue) {
        queue->peek();
    };

    tests["ModifyKey"] = [](IPriorityQueue* queue) {
        const int priority = Benchmark::generateNumber();
        const int newPriority = Benchmark::generateNumber();
        const int value = Benchmark::generateNumber();
        queue->modifyKey(PriorityValue(priority, value), newPriority);
    };

    PriorityValue arr[max_size];
    for(int i = 0; i <max_size; ++i){
        arr[i].priority = Benchmark::generateNumber();
        arr[i].value = Benchmark::generateNumber();
    }

    for (const auto& test : tests) {
        std::cout << "Method: " << test.first << std::endl;
        std::vector<Results> results = Benchmark::run(test.second, arr);

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

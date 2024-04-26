#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Queues/PriorityQueueHeap.hpp"
#include "../Queues/PriorityQueueArray.hpp"
#include "../Structures/PriorityValue.hpp"
#include "../Structures/TestingValue.hpp"
#include "Results.hpp"

namespace Benchmark {
    const std::vector<int> TESTING_SIZES = {1024, 2048, 4096, 8192, 12288, 16384, 24576, 32768};
    const int TESTING_REPETITIONS = 30;

    std::vector<Results> run(
        std::function<void(IPriorityQueue* queue, TestingValue testingData)> callback,
        PriorityValue* fillData,
        TestingValue* testingData
    ) {
        std::vector<Results> benchmarks;

        std::map<std::string, IPriorityQueue*> queues;
        queues["PriorityQueueArray"] = new PriorityQueueArray();
        queues["PriorityQueueHeap"] = new PriorityQueueHeap();

        for (const auto& queue : queues) {
            for (const auto& size : TESTING_SIZES) {
                Results result(queue.first, size);
                IPriorityQueue* copies[TESTING_REPETITIONS];

                for (int j = 0; j < size; ++j) {
                    queue.second->insert(fillData[j]);
                }

                if (queue.first == "PriorityQueueArray"){
                    for (int i = 0; i < TESTING_REPETITIONS; ++i){
                        copies[i] = new PriorityQueueArray(dynamic_cast<PriorityQueueArray*>(queue.second));
                    }
                } else if (queue.first == "PriorityQueueHeap") {
                    for (int i = 0; i < TESTING_REPETITIONS; ++i){
                        copies[i] = new PriorityQueueHeap(dynamic_cast<PriorityQueueHeap*>(queue.second));
                    }
                } else {
                    std::cerr << "Unknown queue type: " << queue.first << std::endl;
                    exit(1);
                }

                for (int i = 0; i < TESTING_REPETITIONS; ++i) {
                    const auto timeStart = std::chrono::high_resolution_clock::now();
                    callback(copies[i], testingData[i]);
                    const auto timeEnd = std::chrono::high_resolution_clock::now();
                    const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd - timeStart);
                    result.push(duration.count());
                }
                benchmarks.push_back(result);
            }
        }

        return benchmarks;
    }
}

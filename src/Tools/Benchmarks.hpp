#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

#include "../Queues/PriorityQueueHeap.hpp"
#include "../Queues/PriorityQueueArray.hpp"
#include "../Structures/PriorityValue.hpp"
#include "Results.hpp"

namespace Benchmark {
    const std::vector<int> TESTING_SIZES = {1024, 2048, 4096, 8192, 12288, 16384, 24576, 32768};
    const int TESTING_REPETITIONS = 30;

    int generateNumber() {
        std::random_device rd;
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 100000);
        return dist(gen);
    }

    std::vector<Results> run(std::function<void(IPriorityQueue* queue)> callback) {
        std::map<std::string, IPriorityQueue*> queues;
        std::vector<Results> benchmarks;

        queues["PriorityQueueArray"] = new PriorityQueueArray();
        queues["PriorityQueueHeap"] = new PriorityQueueHeap();

        for (const auto& queue : queues) {
            for (const auto& size : TESTING_SIZES) {
                Results result(queue.first, size);
                for (int j = 0; j < size; ++j) {
                    const int priority = generateNumber();
                    const int value = generateNumber();
                    queue.second->insert(PriorityValue(priority, value));
                }
                for (int i = 0; i < TESTING_REPETITIONS; ++i) {
                    const auto timeStart = std::chrono::high_resolution_clock::now();
                    callback(queue.second);
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

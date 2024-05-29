#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Queues/PriorityQueueHeap.hpp"
#include "../Queues/PriorityQueueArray.hpp"
#include "../Queues/PriorityQueueHeapMap.hpp"
#include "../Queues/PriorityQueueList.hpp"
#include "../Structures/PriorityValue.hpp"
#include "../Structures/TestingValue.hpp"
#include "Results.hpp"
#include "Utils.hpp"

namespace Benchmark {
    const std::vector<int> TESTING_SIZES = {1024, 2048, 4096, 8192, 12288, 16384, 24576, 32768};
//    const int TESTING_REPETITIONS = 1000;

    std::vector<Results> run(
            std::function<void(IPriorityQueue* queue, TestingValue testingData)> callback, // funkcja testująca
            std::map<int,PriorityValue*> &initzialData, // tablica danych inicjalizujących struktury
            std::map<int, TestingValue*> &testingData, // tablica danych testujących
            const int TESTING_REPETITIONS = 1000
    ) {
        std::vector<Results> benchmarks; // vektor wyników

        std::map<std::string, IPriorityQueue*> queues; // mapa: nazwa struktury - struktura
//        queues["PriorityQueueArray"] = new PriorityQueueArray();
//        queues["PriorityQueueHeap"] = new PriorityQueueHeap();
//        queues["PriorityQueueHeapMap"] = new PriroityQueueHeapMap();
queues["PriorityQueueList"] = new PriorityQueueList();


        for (const auto& queue : queues) { // dla obu struktur
            for (const auto& size : TESTING_SIZES) { // dla wszystkich rozmiarów
                Results result(queue.first, size); // inicjalizaja obiektu przechowującego wyniki
                IPriorityQueue* copies[TESTING_REPETITIONS]; // pusta tablica kopi struktur

                for (int j = 0; j < size; ++j) { // uzupełnienie inicjalizującej struktury
                    queue.second->insert(initzialData[size][j]);
                }

                if (queue.first == "PriorityQueueArray"){ // dla kolejki na tablicy
                    for (int i = 0; i < TESTING_REPETITIONS; ++i){ // stworzenie kopii struktur
                        copies[i] = new PriorityQueueArray(dynamic_cast<PriorityQueueArray*>(queue.second));
                    }
                } else if (queue.first == "PriorityQueueHeap") { // dla kolejki na kopcu
                    for (int i = 0; i < TESTING_REPETITIONS; ++i){ // stowrzenie kopii struktur
                        copies[i] = new PriorityQueueHeap(dynamic_cast<PriorityQueueHeap*>(queue.second));
                    }
                } else if (queue.first == "PriorityQueueHeapMap") { // dla kolejki na kopcu
                    for (int i = 0; i < TESTING_REPETITIONS; ++i){ // stowrzenie kopii struktur
                        copies[i] = new PriroityQueueHeapMap(dynamic_cast<PriroityQueueHeapMap*>(queue.second));
                    }
                } else if (queue.first == "PriorityQueueList") { // dla kolejki na kopcu
                    for (int i = 0; i < TESTING_REPETITIONS; ++i){ // stowrzenie kopii struktur
                        copies[i] = new PriorityQueueList(dynamic_cast<PriorityQueueList*>(queue.second));
                    }
                } else { // nieznany typ kolejki - exit
                    std::cerr << "Unknown queue type: " << queue.first << std::endl;
                    exit(1);
                }

                for (int i = 0; i < TESTING_REPETITIONS; ++i) { // testy
                    const auto timeStart = std::chrono::high_resolution_clock::now();
                    callback(copies[i], testingData[size][i]);
                    const auto timeEnd = std::chrono::high_resolution_clock::now();
                    const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd - timeStart);
                    result.push(duration.count()); // dodaj wynik do obiektu przechowującego wyniki
                }
                benchmarks.push_back(result); // dodaj obiekt przechowujący wyniki do vektora takich obiektów

                for(int i = 0; i < TESTING_REPETITIONS; i ++){
                    delete copies[i];
                }

                if (queue.first == "PriorityQueueArray"){ // dla open addressing
                    // delete queue.second;
                    delete queues["PriorityQueueArray"];
                    queues["PriorityQueueArray"] = new PriorityQueueArray();
                } else if (queue.first == "PriorityQueueHeap") { // dla hash table array
                    // delete queue.second;
                    delete queues["PriorityQueueHeap"];
                    queues["PriorityQueueHeap"] = new PriorityQueueHeap();
                } else if (queue.first == "PriorityQueueHeapMap") { // dla cucko hash table
                    // delete queue.second;
                    delete queues["PriorityQueueHeapMap"];
                    queues["PriorityQueueHeapMap"] = new PriroityQueueHeapMap();
                } else if (queue.first == "PriorityQueueList") { // dla cucko hash table
                    // delete queue.second;
                    delete queues["PriorityQueueList"];
                    queues["PriorityQueueList"] = new PriorityQueueList();
                } else { // nieznany typ kolejki - exit
                    std::cerr << "Unknown queue type: " << queue.first << std::endl;
                    exit(1);
                }
            }
        }

        delete queues["PriorityQueueArray"];
        delete queues["PriorityQueueHeap"];
        delete queues["PriorityQueueHeapMap"];
        return benchmarks; // zwraca wektor wyników
    }
}

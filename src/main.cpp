#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include "Tools/Benchmarks.hpp"
#include "Tools/Utils.hpp"
#include "Tools/DataExporter.hpp"

int main(int argc, char* argv[]) {
    std::map< // Słownik mapujący nazwę testu na funkcję testującą
        std::string,
        std::function<void(IPriorityQueue* queue, TestingValue testingData)>
    > tests;

    // Funkcja testowa INSERT
    tests["Insert"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->insert(testingData);
    };

    // Funkcja testowa EXTRACT MAX
    tests["ExtractMax"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->extractMax();
    };

    // Funkcja testowa PEEK
    tests["Peek"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->peek();
    };

    // Funkcja testowa MODIFY KEY
    tests["ModifyKey"] = [](IPriorityQueue* queue, TestingValue testingData) {
        queue->modifyKey(testingData, testingData.newPriority);
    };

    const int maxSize = Benchmark::TESTING_SIZES.back(); // rozmiar największej struktury

    PriorityValue fillData[maxSize]; // tablica danych inicjalizujących
    for (int i = 0; i < maxSize; ++i){ // uzupełnia tablice danych inicjalizujących - losuje dane
        fillData[i].priority = Utils::generateNumber();
        fillData[i].value = Utils::generateNumber();
    }

    TestingValue testingData[Benchmark::TESTING_REPETITIONS]; // losuje dane testujące

    for (const auto& test : tests) { // dla wszystkich testów
        std::cout << "Method: " << test.first << std::endl;
        std::vector<Results> results = Benchmark::run(test.second, fillData, testingData); // funkcja testująca

        for (auto& benchmark : results) { // dla rezultatów
            float average = benchmark.average(); // pobiera średnią z pomiarów
            std::cout << "Class: " << benchmark.className; // nazwa struktury
            std::cout << " Size: " << benchmark.stack; // wielkość struktury
            std::cout << " Average: " << average << " ns"; // średnia
            std::cout << std::endl;
        }

        DataExporter exporter(test.first, results); // inicjalizuje exporter danych do csv poprzez nazwe testu i wyniki testów
        exporter.generate(); // zapisuje dane

        std::cout << std::endl;
    }

    return 0;
}

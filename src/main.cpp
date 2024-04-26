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

    // Mapa rozmiar struktury -> tablica danych inicjalizujących
    std::map<
            int, // rozmiar
            PriorityValue* // tablica danych
    > initzialData;

    // Losowanie danych inicjalizujących dla każdego rozmiaru
    std::cout << "Randoming initzialization data..." << std::endl;
    for(const auto& data : Benchmark::TESTING_SIZES){ // uzupełnia tablice danych inicjalizujących
        initzialData[data] = new PriorityValue[data]; // alokowanie odpowiedniego rozmiaru tablicy
        for(int i = 0; i < data; i++){
            initzialData[data][i] = TestingValue(data);
//
//            initzialData[data][i].value = Utils::generateNumber(data);
//            initzialData[data][i].priority = Utils::generateNumber(data*3);
        }
    }



    /*NIE*/    TestingValue testingData[Benchmark::TESTING_REPETITIONS]{}; // losuje dane testujące ---- NIE
    // Mapa rozmiar struktury -> tablica danych testujących funkcje insert
    std::map<
            int, // rozmiar
            TestingValue* // tablica danych
    > testingDataInsert;

    // Losowanie danych testowych funkcji insert dla każdego rozmiaru
    std::cout << "Randoming testing data..." << std::endl;
    for(const auto& data : Benchmark::TESTING_SIZES){ // uzupełnia tablice danych testujących - dla INSERT
        testingDataInsert[data] = new TestingValue[data]; // alokowanie odpowiedniego rozmiaru tablicy
        for(int i = 0; i < data; i++){
            testingDataInsert[data][i] = TestingValue(data);
        }
    }

    // Mapa rozmiar struktury -> tablica danych testujących funkcje modify
    std::map<
            int, // rozmiar
            TestingValue* // tablica danych
    > testingDataModify;

    // Losowanie danych testowych funkcji modify dla każdego rozmiaru
    for(const auto& data : Benchmark::TESTING_SIZES){ // uzupełnia tablice danych testujących - dla INSERT
        testingDataModify[data] = new TestingValue[data]; // alokowanie odpowiedniego rozmiaru tablicy
        for(int i = 0; i < data; i++){
            testingDataModify[data][i] = TestingValue(initzialData[data],data);
        }
    }

    std::cout << "Randoming data finished." << std::endl << std::endl;

    std::cout << "Testing data..." << std::endl << std::endl;


    DataExporter exporter; // inicjalizuje exporter danych do csv poprzez nazwe testu i wyniki testów
    std::string folderPath = exporter.createNewFolder();
    for (const auto& test : tests) { // dla wszystkich testów
        std::vector<Results> results; // vektor rezultatów
        std::cout << "Method: " << test.first << "..." << std::endl;
        if (test.first == "ModifyKey"){
            results = Benchmark::run(test.second, initzialData, testingDataModify); // funkcja testująca
        } else {
            results = Benchmark::run(test.second, initzialData, testingDataInsert); // funkcja testująca
        }

        for (auto& benchmark : results) { // dla rezultatów
            float average = benchmark.average(); // pobiera średnią z pomiarów
            std::cout << "Class: " << benchmark.className; // nazwa struktury
            std::cout << " Size: " << benchmark.stack; // wielkość struktury
            std::cout << " Average: " << average << " ns"; // średnia
            std::cout << std::endl;
        }

        exporter = DataExporter(test.first, results); // inicjalizuje exporter danych do csv poprzez nazwe testu i wyniki testów
        exporter.generate(folderPath); // zapisuje dane

        std::cout << std::endl;
    }

    return 0;
}

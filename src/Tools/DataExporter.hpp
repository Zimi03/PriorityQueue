#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Results.hpp"

class DataExporter {
    std::string name;
    std::vector<Results> results;

    public:
        DataExporter(
            const std::string _name,
            const std::vector<Results>& _results
        ) :  name(_name), results(_results) {}

        void generate() {
            std::fstream fs(filename(), std::ios::out);

            if (!fs.is_open()) {
                std::cerr << "Could not open file " << filename() << std::endl;
                return;
            }

            const std::string header = "className;stack;average\n";
            fs << header;

            for (auto result : results) {
                fs << result.className << ";" << result.stack << ";" << result.average() << "\n";
            }

            fs.close();
        }

    private:
        std::string filename() {
            return "results_" + name + ".csv";
        }
};

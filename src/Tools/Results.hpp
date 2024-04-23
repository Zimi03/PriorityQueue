#pragma once

#include <vector>
#include <string>
#include <numeric>

class Results
{
    public:
        std::string className;
        std::vector<int> durations;
        int stack;

        Results(
            std::string className,
            int stack
        ) : className(className), stack(stack) {}

        void push(int duration) {
            durations.push_back(duration);
        }

        float average() {
            if (durations.empty()) return 0;
            auto const count = durations.size();
            return std::reduce(durations.begin(), durations.end()) / count;
        }
};

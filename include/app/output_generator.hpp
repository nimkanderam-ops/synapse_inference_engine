#pragma once
#include "core/tensor.hpp"
#include <string>
#include <vector>

class OutputGenerator
{
    private:
        std::vector<std::string> labels;

    public:
        OutputGenerator() = default;

        void loadLabels(const std::string& filepath);
        std::string generate(const Tensor& output) const;
        bool isLoaded() const;
};

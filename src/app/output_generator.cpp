#include "app/output_generator.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

void OutputGenerator::loadLabels(const std::string& filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open())
    {
        throw std::runtime_error("Failed to open labels file: " + filepath);
    }

    std::string line;
    while(std::getline(file, line))
    {
        
        std::istringstream iss(line);
        int index;
        std::string label;
        if(iss >> index >> label)
        {
            
            std::string rest;
            if(std::getline(iss, rest))
            {
                label += rest;
            }
            
            
            if(index >= static_cast<int>(labels.size()))
            {
                labels.resize(index + 1, "Unknown");
            }
            labels[index] = label;
        }
    }

    std::cout << "[SYSTEM] Labels loaded: " << labels.size() << " classes\n";
}

std::string OutputGenerator::generate(const Tensor& output) const
{
    const auto& data = output.getdata();

    if(data.empty())
    {
        return "[ERROR] Empty output tensor.";
    }

    
    int predictedIndex = 0;
    float maxVal = data[0];
    for(size_t i = 1; i < data.size(); ++i)
    {
        if(data[i] > maxVal)
        {
            maxVal = data[i];
            predictedIndex = static_cast<int>(i);
        }
    }

    
    std::ostringstream result;

    std::string predictedLabel = (predictedIndex < static_cast<int>(labels.size()))
        ? labels[predictedIndex] : "Class_" + std::to_string(predictedIndex);

    result << "\n  Result: " << predictedLabel 
           << "  (" << std::fixed << std::setprecision(1) << (maxVal * 100.0f) << "%)\n";
    result << "  ----------------------------------------\n";

    
    for(size_t i = 0; i < data.size(); ++i)
    {
        std::string label = (i < labels.size()) ? labels[i] : "Class_" + std::to_string(i);
        float confidence = data[i] * 100.0f;

        
        while(label.size() < 12) label += " ";

        
        int barLen = static_cast<int>(data[i] * 20.0f);
        std::string bar(barLen, '#');

        result << "  " << label << " " << bar;
    
        for(int j = barLen; j < 20; ++j) result << " ";
        result << "  " << std::fixed << std::setprecision(1) << confidence << "%\n";
    }

    return result.str();
}

bool OutputGenerator::isLoaded() const
{
    return !labels.empty();
}

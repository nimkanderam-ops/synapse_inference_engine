#include "core/modelfactory.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

std::vector<std::unique_ptr<layer>> ModelFactory::buildnetwork(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    if(!file.is_open())
    {
        throw std::runtime_error("Failed to open model file: " + filepath);
    }

    int num_layers;
    file.read(reinterpret_cast<char*>(&num_layers), sizeof(int));
    std::cout << "[SYSTEM] Factory assembling network with " << num_layers << " layers\n";

    std::vector<std::unique_ptr<layer>> network;

    for(int i = 0; i < num_layers; ++i)
    {
        int in_size, out_size, act_type;
        file.read(reinterpret_cast<char*>(&in_size), sizeof(int));
        file.read(reinterpret_cast<char*>(&out_size), sizeof(int));
        file.read(reinterpret_cast<char*>(&act_type), sizeof(int));

        ActivationType activation = static_cast<ActivationType>(act_type);

        
        const char* act_names[] = {"None", "ReLU", "Sigmoid", "Softmax", "Tanh"};
        const char* act_name = (act_type >= 0 && act_type <= 4) ? act_names[act_type] : "Unknown";
        std::cout << "  Layer " << i + 1 << ": " << in_size << "x" << out_size << " [" << act_name << "]\n";

        int weight_count = in_size * out_size;
        std::vector<float> weightdata(weight_count);
        file.read(reinterpret_cast<char*>(weightdata.data()), weight_count * sizeof(float));

        int bias_count = out_size;
        std::vector<float> biasdata(bias_count);
        file.read(reinterpret_cast<char*>(biasdata.data()), bias_count * sizeof(float));

        Tensor weights({in_size, out_size}, weightdata);
        Tensor bias({1, out_size}, biasdata);

        network.push_back(std::make_unique<linearlayer>(weights, bias, activation));
    }

    return network;
}

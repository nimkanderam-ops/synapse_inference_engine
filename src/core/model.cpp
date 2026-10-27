#include "core/model.hpp"
#include <iostream>

Model::Model(std::vector<std::unique_ptr<layer>> layers)
    : layers(std::move(layers)) {}

Tensor Model::forward(const Tensor& input) const
{
    Tensor current = input;
    for(size_t i = 0; i < layers.size(); ++i)
    {
        current = layers[i]->forward(current);
    }
    return current;
}

int Model::getLayerCount() const
{
    return static_cast<int>(layers.size());
}

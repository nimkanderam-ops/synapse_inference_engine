#include "core/linearlayer.hpp"

linearlayer::linearlayer(const Tensor& weights, const Tensor& biases, ActivationType activation)
    : weights(weights), biases(biases), activation(activation) {}

Tensor linearlayer::applyActivation(const Tensor& input) const
{
    switch(activation)
    {
        case ActivationType::RELU:    return input.relu();
        case ActivationType::SIGMOID: return input.sigmoid();
        case ActivationType::SOFTMAX: return input.softmax();
        case ActivationType::TANH:    return input.tanh_activation();
        case ActivationType::NONE:
        default:                      return input;
    }
}

Tensor linearlayer::forward(const Tensor& input) const
{
    Tensor output = input.matmul(weights);
    output = output.add(biases);
    return applyActivation(output);
}

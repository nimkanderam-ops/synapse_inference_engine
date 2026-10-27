#pragma once
#include "core/layer.hpp"

enum class ActivationType
{
    NONE = 0,
    RELU = 1,
    SIGMOID = 2,
    SOFTMAX = 3,
    TANH = 4
};

class linearlayer : public layer
{
    private:
        Tensor weights;
        Tensor biases;
        ActivationType activation;

        Tensor applyActivation(const Tensor& input) const;
    
    public:
        linearlayer(const Tensor& weights, const Tensor& biases, ActivationType activation = ActivationType::NONE);

        Tensor forward(const Tensor& input) const override;
};
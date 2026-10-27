#pragma once
#include "core/model.hpp"
#include "core/tensor.hpp"

class InferenceEngine
{
    public:
        Tensor run(const Model& model, const Tensor& input) const;
};

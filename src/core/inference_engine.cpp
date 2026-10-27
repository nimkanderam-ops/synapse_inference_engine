#include "core/inference_engine.hpp"
#include <iostream>

Tensor InferenceEngine::run(const Model& model, const Tensor& input) const
{
    std::cout << "[SYSTEM] Running forward pass...\n";
    Tensor output = model.forward(input);
    return output;
}

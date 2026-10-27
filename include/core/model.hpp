#pragma once
#include "core/layer.hpp"
#include <vector>
#include <memory>

class Model
{
    private:
        std::vector<std::unique_ptr<layer>> layers;

    public:
        Model(std::vector<std::unique_ptr<layer>> layers);

        Tensor forward(const Tensor& input) const;

        int getLayerCount() const;
};

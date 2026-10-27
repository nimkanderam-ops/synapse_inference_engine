#pragma once
#include "core/tensor.hpp"

class layer
{
    public:
        virtual ~layer()=default;

        virtual Tensor forward(const Tensor& input) const =0;
};
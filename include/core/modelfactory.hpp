#pragma once
#include "core/layer.hpp"
#include "core/linearlayer.hpp"
#include <string>
#include <vector>
#include <memory>

class ModelFactory
{
    public:
        static std::vector<std::unique_ptr<layer>> buildnetwork(const std::string& filepath);
};
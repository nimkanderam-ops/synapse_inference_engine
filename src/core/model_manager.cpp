#include "core/model_manager.hpp"
#include <iostream>
#include <stdexcept>

void ModelManager::loadModel(const std::string& filepath)
{
    
    if(model)
    {
        std::cout << "[SYSTEM] Destroying previous model...\n";
        model.reset();
    }

    std::cout << "[SYSTEM] Loading model from: " << filepath << "\n";

    
    auto layers = ModelFactory::buildnetwork(filepath);
    model = std::make_unique<Model>(std::move(layers));

    std::cout << "[SYSTEM] Model loaded successfully. (" << model->getLayerCount() << " layers)\n";
}

void ModelManager::destroyModel()
{
    if(model)
    {
        model.reset();
        std::cout << "[SYSTEM] Model destroyed.\n";
    }
    else
    {
        std::cout << "[SYSTEM] No model loaded.\n";
    }
}

Model& ModelManager::getModel()
{
    if(!model)
    {
        throw std::runtime_error("No model is currently loaded. Use 'load' first.");
    }
    return *model;
}

bool ModelManager::hasModel() const
{
    return model != nullptr;
}

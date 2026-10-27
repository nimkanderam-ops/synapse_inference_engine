#pragma once
#include "core/model.hpp"
#include "core/modelfactory.hpp"
#include <memory>
#include <string>

class ModelManager
{
    private:
        std::unique_ptr<Model> model;

    public:
        ModelManager() = default;

        void loadModel(const std::string& filepath);
        void destroyModel();
        Model& getModel();
        bool hasModel() const;
};

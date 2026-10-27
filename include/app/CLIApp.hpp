#pragma once
#include "core/model_manager.hpp"
#include "core/tokenizer.hpp"
#include "core/inference_engine.hpp"
#include "app/output_generator.hpp"
#include <string>
#include <unordered_map>
#include <functional>

class CLIApp
{
    private:
        bool isrunning;
        ModelManager modelManager;
        Tokenizer tokenizer;
        InferenceEngine engine;
        OutputGenerator outputGen;
        std::unordered_map<std::string, std::function<void()>> commands;

        void displayHelp() const;
        void handleLoad();
        void handleInfer();
        void handleUnload();
        void handleExit();

    public:
        CLIApp();
        void run();
};

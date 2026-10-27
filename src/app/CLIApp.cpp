#include "app/CLIApp.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace {
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }
}

CLIApp::CLIApp() : isrunning(true)
{
    commands["help"] = [this]() { displayHelp(); };
    commands["load"] = [this]() { handleLoad(); };
    commands["infer"] = [this]() { handleInfer(); };
    commands["unload"] = [this]() { handleUnload(); };
    commands["exit"] = [this]() { handleExit(); };
}

void CLIApp::run()
{
    std::cout << "========================================\n";
    std::cout << "    Project SYNAPSE: Inference Engine   \n";
    std::cout << "========================================\n";
    std::cout << "Type 'help' for a list of commands.\n\n";

    std::string line;
    while(isrunning)
    {
        std::cout << " SYNAPSE > ";
        if (!std::getline(std::cin, line))
        {
            break;
        }

        std::string trimmed = trim(line);
        if (trimmed.empty())
        {
            continue;
        }

        std::istringstream iss(trimmed);
        std::string cmd;
        iss >> cmd;

        std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c){ return std::tolower(c); });

        auto it = commands.find(cmd);
        if(it != commands.end())
        {
            it->second();
        }
        else
        {
            std::cout << "[ERROR] Invalid command: '" << cmd << "'. Type 'help' for available commands.\n";
        }
    }
}

void CLIApp::displayHelp() const
{
    std::cout << "\nAvailable commands:\n"
              << "  help   - Show this help message\n"
              << "  load   - Load model weights, vocabulary, and labels\n"
              << "  infer  - Run a forward pass / prediction on input text\n"
              << "  unload - Unload the active model from memory\n"
              << "  exit   - Terminate the engine\n\n";
}

void CLIApp::handleLoad()
{
    std::string modelPath;
    std::cout << "Enter model path [default: models/model.bin]: ";
    std::getline(std::cin, modelPath);
    modelPath = trim(modelPath);
    if (modelPath.empty()) modelPath = "models/model.bin";

    std::string vocabPath;
    std::cout << "Enter vocab path [default: models/vocab.txt]: ";
    std::getline(std::cin, vocabPath);
    vocabPath = trim(vocabPath);
    if (vocabPath.empty()) vocabPath = "models/vocab.txt";

    std::string labelsPath;
    std::cout << "Enter labels path [default: models/labels.txt]: ";
    std::getline(std::cin, labelsPath);
    labelsPath = trim(labelsPath);
    if (labelsPath.empty()) labelsPath = "models/labels.txt";

    try
    {
        modelManager.loadModel(modelPath);
        tokenizer.loadVocab(vocabPath);
        outputGen.loadLabels(labelsPath);
        std::cout << "[SUCCESS] Model, vocabulary, and labels loaded successfully!\n\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "[ERROR] Failed to load: " << e.what() << "\n\n";
    }
}

void CLIApp::handleInfer()
{
    if (!modelManager.hasModel())
    {
        std::cout << "[ERROR] No model loaded. Please run 'load' first.\n";
        return;
    }
    if (!tokenizer.isLoaded())
    {
        std::cout << "[ERROR] Tokenizer vocabulary not loaded. Please run 'load' first.\n";
        return;
    }

    std::cout << "Enter input text / prompt: ";
    std::string prompt;
    std::getline(std::cin, prompt);
    prompt = trim(prompt);

    if (prompt.empty())
    {
        std::cout << "[WARNING] Empty input received. Inference aborted.\n";
        return;
    }

    try
    {
        Tensor inputTensor = tokenizer.encode(prompt);
        Tensor outputTensor = engine.run(modelManager.getModel(), inputTensor);
        std::string resultStr = outputGen.generate(outputTensor);
        std::cout << resultStr << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "[ERROR] Inference failed: " << e.what() << "\n";
    }
}

void CLIApp::handleUnload()
{
    modelManager.destroyModel();
}

void CLIApp::handleExit()
{
    std::cout << "[SYSTEM] Shutting down Synapse Engine, freeing memory...\n";
    modelManager.destroyModel();
    isrunning = false;
}
#pragma once
#include "core/tensor.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Tokenizer
{
    private:
        std::unordered_map<std::string, int> wordToId;
        std::unordered_map<int, std::string> idToWord;
        int vocabSize;
        int unknownId;
        int padId;

    public:
        Tokenizer() : vocabSize(0), unknownId(0), padId(1) {}

        void loadVocab(const std::string& filepath);
        Tensor encode(const std::string& text) const;
        std::string decode(const Tensor& tokens) const;
        bool isLoaded() const;
        int getVocabSize() const;
};

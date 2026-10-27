#include "core/tokenizer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

void Tokenizer::loadVocab(const std::string& filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open())
    {
        throw std::runtime_error("Failed to open vocab file: " + filepath);
    }

    std::string word;
    int id;
    while(file >> word >> id)
    {
        wordToId[word] = id;
        idToWord[id] = word;
    }

    vocabSize = static_cast<int>(wordToId.size());

    
    auto unkIt = wordToId.find("<unk>");
    if(unkIt != wordToId.end()) unknownId = unkIt->second;

    auto padIt = wordToId.find("<pad>");
    if(padIt != wordToId.end()) padId = padIt->second;

    std::cout << "[SYSTEM] Vocabulary loaded: " << vocabSize << " words\n";
}

Tensor Tokenizer::encode(const std::string& text) const
{
    if(vocabSize == 0)
    {
        throw std::runtime_error("Vocabulary not loaded. Load vocab first.");
    }

    
    std::string lower = text;
    std::transform(lower.begin(), lower.end(), lower.begin(),
        [](unsigned char c){ return std::tolower(c); });


    std::vector<float> bow(vocabSize, 0.0f);

    std::istringstream stream(lower);
    std::string word;
    int tokenCount = 0;

    while(stream >> word)
    {
        auto it = wordToId.find(word);
        if(it != wordToId.end())
        {
            bow[it->second] = 1.0f;
            tokenCount++;
        }
        else
        {
            
            bow[unknownId] = 1.0f;
        }
    }

    std::cout << "[SYSTEM] Tokenized: " << tokenCount << " known tokens\n";
    return Tensor({1, vocabSize}, bow);
}

std::string Tokenizer::decode(const Tensor& tokens) const
{
    std::string result;
    const auto& data = tokens.getdata();
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(data[i] > 0.5f)
        {
            auto it = idToWord.find(static_cast<int>(i));
            if(it != idToWord.end())
            {
                if(!result.empty()) result += " ";
                result += it->second;
            }
        }
    }
    return result;
}

bool Tokenizer::isLoaded() const
{
    return vocabSize > 0;
}

int Tokenizer::getVocabSize() const
{
    return vocabSize;
}

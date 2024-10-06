
#include "dictionary.h"
#include <iostream>
#include <fstream>

std::string Dictionary::WordListPath = "assets/words/words.txt";
#define CEIL(x,y) (((x) + (y) - 1) / (y))

constexpr int ConstIntCeil(float f)
{
    const int i = static_cast<int>(f);
    return f > i ? i + 1 : i;
}
void Dictionary::ParseWords(std::vector<std::string> words)
{
    for (std::string word : words)
    {
        Dictionary::AddWord(word);
    }
}
void Dictionary::WaitForLoading()
{
    for (std::thread& thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }
    if (Dictionary::LoadThread.joinable())
        LoadThread.join();
}
void Dictionary::LoadDictionary()
{
    std::ifstream stream(WordListPath);
    std::string line;

    constexpr int arraySize = ConstIntCeil(_NumThreads);
    std::vector<std::string> lines[arraySize];

    if (stream.is_open())
    {
        while (getline(stream,line))
        {
            //convert ascii 97-132 [a-z] to 0-25
            char firstChar = TrieNode::ToArrayIndex(tolower(line[0]));
            int pool = firstChar % _NumThreads;
            lines[pool].push_back(line);
        }
    }
    else
    {
        std::cout << "Could not open " << WordListPath;
    }

    for (int i = 0; i < _NumThreads; i++)
    {
        threads[i] = std::thread(Dictionary::ParseWords, lines[i]);
    }
    
}
int Dictionary::NumWildcards(std::string word)
{
    int numWildcards = 0;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == '*')
            numWildcards++;
    }
    return numWildcards;
}
void Dictionary::AddWord(std::string word)
{
    TrieNode* currentNode = &FirstNode;
    for (char c : word)
    {
        if (!isalpha(c) || !islower(c))
            return;
        char arrayIndex = TrieNode::ToArrayIndex(c);
        if (!currentNode->Children[arrayIndex])
        {
            currentNode->Children[arrayIndex] = std::make_unique<TrieNode>();
        }
        currentNode = currentNode->Children[arrayIndex].get();
    }
    currentNode->isEnd = true;
}
 bool Dictionary::CheckWord(std::string word)
 {
    WaitForLoading();
    return CheckWord(word, &FirstNode, 0);
}
void Dictionary::ClearThreads()
{
    WaitForLoading();
}
bool Dictionary::CheckWord(std::string word, TrieNode* startAt, int depth)
{
    TrieNode* currentNode = startAt;

    for (int i = depth; i < word.size(); i++)
    {
        char c = word[i];
        char arrayIndex = TrieNode::ToArrayIndex(c);

        if (word[i] == '*')
        {
            for (int j = 0; j < 26; j++)
            {
                char toTest = 'a' + j;
                std::string newWord = word;
                newWord[i] = toTest;
                int newArrayIndex = TrieNode::ToArrayIndex(toTest);
                if (CheckWord(newWord, currentNode, i))
                    return true;
            }
        }
        else
        {
            if (currentNode->Children[arrayIndex] == nullptr)
            {
                return false;
            }
            currentNode = currentNode->Children[arrayIndex].get();
            if (i == word.size() - 2)
            {
                return (currentNode->isEnd);
            }
        }
    }

    return false;

}
void Dictionary::InitDictionary()
{
    Dictionary::LoadThread = std::thread(Dictionary::LoadDictionary);
}
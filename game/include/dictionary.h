#pragma once
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iostream>
#include <thread>
#include "updatable.h"

#define _AlphabetCharacters 26
#define _NumThreads 4
class TrieNode
{
public:
    std::unique_ptr<TrieNode> Children[_AlphabetCharacters];
    bool isEnd;

    static char ToArrayIndex(char c)
    {
        return c - 97;
    }

    TrieNode()
    {
        for (int i = 0; i < _AlphabetCharacters; i++)
        {
            Children[i] = nullptr;
        }
    }
};

class Dictionary : Updatable
{
public:
    static Dictionary _Dictionary;
    inline static TrieNode FirstNode = TrieNode();
    static std::unordered_set<std::string> dict;
    static bool TestWord(std::string word);

    static int NumWildcards(std::string word);

    static void LoadDictionary();

    inline static std::thread threads[_NumThreads];
    static void WaitForLoading();
    inline static std::thread LoadThread;
    static void ClearThreads()
    {
        WaitForLoading();
    }
    static void AddWord(std::string word)
    {
        TrieNode* currentNode = &FirstNode;
        for (char c : word)
        {
            if (!isalpha(c) || !islower(c))
                return;
            char arrayIndex = TrieNode::ToArrayIndex(c);
            if (!currentNode->Children[arrayIndex])
            {
                //currentNode->Children[arrayIndex] = std::make_unique<TrieNode>();
                currentNode->Children[arrayIndex] = std::make_unique<TrieNode>();
            }
            currentNode = currentNode->Children[arrayIndex].get();
        }
        currentNode->isEnd = true;
    }

    static bool CheckWord(std::string word)
    {
        WaitForLoading();
        return CheckWord(word, &FirstNode, 0);
    }
private:
    static std::string WordListPath;
    static void ParseWords(std::vector<std::string> words);

    static bool CheckWord(std::string word, TrieNode* startAt, int depth)
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
};

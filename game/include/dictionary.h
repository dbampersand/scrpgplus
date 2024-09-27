#pragma once
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iostream>
class TrieNode
{
public:

    std::unordered_map<char, TrieNode> Children;
    bool isEnd;

    TrieNode(char c)
    {
    }
    ~TrieNode() = default;


};
class Trie
{
public:
    static Trie Dictionary;
    inline static TrieNode FirstNode = TrieNode('a');
    static void AddWord(std::string word)
    {
        TrieNode* currentNode = &FirstNode;
        for (char c : word)
        {
            if (currentNode->Children.find(c) == currentNode->Children.end())
            {
                TrieNode newNode = TrieNode(c);
                currentNode->Children.insert( { c,newNode });
            }
            currentNode = &currentNode->Children.at(c);
        }
        currentNode->isEnd = true;
    }
    static bool CheckWord(std::string word)
    {
        TrieNode* currentNode = &FirstNode;
        
        for (int i = 0; i < word.size(); i++)
        {
            char c = word[i];
            if (word[i] == '*')
            {
                for (int j = 0; j < 26; j++)
                {
                    char toTest = 'a' + j;
                    std::string newWord = word;
                    newWord[i] = toTest;
                    if (CheckWord(newWord))
                        return true;
                }
            }

            else if (currentNode->Children.find(c) == currentNode->Children.end())
            {
                return false;
            }
            if (currentNode->Children.find(c) == currentNode->Children.end())
                return false;
            currentNode = &currentNode->Children.at(c);
            if (i == word.size() - 1)
            {
                return (currentNode->isEnd);
            }

        }
        return false;
        /*start:
        for (TrieNode child : currentNode->Children)
        {
            if (word[currentWordIndex] == child.NodeCharacter)
            {
                if (currentWordIndex == word.size() - 1)
                {
                    return true;
                }
                currentNode = &child;
                goto start;
            }
            if (word[currentWordIndex] == '*')
            {
                for (int i = 0; i < 27; i++)
                {
                    char toTest = 'a' + i;
                    std::string newWord = word;
                    newWord[currentWordIndex] = toTest;
                    TestWord(newWord);
                }
            }
        }*/
        return false;

    }
};

class Dictionary
{
    static std::unordered_set<std::string> dict;
    static bool TestWord(std::string word);

    public:
        static std::string WordListPath;
        static void LoadDict(std::string path);
        static int NumWildcards(std::string word);
        static std::vector<int> GetWildcardPositions(std::string word);
        static std::string CheckWord(std::string word);
};
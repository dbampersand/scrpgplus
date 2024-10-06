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
    //all child nodes
    std::unique_ptr<TrieNode> Children[_AlphabetCharacters];
    // the node is an end point - i.e. it is a word
    bool isEnd = false;

    static char ToArrayIndex(char c)
    {
        return c - 97;
    }

    TrieNode()
    {
    }
};

class Dictionary : Updatable
{
public:
   
    //Count number of wildcards in a word
    static int NumWildcards(std::string word);


    //Waits for threads to finish 
    static void WaitForLoading();

    //Destroy old threads
    static void ClearThreads();

    //Check if word exists in dictionary
    static bool CheckWord(std::string word);

    //Initialises dictionary loading
    static void InitDictionary();

private:
    //First node of trie
    inline static TrieNode FirstNode = TrieNode();
   
    //path for the word list txt file
    static std::string WordListPath;

    //Threads for building trie
    inline static std::thread threads[_NumThreads];

    //Thread for async loading
    inline static std::thread LoadThread;

    static Dictionary _Dictionary;
    static std::unordered_set<std::string> dict;


    //Load dictionary into RAM and build trie
    static void LoadDictionary();

    static void ParseWords(std::vector<std::string> words);
    //reentrant version of CheckWord so that we can parse wildcards starting at the depth of the wildcard
    static bool CheckWord(std::string word, TrieNode* startAt, int depth);
    //Add word to dictionary trie
    static void AddWord(std::string word);



};

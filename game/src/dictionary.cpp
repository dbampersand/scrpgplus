
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

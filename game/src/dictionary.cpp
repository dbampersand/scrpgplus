
#include "dictionary.h"
#include <iostream>
#include <fstream>

std::unordered_set<std::string> Dictionary::dict;
std::string Dictionary::WordListPath = "assets/words/words.txt";

void Dictionary::LoadDictionary()
{
    std::ifstream stream(WordListPath);
    std::string line;
    if (stream.is_open())
    {
        while (getline(stream,line))
        {
            //dict.insert(line);
            Dictionary::AddWord(line);
        }
    }
    else
    {
        std::cout << "Could not open " << WordListPath;
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


#include "dictionary.h"
#include <iostream>
#include <fstream>

std::unordered_set<std::string> Dictionary::dict;
std::string Dictionary::WordListPath = "assets/words/words.txt";

void Dictionary::LoadDict(std::string path)
{
    std::ifstream stream(path);
    std::string line;
    if (stream.is_open())
    {
        while (getline(stream,line))
        {
            dict.insert(line);
        }
    }
    else
    {
        std::cout << "Could not open " << path;
    }

}
bool Dictionary::TestWord(std::string word)
{
    if (dict.size() == 0)
        LoadDict(WordListPath);
    if (word.size() == 0)
        return false;
    return (dict.count(word) > 0);
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

std::vector<int> Dictionary::GetWildcardPositions(std::string word)
{
    std::vector<int> positions;
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == '*')
            positions.push_back(i);
    }

    return positions;
}
// recursively checks words if a wildcard is in the given word
// VERY SLOW when there's a lot of wildcards 
// TODO: replace with a trie solution
std::string Dictionary::CheckWord(std::string word)
{
    int firstWildcardPosition = word.find("*");
    // if we have no wildcards, just run TestWord
    if (firstWildcardPosition == -1)
        return TestWord(word) == true ? word : "";
    std::string temp = word;

    // initialise * to 'a' so we can iterate over the entire alphabet by incrementing 
    temp[firstWildcardPosition] = 'a';
    
    for (int j = 0; j < 26; j++)
    {
        if (TestWord(temp))
            return temp;

        std::string s =  CheckWord(temp);
        // if we have a match 
        if (s.size() > 0)
            return s;
        temp[firstWildcardPosition]++;
    }
    // no match
    return "";
}


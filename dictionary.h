#pragma once
#include <unordered_set>

class Dictionary
{
    static std::unordered_set<std::string> dict;
    static std::string WordListPath;
    static bool TestWord(std::string word);

    public:
        static void LoadDict(std::string path);
        static int NumWildcards(std::string word);
        static std::vector<int> GetWildcardPositions(std::string word);
        static std::string CheckWord(std::string word);
};
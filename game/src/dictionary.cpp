
#include "dictionary.h"
#include <fstream>
#include "UI.h"

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
    //If we're calling this, then we need access to the dictionary but the Trie isn't fully built yet
    //so we need to wait for the threads to finish

    //Finish loading the txt file
    if (Dictionary::LoadThread.joinable())
        LoadThread.join();

    //Finish the trie building threads
    for (std::thread& thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }
}
void Dictionary::LoadDictionary()
{
    std::ifstream stream(WordListPath);
    std::string line;

    //Creates pools of arrays so we can split the Trie building between threads
    constexpr int arraySize = ConstIntCeil(_NumThreads);
    std::vector<std::string> lines[arraySize];

    if (stream.is_open())
    {
        while (getline(stream,line))
        {
            //convert ascii 97-132 [a-z] to 0-25
            char firstChar = TrieNode::ToArrayIndex(tolower(line[0]));
            //Set the threading pool based on the first character - there will be no thread race conditions as they are all going down seperate Trie paths
            int pool = firstChar % _NumThreads;
            lines[pool].push_back(line);
        }
    }
    else
    {
        UI::ConsolePrint("Could not open " + WordListPath);
        exit(1);
    }

    //Start the threads
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
        //the branch path doesn't exist, we need to make it now
        if (!currentNode->Children[arrayIndex])
        {
            currentNode->Children[arrayIndex] = std::make_unique<TrieNode>();
        }
        currentNode = currentNode->Children[arrayIndex].get();
    }
    //We're at the end of the trie: mark this as a word
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

        //We're at a wildcard, recursively search down the trie starting at the current node
        if (word[i] == '*')
        {
            //iterate over the entire alphabet
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
            //we've came to a dead end: this isn't a word in the dictionary
            if (currentNode->Children[arrayIndex] == nullptr)
            {
                return false;
            }
            //set current node to the current character's index so we can continue going down the trie
            currentNode = currentNode->Children[arrayIndex].get();
            //if the next node is the final node, then we just need to check if it's a word or not
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
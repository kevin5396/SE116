/*
 * File: WordLadder.cpp
 * --------------------
 *
 * Name: 凌康伟
 * Student ID:  5140219259
 * This file is the starter project for the word ladder problem.
 *
 */
#include <iostream>
#include <fstream>
#include "vector.h"
#include "queue.h"
#include "lexicon.h"
using std::string;using std::endl;using std::cout;using std::cin;
using Ladder = Vector<string>;

void printLadder(const Ladder &ladder);
Vector<string> wordLadder(const string &start, const string &end, Lexicon &dict);

int main()
{
    Lexicon dict("/Users/kevin/Study/se116/Lab1/WordLadder/EnglishWords.dat");
    while (true)
    {
        string startWord, endWord;
        cout << "Enter start word (RETURN to quit): ";
        getline(cin, startWord);
        if (startWord.empty())
            break;
        cout << "Enter destination word: ";
        getline(cin, endWord);
        startWord = toLowerCase(startWord);
        endWord = toLowerCase(endWord);
        Ladder ladder = wordLadder(startWord, endWord, dict);
        printLadder(ladder);
    }
    return 0;
}

void printLadder(const Ladder &ladder)
{
    for (auto &word : ladder)
        cout << word << ' ';
    cout << endl;
}
Vector<string> wordLadder(const string &start, const string &end, Lexicon& dict)
{
    Lexicon usedWords;
    usedWords.clear();
    Ladder ladder;
    if (!(dict.contains(start)&&dict.contains(end)))  // check if both words are valid
    {
        return ladder;
    }
    Queue<Ladder> ladderQueue;
    ladder.push_back(start);
    ladderQueue.add(ladder);
    while (!ladderQueue.isEmpty())
    {
        Ladder first = ladderQueue.dequeue();            //dequeue the first ladder
        string bridge = first[first.size()-1];           // use the end word to be the bridge
        if (bridge == end)
            return first;
        for (int i = 0 ; i < bridge.size(); ++i)        // iterate through every possible transform
        {
            string search = bridge;
            char c;
            for (c = 'a'; c <= 'z' ; ++c)
            {
                search = bridge;
                if (bridge[i] == c)
                    continue;
                search[i] = c;
                if (dict.contains(search) && !usedWords.contains(search))    // valid word and not used
                {
                    usedWords.add(search);                                  //marked this word used
                    Ladder newLadder(first);                                //copy the ladder
                    newLadder.push_back(search);                            //build the new ladder
                    ladderQueue.enqueue(newLadder);                         //push it to the queue
                }
                
            }
        }
    }
    return Vector<string>();
}



// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool checkLetter(int row, int col);
    bool humanWordSearch(string word);
    void computerWordSearchHelper(Set<string>& result,string words, int row, int col);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    // TODO: add any other member functions/variables necessary
    Grid<char> gameboard;
    Grid<int> mark;
    Lexicon dict;

};

#endif // _boggle_h

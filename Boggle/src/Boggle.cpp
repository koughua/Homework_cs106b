// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "shuffle.h"
//shuffle(array, length);
#include "random.h"
//randomInteger(0, 6);
#include <string>

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {\
    dict = dictionary;
    if(!boardText.size()) {
        // if the boardText is empty, make the array
        string rd;
        for(int i = 0; i < 16; i++){
            string middle = CUBES[i];
            int idx = randomInteger(0, 5);
            cout << idx;
            rd += middle.substr(idx, 1);
            boardText = shuffle(rd);
        }
    }
    // initial the gameboard
    gameboard.resize(4, 4);
    mark.resize(4, 4);
    // store the gameboard
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            gameboard[i][j] = boardText[(i*4) + j];
            mark[i][j] = 0;
        }
    }

//    cout << gameboard << endl;
    // TODO: implement
}

char Boggle::getLetter(int row, int col) {
    char x  = gameboard[row][col];
    return x;   // remove this
}

bool Boggle::checkWord(string word) {
    if(dict.containsPrefix(word)) {
        return true;
    } else {
        return false;
    }

}

bool Boggle::checkLetter(int row, int col) {
    if((row >= 0) && (row < 4) && (col >= 0) && (col < 4)) {
        return true;
    } else {
        return false;
    }

}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    if(word.size() >=4 && dict.contains(word) ){
        return true;   // remove this
    } else {
        return false;
    }
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return 0;   // remove this
}

void Boggle::computerWordSearchHelper(Set<string>& result, string words, int row, int col) {
    // TODO: implement
//    cout << words << endl;
    if(!mark[row][col]){
        if(checkWord(words)){
            mark[row][col] = 1;
            if(checkLetter(row , col + 1)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row , col + 1);
            }
            if(checkLetter(row , col - 1)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row , col - 1);
            }
            if(checkLetter(row +1 , col)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row +1 , col);
            }
            if(checkLetter(row +1 , col + 1)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row + 1 , col + 1);
            }
            if(checkLetter(row +1 , col - 1)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row + 1 , col - 1);
            }
            if(checkLetter(row -1 , col)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row - 1 , col);
            }
            if(checkLetter(row -1 , col + 1)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row - 1 , col + 1);
            }
            if(checkLetter(row -1 , col - 1)) {
                computerWordSearchHelper(result, words + getLetter(row, col), row - 1 , col - 1);
            }

        }

        if(words.size() >=4 && dict.contains(words) ){
            result.add(words);
        }
        mark[row][col] = 0;
    }


}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement

    Set<string> result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            string words = {};
            computerWordSearchHelper(result, words, i, j);
        }
    }
  // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement

    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            out << boggle.gameboard[i][j];
        }
        out << endl;
    }
    // TODO: implement
    return out;
}

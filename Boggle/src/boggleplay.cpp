// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "shuffle.h"
#include <string>
#include "shuffle.h"
//shuffle(array, length);
#include "random.h"
//randomInteger(0, 6);
#include <cctype>
//isalpha(ch);
#include "simpio.h"
//getYesOrNo(“Do you want to eat cake? ”);
#include "Boggle.h"

using namespace std;

void showClear() {
    cout << "==================== (console cleared) ====================" << endl;
}

string getboardText() {
    while(1) {
      string boardText = getLine("Type the 16 letters to appear on the board:");
        if(boardText.size() == 16) {
            int x = 0;
            for(int i = 0; i < 16; i++){
                if(!isalpha(boardText[i])) {
                   x++;
                }
            }
            if(!x) {
             return boardText;
            }

        }
        cout << "That is not a valid 16-letter board string. Try again." << endl;
    }

}

void showYourTurn(Lexicon& dictionary) {
    cout << "It's your turn!" << endl;
    string boardText = getboardText();

    Boggle boggle(dictionary, boardText);
    cout << boggle << endl;
    Set<string> res = boggle.computerWordSearch();
    cout << res;

}

void showYourTurnRandom(Lexicon& dictionary) {
    cout << "It's your turn!" << endl;
    string boardText = {};

    Boggle boggle(dictionary, boardText);
    cout << boggle << endl;
    Set<string> res = boggle.computerWordSearch();
    cout << res;
}

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    if (getYesOrNo("Do you want to generate a random board?")) {
        showClear();
        showYourTurnRandom(dictionary);
    } else {
        showClear();
        showYourTurn(dictionary);
    }









}

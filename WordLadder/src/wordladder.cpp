// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "set.h"
#include "filelib.h"
#include "queue.h"
#include "stack.h"
#include "strlib.h"
#include "string.h"


using namespace std;
void findHelper(){


}
void getfilename(string& filename){

    // get the filename and make sure it exisit.

    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl << endl;
//    filename = getLine("Dictionary file name? ");
//    while (!fileExists(filename)) {
//        cout << "Unable to open that file.  Try again." << endl << endl;
//        filename = getLine("Dictionary file name? ");
//    }
    filename = "dictionary.txt";
    cout << endl;

}
void getword(Set<string>& dict, string& word1, string& word2 ){

    //get two words.

    word1 = getLine("Word #1 (or Enter to quit): ");
    word2 = getLine("Word #2 (or Enter to quit): ");

    while((word1.length() != word2.length()) || (!dict.contains(word1) || !dict.contains(word2)) || (word1 == word2)){
        if(word1.length() != word2.length()){
            cout << "The two words must be the same length." <<endl << endl;
            word1 = getLine("Word #1 (or Enter to quit): ");
            word2 = getLine("Word #2 (or Enter to quit): ");
        }
        if(!dict.contains(word1) || !dict.contains(word2)){
            cout << "The two words must be found in the dictionary." <<endl << endl;
            word1 = getLine("Word #1 (or Enter to quit): ");
            word2 = getLine("Word #2 (or Enter to quit): ");
        }
        if(word1 == word2){
            cout << "The two words must be different." <<endl << endl;
            word1 = getLine("Word #1 (or Enter to quit): ");
            word2 = getLine("Word #2 (or Enter to quit): ");
        }
    }

}

void getdict(Set<string>& dict, string& filename){

    // file -> set

    ifstream file;
    file.open(filename);

    string word;
    while (file >> word) {
        dict.add(word);
    }
}

void getbase(string& filename, Set<string>& dict){

    //get the base information

    getfilename(filename);
    getdict(dict, filename);
//
}

void find(Set<string>& dict, string& word1, string& word2){

    //find the solution
    dict.remove(word1);
    Queue<Stack<string>> q;
    Stack<string> st;
    st.push(word1);
    q.enqueue(st);
    Stack<string> out;
    int outcont = 0;
    int place = word1.length() - 1;

    while (!q.isEmpty() && !outcont) {

//            cout << q << endl;
        Stack<string> s = q.dequeue();
        string word_m = s.peek();

        for(int i = 0; i < 26; i++){
            for(int j = 0; j <= place; j++){
    //            cout << q <<endl;
                string word_sb = word_m.substr(0, word_m.length());

                word_sb[j] = ('a' + i);
                if(dict.contains(word_sb)){
    //                    cout << word_sb << endl;
                    dict.remove(word_sb);
                    s.push(word_sb);
                    q.enqueue(s);
    //                    cout << q << endl;
                    if(word_sb == word2){
    //                        cout << word_sb << endl;
    //                        cout << s << endl;
                        out = s;
                        outcont ++;
                    }
                    s.pop();
                }
            }
        }
    }
    dict.add(word1);
    cout << out << endl;
    cout<< "A ladder from dog back to cat:" << endl;
    cout << out << endl;
//    while(out.isEmpty()){
//        cout << out.peek() << " ";
//        out.
//    }
}

int main() {
    // TODO: Finish the program!


    string filename;
    Set<string> dict;
    string word1, word2;
    getbase(filename, dict);

    while(1){
         getdict(dict, filename);
        getword(dict, word1, word2);
        if ((word1 == "byebye") || (word2 == "byebye")){
            break;
        }
        find(dict, word1, word2);

    }






    cout << "Have a nice day." << endl;
    return 0;
}

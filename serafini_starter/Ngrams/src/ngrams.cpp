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
#include "random.h"

using namespace std;



void getfilename(string& filename){

    // get the filename and make sure it exisit.

    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl << endl;
    filename = "cisneros.txt";
    cout << endl;

}
void getvalue(int& value){

    //get Value of N?.

    value = getInteger("Value of N? ");

}
void getnum(int& num){

    //get random words to generate.

    num = getInteger("# of random words to generate (0 to quit)? ");

}


void getdict(Map<Vector<string>, Vector<string>>& map, Vector<Vector<string>>& keymap, string& filename, int& value){

    // file -> map

    ifstream file;
    file.open(filename);

    string word;
    int caut = 1;
    Vector<string> v1;
    Vector<string> v2;
    Vector<string> vm;
    v2.add("");
    // remember the front word
    Vector<Vector<string>> frist;
//    Vector<string> second;
    while (file >> word) {
        if(caut < value){
            // make enough number of the dist
            v1.add(word);
             // remember the front word
            Vector<string> second;
            second.add(word);
            frist.add(second);

        } else{

            if (map.containsKey(v1)){
                 // if cotains, add behind the value
                vm = map[v1];
                vm.add(word);
                map.put(v1, vm);
            } else{
                // if not
//                cout<< v1 <<endl;
                keymap.add(v1);
                v2[0] = word;
                map.put(v1, v2);
            }
//            cout<< v1 <<endl;
            v1.add(word);
            v1.remove(0);

        }
        caut++;

    }
    for(int i = 0; i < value - 1; i++){
        // add the words in the front
//        cout<< v1 <<endl;
        if (map.containsKey(v1)){
            vm = map[v1];
            vm.add(frist[i][0]);
            map.put(v1, vm);
        } else{
            map.put(v1, frist[i]);
            keymap.add(v1);
        }
        v1.add(frist[i][0]);
        v1.remove(0);
    }

//    cout << map << endl;
//    cout << keymap << endl;

}

void getbase(Map<Vector<string>, Vector<string>>& map, Vector<Vector<string>>& keymap, string& filename, int& value, int& num){

    //get the base information

    getfilename(filename);
    getvalue(value);
    getnum(num);
    getdict(map, keymap, filename, value);
//
}
void generte(Map<Vector<string>, Vector<string>>& map, Vector<Vector<string>>& keymap, int& value, int& num){

    int begin = randomInteger(0, map.size() - 1);
    int numall = num - 2;
    Vector<string> now;
    string ns;
    Vector<string> next;
    cout<< "... ";
    for(int i = 0; i < numall; i++){
        if(i <= 0){
            Vector<string> v = keymap[begin];
            for(int j = 0; j < value - 1; j++){
                cout << v[j] << " ";
                now.add(v[j]);
            }
            next = map[v];
            int nextProb = randomInteger(0, next.size() -1 );
            ns = next[nextProb];
//            cout << ns << endl;
            cout << ns << " ";
            now.add(ns);
            now.remove(0);
//            cout << now << endl;
        } else{
                next = map[now];
//                cout << now << endl;

//                cout << next << endl;
                int n = randomInteger(0, next.size() - 1);
                ns = next[n];
                cout << ns << " ";
                now.add(ns);
                now.remove(0);

            }
        }
    cout << "..." << endl;
}

int main() {
    // TODO: Finish the program!
    string filename;
    Map<Vector<string>, Vector<string>> map;
    Vector<Vector<string>> keymap;
    int value, num;
    getbase(map, keymap, filename, value, num);

    generte(map, keymap, value, num);

//    cout << map << endl;

    while(1){
        map.clear();
        keymap.clear();
        getbase(map, keymap, filename, value, num);
         generte(map, keymap, value, num);
        if (num <= 0){
            break;
        }
    }

    cout << "Exiting." << endl;
    return 0;
}

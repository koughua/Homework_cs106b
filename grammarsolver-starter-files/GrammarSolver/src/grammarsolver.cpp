/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "map.h"
#include "random.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
//Vector<string> stringSplit(string s, string delimiter) {
//    Vector<string> output = {"qweqeqweqeqweqeqweqeqw" "eqweqeqweqeqeqeq"};
//    return output;
//}

Map<string, string> MapGenerate(istream& input) {

    string str;
    Vector<string> v1, v2, v3;
    Map<string, string> m;
    while(getline(input, str)) {
         v1 = stringSplit(str, "::=");
         m[v1[0]] = v1[1];
    }
    return m;
}

string OutputGenerateHelper(Map<string, string> m, string symbol) {
    string out, output;
    Vector<string> v = stringSplit(symbol, "|");

    int x =randomInteger(0, v.size() - 1);
    Vector<string> v1 = stringSplit(v[x], " ");
    for(int i = 0; i < v1.size(); i++) {

        if (m.containsKey(v1[i])) {
            out = OutputGenerateHelper(m, m[v1[i]]);
        } else {
            out = v1[i];
            }
        output += (" " + trim(out));
        }

    return output;
}


string OutputGenerate(Map<string, string> m, string symbol) {
    string output;

    if(m.containsKey(symbol)){
        string middle = m[symbol];
        output = OutputGenerateHelper(m, middle);
    } else {
        output = symbol;
    }


    return output;

}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function
    Map<string, string> m = MapGenerate(input);


    Vector<string> output;
    for(int i = 0; i < times; i++) {

        string str = trim(OutputGenerate(m, symbol));
        output.add(str);

    }

    return output;           // This is only here so it will compile
}

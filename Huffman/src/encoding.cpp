// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "HuffmanNode.h"
#include "pqueue.h"
#include "filelib.h"
// TODO: include any other headers you need

Map<int, int> buildFrequencyTable(istream& input) {

    Map<int, int> freqTable;
    char ch;
    while(input.get(ch)) {
        freqTable[ch]++;
    }
    freqTable[PSEUDO_EOF]++;
    return freqTable;

}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // initialize the parameters
    HuffmanNode* EncodingTree = new HuffmanNode;
    PriorityQueue<HuffmanNode*> pq;
    Vector<int> keys = freqTable.keys();
    Vector<int> values = freqTable.values();

    // store the map to the priority queue
    for(int i = 0; i < freqTable.size(); i++) {
        HuffmanNode* EncodingTrees = new HuffmanNode(keys[i], values[i]);
        pq.enqueue(EncodingTrees, values[i]);
    }

    // make the encoding tree, the last one is the tree we need
    while(pq.size() > 1){
        EncodingTree = pq.dequeue();
        HuffmanNode* EncodingTree0 = EncodingTree;
        EncodingTree = pq.dequeue();
        HuffmanNode* EncodingTree1 = EncodingTree;
        EncodingTree = new HuffmanNode(NOT_A_CHAR, EncodingTree0->count + EncodingTree1->count,EncodingTree0, EncodingTree1);
        pq.enqueue(EncodingTree, EncodingTree->count);
    }

     // dequeue the last HuffmanNode
    EncodingTree = pq.dequeue();

    return EncodingTree;
}

Map<int, string> buildEncodingMapHelper(HuffmanNode* encodingTree, Map<int, string> encodingMap, string code) {

    if(encodingTree->zero != nullptr) {
        encodingMap = buildEncodingMapHelper(encodingTree->zero, encodingMap, code + "0");
    }

    if(encodingTree->one != nullptr) {
        encodingMap = buildEncodingMapHelper(encodingTree->one, encodingMap, code + "1");
    }
    if(encodingTree->character != NOT_A_CHAR) {
        encodingMap[encodingTree->character] = code;
    }
    return encodingMap;
}



Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    string code = "";
    encodingMap = buildEncodingMapHelper(encodingTree, encodingMap, code);
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {

    char ch;
    while(input.get(ch)) {
        string str = encodingMap[ch];
        int strl = str.size();
        for(int i = 0; i < strl; i++) {
          output.writeBit(str[i] - 48);
        }
    }

    string str = encodingMap[PSEUDO_EOF];
    int strl = str.size();
    for(int i = 0; i < strl; i++) {
      output.writeBit(str[i] - 48);
    }
}

void decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // recursive to print the decoder string.
    char ch;
    if((encodingTree->one ==nullptr) && (encodingTree->zero ==nullptr)) {

        if(encodingTree->character != PSEUDO_EOF) {
            ch = encodingTree->character;
            output << ch;
        } else {
            // store with entire 8 bits!!!!!!!!!!!
            // if come to the EOF, release all the ibistream!!!!!!!!!
            while(!input.fail()) {
                input.readBit();
            }
        }
    } else {
        if(!input.readBit()) {
            decodeDataHelper(input, encodingTree->zero, output);
        } else {
            decodeDataHelper(input, encodingTree->one, output);
        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    while(!input.fail()) {
        decodeDataHelper(input, encodingTree, output);
    }
}

void compress(istream& input, obitstream& output) {
    Map<int, int>FrequencyTable = buildFrequencyTable(input);
    HuffmanNode* EncodingTree = buildEncodingTree(FrequencyTable);
    Map<int, string> EncodingMap = buildEncodingMap(EncodingTree);
    output << FrequencyTable;
    rewindStream(input);
    encodeData(input, EncodingMap, output);


}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    Map<int, int>FrequencyTable;
    input >> FrequencyTable;
    HuffmanNode* EncodingTree = buildEncodingTree(FrequencyTable);
    decodeData(input, EncodingTree, output);
}

void freeTree(HuffmanNode* node) {
    if(node == nullptr) {
        return;
    }
    freeTree(node->zero);
    freeTree(node->one);

    delete node;


//    if(node != nullptr) {
//        if(node->zero != nullptr) {
//            freeTree(node->zero);
//        }
//        if(node->one != nullptr) {
//            freeTree(node->one);
//        }
//        delete node;
//    }
}

#include "huffman.h"
#include <fstream>
#include <iostream>
#include <queue>


using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f): ch(c),  freq(f), left(nullptr),right(nullptr){}
};

struct Compare {
    bool opretaor()(Node* a, Node* b){
        return a->freq > b->freq;
    }
};

void HuffmanTree(){

}
void compressFile(){

}
void decompressFile(){

}

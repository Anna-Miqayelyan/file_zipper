#include "huffman.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>


using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f): ch(c),  freq(f), left(nullptr),right(nullptr){}
};

struct Compare {
    bool operator()(Node* a, Node* b){
        return a->freq > b->freq;
    }
};

void HuffmanTree(Node* root , string str, unordered_map<char,string>& table){
    if(!root) 
    return;
    if(!root->left && !root->right) {
        table[root->ch]=str;
    }
    HuffmanTree(root->left,str + "0",table);
    HuffmanTree(root->right,str + "1",table);
    

}

void compressFile(string& inputPath,string &outputPath){
    ifstream in(inputPath);
    ofstream out(outputPath);

    unordered_map<char,int> freq;
    string text;




    char ch;
    while(in.get(ch)){
        text+=ch;
        freq[ch]++;
    }
    priority_queue<Node* ,vector<Node*>,Compare> pq;
    for(auto& pair : freq){
        pq.push(new Node(pair.first,pair.second));
    }

    while (pq.size()>1){
        Node * left= pq.top(); 
        pq.pop();
        Node* right=pq.top(); 
        pq.pop();
        Node* parent= new Node('\0',left->freq+right->freq);
        parent->left=left;
        parent->right=right;
        pq.push(parent);
    }

    Node* root=pq.top();


    unordered_map<char,string> table;
    HuffmanTree(root,"",table);
   


    out<<freq.size()<<'\n';
    for (auto& pair : freq) {
        out << (int)pair.first << ' ' << pair.second << '\n'; 
    }
    string encodedTect;
    for(char c :text){
        encodedTect+=table[c];
    }
    while (encodedTect.size()%8!=0)
             encodedTect+="0";

             for (size_t i = 0; i < encodedTect.size(); i += 8) {
                bitset<8> bits(encodedTect.substr(i, 8));  
                char byte = (char)bits.to_ulong();
                out.write(&byte, 1);
            }
            in.close(); out.close(); 
            cout << "File compressed to: " << outputPath << endl;
}
void decompressFile(string& inputPath, string& outputPath){
    ifstream in(inputPath, ios::binary);
    ofstream out(outputPath);

    int numChars;

    in>>numChars;
    unordered_map<char,int> freq;



    for(int i=0;i<numChars;i++){
        int ch,f;
        in>>ch>>f;
        freq[(char)ch]=f;

    }
    in.get();
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();



    string encodedText;
    char byte;
    while (in.read(&byte, 1)) {
        bitset<8> bits(byte);
        encodedText += bits.to_string();  


        Node* node = root;
        for (char bit : encodedText) {
            node = (bit == '0') ? node->left : node->right;
            if (!node->left && !node->right) { 
                out << node->ch; 
                node = root; 
            }
        }
    
    }




}

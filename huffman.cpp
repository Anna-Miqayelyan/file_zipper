#include "huffman.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>


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

void HuffmanTree(Node* root , std::string str, std::unordered_map<char,std::string>& table){
    if(!root) 
    return;
    if(!root->left && !root->right) {
        table[root->ch]=str;
    }
    HuffmanTree(root->left,str + "0",table);
    HuffmanTree(root->right,str + "1",table);
    

}

void compressFile(const std::string& inputPath,const std::string& outputPath){
    std::ifstream in(inputPath);
   std:: ofstream out(outputPath,std::ios::binary);

   std:: unordered_map<char,int> freq;
   std:: string text;




    char ch;
    while(in.get(ch)){
        text+=ch;
        freq[ch]++;
    }
   std:: priority_queue<Node* ,std::vector<Node*>,Compare> pq;
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


    std::unordered_map<char,std::string> table;
    HuffmanTree(root,"",table);
   


    out<<freq.size()<<'\n';
    for (auto& pair : freq) {
        out << (int)pair.first << ' ' << pair.second << '\n'; 
    }
   std:: string encodedTect;
    for(char c :text){
        encodedTect+=table[c];
    }
    while (encodedTect.size() % 8 !=0)  {
         encodedTect += "0";
        }
    
        size_t paddingBits = (8 - encodedTect.size() % 8) % 8;
       out.write(reinterpret_cast<const char*>(&paddingBits), sizeof(size_t));


    for (size_t i = 0; i < encodedTect.size(); i += 8) {
                std::bitset<8> bits(encodedTect.substr(i, 8));  
                char byte = (char)bits.to_ulong();
                out.write(&byte, 1);
            }


            in.close(); out.close(); 
           std:: cout << "File compressed to: " << outputPath <<std:: endl;
}
void decompressFile(const std::string& inputPath, const std::string& outputPath){
    std::ifstream in(inputPath, std::ios::binary);
    std::ofstream out(outputPath);

    int numChars;

    in>>numChars;
   std:: unordered_map<char,int> freq;



    for(int i=0;i<numChars;i++){
        int ch,f;
        in>>ch>>f;
        freq[(char)ch]=f;

    }
    in.get();
    std::priority_queue<Node*,std:: vector<Node*>, Compare> pq;
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



    std::string encodedText;
    char byte;
    while (in.read(&byte, 1)) {
       std:: bitset<8> bits(byte);
        encodedText += bits.to_string();  

    }
        Node* node = root;
        for (char bit : encodedText) {
            node = (bit == '0') ? node->left : node->right;
            if (!node->left && !node->right) { 
                out << node->ch; 
                node = root; 
            }
        }
    
    




}

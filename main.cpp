#include "huffman.h"
#include <string>
int main(){
    std::string input = "text.txt";
    std::string compressed="compressed.hzip";
    std:: string decompressed= "output.txt";

    compressFile(input,compressed);
    decompressFile(compressed,decompressed);

    return 0;


}
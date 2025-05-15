#ifndef HUFFMAN_H
#define HUFFMAN_H



#include <string>

void compressFile(const std::string& inputPath, const std::string& outputPath);
void decompressFile( const std::string& inputPath, const std::string& outputPath);


#endif
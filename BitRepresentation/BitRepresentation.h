#ifndef _BITREPRESENTATION_H_
#define _BITREPRESENTATION_H_

#include <string>
#include <vector>

using namespace std;

template <typename T>
class BitRepresentation {
public:
    BitRepresentation(T number);
    BitRepresentation(vector<bool> v);
    string getBinary();
    string getHexadecimal();
    void setBit(unsigned int location);
    void unsetBit(unsigned int location);
    bool isBitSet(unsigned int location);
    T getNumber();
    
private:
    T data;
};

#include "BitRepresentation.cpp"
#endif

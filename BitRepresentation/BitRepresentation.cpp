#include "BitRepresentation.h"
#include <string>
#include <sstream>
using namespace std;

template <typename T>
BitRepresentation <T> :: BitRepresentation(T number) : data(number) {};

template <typename T>
BitRepresentation<T> :: BitRepresentation(vector<bool> v){
    data = 0;
    
    if(v.size() > sizeof(T) * 8){
        for(int i = (v.size()-1); i >= (v.size() - sizeof(T) * 8); i--){
            if(v[i]){
                v[i] = 1;
            }
            else{
                v[i] = 0;
            }
            data = data | (v[i] << v.size()-i-1);
        }
    }
    
    for(int i = (v.size()-1); i < sizeof(T) * 8; i--){
        if(v[i]){
            v[i] = 1;
        }
        else{
            v[i] = 0;
        }
        data = data | (v[i] << v.size()-i-1);
    }
}

template <typename T>
string BitRepresentation<T> :: getBinary(){
    string str;
    
    for (int j = (sizeof(T) * 8) -1; j >= 0; --j){
        if (data >> j & 1){
            str += '1';
        }
        else {
            str += '0';
        }
    }
    return str;
}

template <typename T>
string BitRepresentation<T> :: getHexadecimal(){
    string hex_str;
    stringstream ss;
    ss << hex << data;
    hex_str = ss.str();
    
    for (int i=0; i < hex_str.length(); i++){
        if (hex_str[i] >= 'a' && hex_str[i] <= 'z'){
            hex_str[i]  = hex_str[i] - 32;
        }
    }
    
    while (hex_str.length() < sizeof(T)*2){
        hex_str = '0' + hex_str;
    }
    return hex_str;
    
}

template <typename T>
void BitRepresentation<T> :: setBit(unsigned int location){
    if (!((data >> location) & 1)){
        data = data | (1 << location);
    }
}

template <typename T>
void BitRepresentation<T> :: unsetBit(unsigned int location){
    if ((data >> location) & 1){
        data = data ^ (1 << location);
    }
}

template <typename T>
bool BitRepresentation<T> :: isBitSet(unsigned int location){
    if(location >= sizeof(T)*8){
        return false;
    }
    else{
        if ((data >> location) & 1){
            return true;
        }
        else{
            return false;
        }
    }
}

template <typename T>
T BitRepresentation<T> :: getNumber(){
    return data;
}

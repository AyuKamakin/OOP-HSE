#include "packofcoins.h"
#include <cstdint>
#include <cstring>
#define maxInt 2147483646
#define minInt 1
#define maxLen 10

void PackOfCoins::setCoinsSize() {
    int n=price;
    size=0;
    size+=(int)n/100;
    n=n%100;
    size+=(int)n/50;
    n=n%50;
    size+=(int)n/10;
    n=n%10;
    size+=(int)n/5;
    n=n%5;
    size+=n;
}

PackOfCoins::PackOfCoins(const char *newName, const int32_t &newPrice) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(newPrice>=minInt&&newPrice<maxInt) {
        price = newPrice;
        setCoinsSize();
    }
    else {
        size=0;
        price=0;
    }
    innerSetValue();}

PackOfCoins::PackOfCoins(const char *newName) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    price=0;
    size=0;
}
int8_t PackOfCoins::setInfo(const char *newName, const int32_t &newSize, const int32_t &newPrice) {
    if(strlen(strdup(newName))<=maxLen && strcmp(newName,"")!=0)name = strdup(newName);
    else return 1;
    if(newPrice>=1&&newPrice<maxInt){
        price = newPrice;
        setCoinsSize();
        innerSetValue();
    }
    else return 2;
    return 0;
}
int8_t PackOfCoins::setInfo(const char *newName, const int32_t &newPrice) {
    if(strlen(strdup(newName))<=maxLen&& strcmp(newName,"")!=0)name = strdup(newName);
    else return 1;
    if(newPrice>=1&&newPrice<maxInt){
        price = newPrice;
        setCoinsSize();
    }
    else return 2;
    innerSetValue();
    setCoinsSize();
    return 0;
}
bool PackOfCoins::setPrice(const int32_t &newPrice) {
    if(newPrice>=minInt&&newPrice<maxInt){
        price = newPrice;
        setCoinsSize();
    }
    else return 0;
}

const bool PackOfCoins::type() const {return 1;}

PackOfCoins::PackOfCoins() {
    price=0;
    size=0;
    name="";
}



#ifndef UNTITLED4_PACKOFCOINS_H
#define UNTITLED4_PACKOFCOINS_H


#include <cstdint>
#include "Package.h"

class PackOfCoins: public Package {
public:
    PackOfCoins();
    //PackOfCoins(const char* newName, const int32_t& newSize, const int32_t& newPrice){};
    PackOfCoins(const char* newName, const int32_t& newPrice);;
    PackOfCoins(const char* newName);;
    void setInfo(const char *newName, const int32_t &newSize, const int32_t &newPrice);;
    void setInfo(const char *newName, const int32_t &newPrice);;
    void setPrice(const int32_t& newPrice);
    virtual const bool type() const;;

private:
    void setCoinsSize();
};


#endif //UNTITLED4_PACKOFCOINS_H

#ifndef UNTITLED4_PACKOFCOINS_H
#define UNTITLED4_PACKOFCOINS_H
#include <cstdint>
#include "package.h"

class PackOfCoins: public Package {
public:
    PackOfCoins();
    //PackOfCoins(const char* newName, const int32_t& newSize, const int32_t& newPrice){};
    PackOfCoins(const char* newName, const int32_t& newPrice);;
    PackOfCoins(const char* newName);;
    int8_t setInfo(const char *newName, const int32_t &newSize, const int32_t &newPrice) override;;
    int8_t setInfo(const char *newName, const int32_t &newPrice);;
    bool setPrice(const int32_t& newPrice);
    virtual const bool type() const;;

private:
    void setCoinsSize();
};


#endif //UNTITLED4_PACKOFCOINS_H

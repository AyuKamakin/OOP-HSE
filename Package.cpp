#include <iostream>
#include <cstring>
#include "Package.h"
#include <fstream>

#define DEBUG 0
#define maxLen 10
#define maxInt 2147483646
#define minInt 1
using namespace std;
Package::Package() {
    price=0;
    size=0;
}
bool check(const int32_t& n){
    if(n>=minInt&&n<maxInt) return true;
    else return false;
}
Package::Package(const char *newName, const int32_t &newSize, const int32_t &newPrice) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(check)size = newSize;
    else size=0;
    if(check)price = newPrice;
    else price=0;
    innerSetValue();
}

Package::Package(const char *newName, const int32_t &newSize) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(check)size = newSize;
    else size=0;
    price=0;
    value=0;
}

Package::Package(const char *newName) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    price = 0;
    size=0;
    value=0;
}

Package::Package(const Package &ref) {
    name = ref.name;
    price = ref.price;
    size =ref.size;
    innerSetValue();
}

Package::~Package() {
#if DEBUG==1
    cout<<"called destructor for "<<name<<endl;
#endif
}

void Package::setInfo(const char *newName, const int32_t &newSize, const int32_t &newPrice) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(check)size = newSize;
    else size=0;
    if(check)price = newPrice;
    else price=0;
    innerSetValue();
}

void Package::setName(const char *newName) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
}

void Package::setSize(const int32_t &newSize) {
    if(check)size = newSize;
    else size=0;
    innerSetValue();

}

void Package::setPrice(const int32_t &newPrice) {
    if(check)price = newPrice;
    else price=0;
    innerSetValue();
}

const char *Package::getName() const {
    if(name!=NULL)return name;
    else return "";
}
const int32_t &Package::getSize() const { return size;}

const int32_t &Package::getPrice() const { return price;}

const float& Package::getValue() const{
    return (value);
}
void Package::innerSetValue() {
    if(size==0) value=0;
    else value=(float)price/(float)size;
}


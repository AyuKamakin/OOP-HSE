#include <iostream>
#include <cstring>
#include "Package.h"
#define DEBUG 0
#define maxLen 10
#define maxFloat 1000
#define minFloat 0
using namespace std;
Package::Package() {
    price=0;
    size=0;
}

Package::Package(const char *newName, const float &newSize, const float &newPrice) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(newSize>minFloat&newSize<maxFloat)size = newSize;
    else size=0;
    if(newPrice>minFloat&newPrice<maxFloat)price = newPrice;
    else price=0;
}

Package::Package(const char *newName, const float &newSize) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(newSize>minFloat&newSize<maxFloat)size = newSize;
    else size=0;
    price=0;
}

Package::Package(const char *newName) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    price = 0;
    size=0;
}

Package::Package(const Package &ref) {
    name = ref.name;
    price = ref.price;
    size =ref.size;
}

Package::~Package() {
#if DEBUG==1
    cout<<"called destructor for "<<name<<endl;
#endif
}

void Package::setInfo(const char *newName, const float &newSize, const float &newPrice) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(newSize>minFloat&newSize<maxFloat)size = newSize;
    else size=0;
    if(newPrice>minFloat&newPrice<maxFloat)price = newPrice;
    else price=0;
}

void Package::setName(const char *newName) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
}

void Package::setSize(const float &newSize) {
    if(newSize>minFloat&newSize<maxFloat)size = newSize;
    else size=0;
}

void Package::setPrice(const float &newPrice) {
    if(newPrice>minFloat&newPrice<maxFloat)price = newPrice;
    else price=0;
}

const char *Package::getName() const {
    if(name!=NULL)return name;
    else return "";
}

const float &Package::getSize() const { return size;}

const float &Package::getPrice() const { return price;}


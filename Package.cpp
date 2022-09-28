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
}

Package::Package(const char *newName, const int32_t &newSize) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(check)size = newSize;
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

void Package::setInfo(const char *newName, const int32_t &newSize, const int32_t &newPrice) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
    if(check)size = newSize;
    else size=0;
    if(check)price = newPrice;
    else price=0;
}

void Package::setName(const char *newName) {
    if(strlen(strdup(newName))<=maxLen)name = strdup(newName);
    else name= nullptr;
}

void Package::setSize(const int32_t &newSize) {
    if(check)size = newSize;
    else size=0;
}

void Package::setPrice(const int32_t &newPrice) {
    if(check)price = newPrice;
    else price=0;
}

const char *Package::getName() const {
    if(name!=NULL)return name;
    else return "";
}
const int32_t &Package::getSize() const { return size;}

const int32_t &Package::getPrice() const { return price;}

const float Package::getValue() const{
    if(size>0)return ((float)price/size);
    else return 0;
}
void Package::readFromF(const string& filename){
    ifstream file;
    file.open(filename);
    if(file.is_open()){
        string temp;
        file>>temp>>size>>price;
        name= strdup(temp.c_str());
        file.close();
    }
    return;
}
void Package::writeToF(const string& filename)const{
    ofstream file;
    file.open(filename);
    if(file.is_open()){
        file<<name<<" "<<size<<" "<<price;
        file.close();
    }
    return;

}

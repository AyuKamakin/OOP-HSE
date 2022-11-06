#ifndef UNTITLED_PACKAGE_H
#define UNTITLED_PACKAGE_H
#include <cstdint>
using namespace std;
class Package
{
    friend class Node;
    friend class List;
protected:
    int32_t price;
    int32_t size;
    float value=0;
    char *name = nullptr;
    void innerSetValue();
public:
    //конструкторы по умолчанию
    Package();
    Package(const char* newName, const int32_t& newSize, const int32_t& newPrice);
    Package(const char* newName, const int32_t& newSize);
    Package(const char* newName);
    //конструктор копирования
    Package(const Package &ref);
    //деструктор
    ~Package();

     // методы класса
    virtual int8_t setInfo(const char* newName, const int32_t& newSize, const int32_t& newPrice);
    bool setName(const char* newName);
    const char* getName() const;
    const int32_t& getSize() const;
    const int32_t& getPrice() const;
    const float& getValue() const;
    void Print() const;;

    virtual const bool type()const ;
};


#endif //UNTITLED_PACKAGE_H

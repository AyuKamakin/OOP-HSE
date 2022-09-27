#ifndef UNTITLED_PACKAGE_H
#define UNTITLED_PACKAGE_H
using namespace std;
class Package
{
protected:
    float price;
    float size;
    char *name = nullptr;
public:
    //конструкторы по умолчанию
    Package();
    Package(const char* newName, const float& newSize, const float& newPrice);
    Package(const char* newName, const float& newSize);
    Package(const char* newName);
    //конструктор копирования
    Package(const Package &ref);
    //деструктор
    ~Package();
    // методы класса
    void setInfo(const char* newName, const float& newSize, const float& newPrice);
    void setName(const char* newName);
    void setSize(const float& newSize);
    void setPrice(const float& newPrice);
    const char* getName() const;
    const float& getSize() const;
    const float& getPrice() const;
    const double& getValue() const;
};

#endif //UNTITLED_PACKAGE_H

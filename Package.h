#ifndef UNTITLED_PACKAGE_H
#define UNTITLED_PACKAGE_H
using namespace std;
class Package
{
protected:
    int32_t price;
    int32_t size;
    char *name = nullptr;
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
    void setInfo(const char* newName, const int32_t& newSize, const int32_t& newPrice);
    void setName(const char* newName);
    void setSize(const int32_t& newSize);
    void setPrice(const int32_t& newPrice);
    const char* getName() const;
    const int32_t& getSize() const;
    const int32_t& getPrice() const;
    const float getValue() const;
    void readFromF(const string filename);
    void writeToF(const string filename) const;
};

#endif //UNTITLED_PACKAGE_H

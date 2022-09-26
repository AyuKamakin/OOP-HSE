#include <iostream>
#include "Package.h"
#define UNTITLED_LIST_H
using namespace std;
struct node{
    Package data;
    node * next, * prev;
    float value;
};
class List
{
protected:
    node * first, * last;
    int len;

public:
    List();;
    List(const List& L);;
    ~List();;
    void Del(const int pos);
    void Destruction();;
    int GetLen() const;;
    node* GetElem(int pos) const;;
    void Insert(const Package n,const int pos);;
    void Insert(const Package n);
    void Print() const;;
    void Print(int pos) const;;
};

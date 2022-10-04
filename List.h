#include <iostream>
#include "Package.h"
#include "Node.h"
#define UNTITLED_LIST_H
using namespace std;

class List
{
protected:
    Node* first;
    Node* last;
    int len;
public:
    List();;
    List(const List& L);;
    ~List();;
    void Del(const int& pos);;
    void Destruction();;

    const int& GetLen() const;;
    Node* Head() const;;
    Node* Tail() const;;
    Node* GetElem(const int& pos) const;;

    void Insert(const Package& n);;
    void InsertBetween(const Package& n, const int& pos1, const int& pos2);;
    void InsertWSort(const Package& n);;

    void FromFile(const string& filename);;
    void ToFile(const string& filename);;


    void Print(const int& pos) const;;

    void Sort() const;;
    bool IfSorted() const;;
};

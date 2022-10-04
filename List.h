#include <iostream>
#include "Package.h"
#define UNTITLED_LIST_H
using namespace std;

class List
{
public: class Node {
        friend class Package;
    protected:
        Node* innext= nullptr;
        Node* inprev= nullptr;
        Package data;
    public:
        Node();
        Node(const Package& temp);
        Node(const Package& temp, Node* next, Node* prev);
        Node(Node* next, Node* prev);
        ~Node();
        Node* next() const;
        Node* prev() const;
        void setNext(Node* n);;
        void setPrev(Node* n);;
        void setNextNull();;
        void setPrevNull();;
        void setPack(const Package& n);
        const Package& getPack();
        const bool ifNext();
        const bool ifPrev();
    };
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

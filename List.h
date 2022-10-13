#include <iostream>
#include "Package.h"
#define UNTITLED_LIST_H
using namespace std;

class List
{
public:
    friend class Iterator;
    class Node {
        friend class Package;
        friend class Iterator;
    public:
        Node* innext= nullptr;
        Node* inprev= nullptr;
        Package data;
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
        const bool ifNext() const;
        const bool ifPrev() const;
    };
protected:
    Node* first;
    Node* last;
    int len;

     class Iterator {
        Node *curr;
    public:
        Iterator(Node *fir) {
            this->curr = fir;
        }
        Iterator(){
            curr= nullptr;
        }
//перегрузки операторов
        Node *operator*();

        Node &operator++();

        Node &operator--(int);

         const Package& getPack();;
         void setPack(const Package &n);
         const bool ifNext();;
         const bool ifPrev();;
         void setNext(Iterator n);;
         void setPrev(Iterator n);;
         void setNextNull();;
         void set(Node* n);
         void setPrevNull();;
         Node * next() const;
         Node* prev() const;
     };

public:
    List();;
    List(const List& L);;
    ~List();;
    void del(const int& pos);;
    void destruction();;

    const int& getLen() const;;
    Node* head() const;;
    Node* tail() const;;;
    Node* getElem(const int& pos) const;;

    void add(const Package& n);;
    void insertBetween(const Package& n, const int& pos1, const int& pos2);;
    void insertWSort(const Package& n);;

    void fromFile(const string& filename);;
    void toFile(const string& filename);;


    void Print(const int& pos) const;;

    void sort() const;;
    bool ifSorted() const;;
};

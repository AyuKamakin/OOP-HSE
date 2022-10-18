#include <iostream>
#include "Package.h"
#include "PackOfCoins.h"
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
        Package *data;
        Node();
        Node(Package* temp);
        ~Node();
        Node* next() const;
        Node* prev() const;
        void setNext(Node* n);;
        void setPrev(Node* n);;
        void setNextNull();;
        void setPrevNull();;
        void setPack(Package* n);
        const Package* getPack();
        const bool ifNext() const;
        const bool ifPrev() const;
        const int32_t& getSize() const;
        const int32_t &getPrice() const;
        const char *getName() const;
        const float &getValue() const;
        const bool getType()const;;
    };
protected:
    Node* first;
    Node* last;
    int len;
public:
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

        const Package* getPack()const;;
        const int32_t& getSize() const;
        const int32_t &getPrice() const;
        const char *getName() const;
        const float &getValue() const;
        void setPack(Package* n);
        const bool ifNext()const;;
        const bool ifPrev() const;
        void setNext(Iterator n);
        void setPrev(Iterator n);
        void setNextNull();
        void set(Node* n);
        void setPrevNull();
        bool getType()const;
    };

public:
    List();;
    List(const List& L);; //доделано
    ~List();;
    void del(const int& pos);;
    void destruction();;

    const int& getLen() const;;
    Node* head() const;;
    Node* tail() const;;;
    Node* getElem(const int& pos) const;;

    bool add(Package*);;
    bool insertBetween(Package *n, const int& pos1, const int& pos2);
    bool insertWSort(Package* n);;

    bool fromFile(const string& filename);;//доделано
    void toFile(const string& filename) const;;//доделано

    bool Print(const int& pos) const;;//доделано

    void sort();

    bool ifSorted() const;
};

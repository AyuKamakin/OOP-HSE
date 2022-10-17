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
        Package data;
        PackOfCoins data2;
        int8_t typeOfData;
        Node();
        Node(const Package& temp);
        Node(const PackOfCoins& temp);
        ~Node();
        Node* next() const;
        Node* prev() const;
        void setNext(Node* n);;
        void setPrev(Node* n);;
        void setNextNull();;
        void setPrevNull();;
        void setPack(const Package& n);
        void setPack(const PackOfCoins& n);
        const Package& getPack();
        const PackOfCoins& getCoins();;
        const bool ifNext() const;
        const bool ifPrev() const;
        const int32_t& getSize() const;
        const int32_t &getPrice() const;
        const char *getName() const;
        const float &getValue() const;
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

        const Package& getPack()const;;
        const PackOfCoins& getCoins()const;
        const int32_t& getSize() const;
        const int32_t &getPrice() const;
        const char *getName() const;
        const float &getValue() const;
        void setPack(const Package &n);
        const bool ifNext()const;;
        const bool ifPrev() const;;
        void setNext(Iterator n);;
        void setPrev(Iterator n);;
        void setNextNull();;
        void set(Node* n);
        void setPrevNull();;
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

    bool add(const Package& n);;
    bool add(const PackOfCoins& n);;//доделано
    bool insertBetween(const Package& n, const int& pos1, const int& pos2);;
    bool insertBetween(const PackOfCoins& n, const int& pos1, const int& pos2);;//доделано

    bool insertWSort(const Package& n);;
    bool insertWSort(const PackOfCoins& n);; //доделано

    bool fromFile(const string& filename);;//доделано
    void toFile(const string& filename) const;;//доделано

    bool Print(const int& pos) const;;//доделано


    void sort();;//доделать

    bool ifSorted() const;;//доделано
private:
    void insertBetweenBase(Node *temp, const int &pos1, const int &pos2);

    void addBase(Node *temp);

    void insertWSortBase(Node *temp);
};

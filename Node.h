#ifndef UNTITLED4_NODE_H
#define UNTITLED4_NODE_H
#include <iostream>
#include <fstream>
#include "Package.h"
#include <cstring>

class Node {
friend class Package;
private:
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


#endif //UNTITLED4_NODE_H

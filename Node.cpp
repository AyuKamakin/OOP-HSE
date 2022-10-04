#include "Node.h"

Node::Node() {
    innext= 0;
    inprev= 0;
}

Node::Node(const Package& temp) {
    innext= nullptr;
    inprev= nullptr;
    data=temp;
}

Node::Node(const Package &temp, Node *next, Node *prev) {
    innext= next;
    inprev= prev;
    data=temp;
}

Node::Node(Node *next, Node *prev) {
    innext= next;
    inprev= prev;
    data=NULL;
}

Node *Node::next() const {
    return innext;
}

Node *Node::prev() const {
    return inprev;
}

Node::~Node() {

}

const Package &Node::getPack() {
    return data;
}

 const bool Node::ifPrev() {
    if(inprev!=0) return 1;
    else return 0;
}

 const bool Node::ifNext() {
    if(innext!=0) return 1;
    else return 0;
}

void Node::setNext(Node *n) {
    innext=n;
}

void Node::setPrev(Node *n) {
    inprev=n;
}

void Node::setNextNull() {
    innext= 0;
}

void Node::setPrevNull() {
    inprev= 0;
}

void Node::setPack(const Package &n) {
    data=n;
}


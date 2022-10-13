#include <iostream>
#include <fstream>
#include "Package.h"
#include "List.h"
#include <cstring>

#define DEBUG 0
using namespace std;

//конструкторы по умолчанию и копирования
List::List() {
    first = last = NULL;
    len = 0;
}

List::List(const List &L) {
    first = last = NULL;
    len = 0;
    if (L.len == 0) return;
    Node *temp = L.first;
    while (temp->ifNext()) {
        add(temp->getPack());
        temp = temp->next();
    }
    add(temp->getPack());

}

//деструктор
List::~List() {
    destruction();
}

void List::fromFile(const string &filename) {
    ifstream file;
    file.open(filename);
    string name;
    int32_t size, price;
    Package temp;
    while (file >> name >> size >> price) {
        temp.setInfo(name.c_str(), size, price);
        add(temp);
    }
    file.close();
}

void List::toFile(const string &filename) {
    if(len==0) return;
    ofstream file;
    file.open(filename);
    Node *temp = first;
    if (file.is_open()) {
        while (temp != 0) {
            file << temp->getPack().getName() << " " << temp->getPack().getSize() << " " << temp->getPack().getPrice()
                 << "\n";
            temp = temp->next();
        }
    }
    file.close();
}

void List::destruction() {
    while (len != 0) del(1);
}

void List::del(const int &pos) {
    if (pos < 1 || pos > len) return;
    if (len == 1) {
        delete first;
        len--;

    } else {
        if (pos == 1) {
            Node *to = first->next();
            to->setPrevNull();
            delete first;
            first = to;
        } else if (pos == len) {
            Node *to = last->prev();
            to->setNextNull();
            delete last;
            last = to;
        } else {
            Node *toDelete = first;
            for (int i = 1; i < pos; i++) {
                toDelete = toDelete->next();
            }
            Node *pred = toDelete->prev();
            Node *nex = toDelete->next();
            delete toDelete;
            pred->setNext(nex);
            nex->setPrev(pred);
        }
        len--;
    }
}

//вывод количества эл-тов, элементов или элемента
const int &List::getLen() const {
    return len;
}


void List::Print(const int &pos) const {
    if (pos < 1 || pos > len) {
#if DEBUG == 1
        cout << "Incorrect position\n";
#endif
        return;
    }
    Node *temp;
    if (pos <= len / 2) {
        temp = first;
        for (int i = 1; i < pos; i++) {
            temp = temp->next();
        }
    } else {
        temp = last;
        for (int i = 1; i <= len - pos; i++) {
            temp = temp->prev();
        }
    }
    cout << "size " << temp->getPack().getSize() << ", price " << temp->getPack().getPrice() << ", value "
         << temp->getPack().getValue() << endl;

}

//Добавление элемента
void List::add(const Package &n) {
    if (!strcmp(n.getName(), "")) return;
    Node *temp = new Node(n);
    temp->setNextNull();
    if (len == 0) {
        first = temp;
        temp->setPrevNull();
    } else {
        temp->setPrev(last);
        last->setNext(temp);
    }
    last = temp;
    len++;
}

void List::insertBetween(const Package &n, const int &pos1, const int &pos2) {
    if (pos1 == pos2 || pos2 - pos1 > 1 || pos1 < 0
        || pos2 < 1 || pos1 > len - 1 || pos2 > len || !strcmp(n.getName(), ""))
        return;
    Node *temp = new Node(n);
    if (pos1 == 0) {
        first->setPrev(temp);
        temp->setNext(first);
        temp->setPrevNull();
        first = temp;
    } else {
        temp->setPrev(getElem(pos1));
        temp->setNext(getElem(pos1)->next());
        getElem(pos1)->next()->setPrev(temp);
        getElem(pos1)->setNext(temp);
    }
    len++;
}

void List::insertWSort(const Package &n) {
    if (!strcmp(n.getName(), "")) return;
    Node *temp = new Node(n);
    if (len == 0) {
        first = last = temp;
        temp->setNextNull();
        temp->setPrevNull();
    } else if (len == 1) {
        if (temp->getPack().getValue() > first->getPack().getValue()) {
            first->setNext(temp);
            temp->setPrev(first);
            temp->setNextNull();
            last = temp;
        } else {
            last = first;
            first = temp;
            temp->setNext(last);
            temp->setPrevNull();
            last->setNextNull();
            last->setPrev(temp);
        }
    } else {
        if (temp->getPack().getValue() <= first->getPack().getValue()) {
            temp->setNext(first);
            temp->setPrevNull();
            first = temp;
        } else if (temp->getPack().getValue() >= last->getPack().getValue()) {
            last->setNext(temp);
            temp->setNextNull();
            temp->setPrev(last);
            last = temp;
        } else {
            Node *curr = first;
            Node *ncurr = curr->next();
            while (!(curr->getPack().getValue() <= temp->getPack().getValue() &&
                     ncurr->getPack().getValue() >= temp->getPack().getValue())) {
                curr = ncurr;
                ncurr = curr->next();
            }
            temp->setPrev(curr);
            temp->setNext(ncurr);
            curr->setNext(temp);
            ncurr->setPrev(temp);
        }
    }
    len++;
}

//получение конкретного элемента
List::Node *List::getElem(const int &pos) const {
    if (pos < 1 || pos > len) return 0;
    Node *curr = first;
    int i = 1;
    while (i < pos && curr != 0) {
        curr = curr->next();
        i++;
    }
    if (curr == 0) return 0;
    else return curr;
}

List::Node *List::head() const {
    return first;
}

List::Node *List::tail() const {
    return last;
}

bool List::ifSorted() const {
    Node *temp = first;
    while (temp->ifNext()) {
        if (temp->next()->getPack().getValue() < temp->getPack().getValue()) return 0;
        temp = temp->next();
    }
    return 1;
}

void List::sort() const {
    Node *curr = first;
    Node *ncurr = first->next();
    Package temp = Package(ncurr->getPack());
    ncurr->setPack(curr->getPack());
    curr->setPack(temp);
    curr = ncurr;
    ncurr = ncurr->next();
    while (!ifSorted()) {
        if (ncurr->getPack().getValue() < curr->getPack().getValue()) {
            temp = ncurr->getPack();
            ncurr->setPack(curr->getPack());
            curr->setPack(temp);
        }
        if (ncurr->ifNext()) {
            curr = ncurr;
            ncurr = ncurr->next();
        } else {
            curr = first;
            ncurr = first->next();
        }
    }
}

void GetFromFile(const string &s) {
    ifstream file;
    file.open("toFrom");
    Package temp = Package();
    char *a;
    float b;
    float c;
    while (file.is_open()) file >> b >> c >> a;
    file.close();
}

List::Node::Node() {
    innext= 0;
    inprev= 0;
}

List::Node::Node(const Package& temp) {
    innext= nullptr;
    inprev= nullptr;
    data=temp;
}

List::Node::Node(const Package &temp, Node *next, Node *prev) {
    innext= next;
    inprev= prev;
    data=temp;
}

List::Node::Node(Node *next, Node *prev) {
    innext= next;
    inprev= prev;
    data=NULL;
}

List::Node *List::Node::next() const {
    return innext;
}

List::Node* List::Node::prev() const {
    return inprev;
}

List::Node::~Node() {

}

const Package& List::Node::getPack() {
    return data;
}

const bool List::Node::ifPrev() const {
    if(inprev!=0) return 1;
    else return 0;
}

const bool List::Node::ifNext() const {
    if(innext!=0) return 1;
    else return 0;
}

void List::Node::setNext(Node *n) {
    innext=n;
}

void List::Node::setPrev(Node *n) {
    inprev=n;
}

void List::Node::setNextNull() {
    innext= 0;
}

void List::Node::setPrevNull() {
    inprev= 0;
}

void List::Node::setPack(const Package &n) {
    data=n;
}
//функции класса Iterator

List::Node &List::Iterator::operator--(int) {
    this->curr = this->curr->inprev;
    return *this->curr;
}

List::Node &List::Iterator::operator++() {
    this->curr = this->curr->innext;
    return *this->curr;
}

List::Node *List::Iterator::operator*() { return curr; }

const Package &List::Iterator::getPack() {
    return curr->data;
}

List::Node *List::Iterator::next() const {
    return curr->innext;
}

List::Node *List::Iterator::prev() const {
    return curr->inprev;
}

void List::Iterator::setPrevNull() {
    curr->inprev= 0;
}

void List::Iterator::setNextNull() {
    curr->innext= 0;
}

void List::Iterator::setPrev(List::Iterator n) {
    curr->inprev=n.curr;
}

void List::Iterator::setNext(List::Iterator n) {
    curr->innext=n.curr;
}

const bool List::Iterator::ifPrev() {
    if(curr->inprev!=0) return 1;
    else return 0;
}

const bool List::Iterator::ifNext() {
    if(curr->innext!=0) return 1;
    else return 0;
}

void List::Iterator::setPack(const Package &n) {
    curr->data=n;
}

void List::Iterator::set(List::Node *n) {
    curr=n;
}

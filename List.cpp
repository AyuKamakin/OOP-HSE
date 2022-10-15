#include <iostream>
#include <fstream>
#include "Package.h"
#include "PackOfCoins.h"

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
        if (temp->typeOfData == 1) add(temp->getPack());
        else if (temp->typeOfData == 2) add(temp->getCoins());
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
    int8_t type;
    Package temp;
    PackOfCoins temp2;
    while (file >> name >> size >> price >> type) {
        if (type == 1) {
            temp.setInfo(name.c_str(), size, price);
            add(temp);
        } else if (type == 2) {
            temp2.setInfo(name.c_str(), price);
            add(temp2);
        }
    }
    file.close();
}

void List::toFile(const string &filename) {
    if (len == 0) return;
    ofstream file;
    file.open(filename);
    Node *temp = first;
    if (file.is_open()) {
        while (temp != 0) {
            file << temp->getName() << " " << temp->getSize() << " " << temp->getPrice()
                 << " " << temp->typeOfData << "\n";
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
    cout << "name " << temp->getName() << " size " << temp->getSize() << ", price " << temp->getPrice() << ", value "
         << temp->getValue() << endl;

}

//Добавление элемента
void List::add(const Package &n) {
    if (!strcmp(n.getName(), "")) return;
    Node *temp = new Node(n);
    addBase(temp);

}

void List::add(const PackOfCoins &n) {
    if (!strcmp(n.getName(), "")) return;
    Node *temp = new Node(n);
    addBase(temp);
}

void List::addBase(Node *temp) {
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
    insertBetweenBase(temp, pos1, pos2);

}

void List::insertBetween(const PackOfCoins &n, const int &pos1, const int &pos2) {
    if (pos1 == pos2 || pos2 - pos1 > 1 || pos1 < 0
        || pos2 < 1 || pos1 > len - 1 || pos2 > len || !strcmp(n.getName(), ""))
        return;
    Node *temp = new Node(n);
    insertBetweenBase(temp, pos1, pos2);
}

void List::insertBetweenBase(Node *temp, const int &pos1, const int &pos2) {
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
    insertWSortBase(temp);

}

void List::insertWSort(const PackOfCoins &n) {
    if (!strcmp(n.getName(), "")) return;
    Node *temp = new Node(n);
    insertWSortBase(temp);
}

void List::insertWSortBase(Node *temp) {
    if (len == 0) {
        first = last = temp;
        temp->setNextNull();
        temp->setPrevNull();
    } else if (len == 1) {
        if (temp->getValue() > first->getValue()) {
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
        if (temp->getValue() <= first->getValue()) {
            first->setPrev(temp);
            temp->setNext(first);
            temp->setPrevNull();
            first = temp;
        } else if (temp->getValue() >= last->getValue()) {
            last->setNext(temp);
            temp->setNextNull();
            temp->setPrev(last);
            last = temp;
        } else {
            Node *curr = first;
            Node *ncurr = curr->next();
            while (!(curr->getValue() <= temp->getValue() &&
                     ncurr->getValue() >= temp->getValue())) {
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
        if (temp->next()->getValue() < temp->getValue()) return 0;
        temp = temp->next();
    }
    return 1;
}

void List::sort() {
    Node *curr = first;
    Node *ncurr = first->next();
    while(!ifSorted()) {

        if (ncurr->getValue() < curr->getValue()) {
            if (curr->ifPrev()&&ncurr->ifNext()) {
                curr->prev()->setNext(ncurr);
                ncurr->setPrev(curr->prev());
                curr->setNext(ncurr->next());
                ncurr->next()->setPrev(curr);
                ncurr->setNext(curr);
                curr->setPrev(ncurr);
                curr=ncurr;
                ncurr=ncurr->next();
            }
            else if (curr==first) {
                curr->setNext(ncurr->next());
                ncurr->next()->setPrev(curr);
                curr->setPrev(ncurr);
                ncurr->setNext(curr);
                ncurr->setPrevNull();
                first = ncurr;
                curr = first->next();
                ncurr = curr->next();

            }
            else if (ncurr==last) {
                last = curr;
                curr->setNextNull();
                ncurr->setPrev(curr->prev());
                ncurr->prev()->setNext(ncurr);
                curr->setPrev(ncurr);
                ncurr->setNext(curr);
                curr = first;
                ncurr = first->next();
            }
        }
        else{
            if(ncurr!=last){
            curr=ncurr;
            ncurr=ncurr->next();
            }
            else{
                curr=first;
                ncurr=first->next();
            }
        }

    }
}


List::Node::Node() {
    innext = 0;
    inprev = 0;
    typeOfData = 0;
}

List::Node::Node(const Package &temp) {
    innext = nullptr;
    inprev = nullptr;
    data = temp;
    typeOfData = 1;
}

List::Node::Node(const PackOfCoins &temp) {
    innext = nullptr;
    inprev = nullptr;
    data2 = temp;
    typeOfData = 2;
}

List::Node *List::Node::next() const {
    return innext;
}

List::Node *List::Node::prev() const {
    return inprev;
}

List::Node::~Node() {

}

const Package &List::Node::getPack() {
    if (typeOfData == 1)return data;
    else return NULL;
}

const PackOfCoins &List::Node::getCoins() {
    if (typeOfData == 2)return data2;
    else return NULL;
}

const bool List::Node::ifPrev() const {
    if (inprev != 0) return 1;
    else return 0;
}

const bool List::Node::ifNext() const {
    if (innext != 0) return 1;
    else return 0;
}

void List::Node::setNext(Node *n) {
    innext = n;
}

void List::Node::setPrev(Node *n) {
    inprev = n;
}

void List::Node::setNextNull() {
    innext = 0;
}

void List::Node::setPrevNull() {
    inprev = 0;
}

void List::Node::setPack(const Package &n) {
    if (typeOfData == 0 || typeOfData == 1)data = n;
    if (typeOfData == 0) typeOfData = 1;
}

void List::Node::setPack(const PackOfCoins &n) {
    if (typeOfData == 0 || typeOfData == 2)data2 = n;
    if (typeOfData == 0) typeOfData = 2;
}

/*const PackOfCoins &List::Node::getCoins() {
    if(typeOfData==2)return data2;
}*/

const int32_t &List::Node::getSize() const {
    if (typeOfData == 1)return data.getSize();
    else return data2.getSize();
}

const int32_t &List::Node::getPrice() const {
    if (typeOfData == 1)return data.getPrice();
    else return data2.getPrice();
    //else return NULL;

}

const char *List::Node::getName() const {
    if (typeOfData == 1)return data.getName();
    else return data2.getName();
    //else return "";
}

const float &List::Node::getValue() const {
    if (typeOfData == 1)return data.getValue();
    else return data2.getValue();
    //else { float temp=0; return temp;};
}
//функции класса Iterator

List::Node &List::Iterator::operator--(int) {
    this->curr = this->curr->prev();
    return *this->curr;
}

List::Node &List::Iterator::operator++() {
    this->curr = this->curr->next();
    return *this->curr;
}

List::Node *List::Iterator::operator*() { return curr; }

const Package &List::Iterator::getPack() {
    return curr->data;
}

const PackOfCoins &List::Iterator::getCoins() {
    return curr->data2;
}

void List::Iterator::setPrevNull() {
    curr->setNextNull();
}

void List::Iterator::setNextNull() {
    curr->setNextNull();
}

void List::Iterator::setPrev(List::Iterator n) {
    curr->setPrev(n.curr);
}

void List::Iterator::setNext(List::Iterator n) {
    curr->setNext(n.curr);
}

const bool List::Iterator::ifPrev() {
    return curr->ifPrev();
}

const bool List::Iterator::ifNext() {
    return curr->ifNext();
}

void List::Iterator::setPack(const Package &n) {
    curr->setPack(n);
}

void List::Iterator::set(List::Node *n) {
    curr = n;
}

const int32_t &List::Iterator::getSize() const {
    return curr->getSize();
}

const int32_t &List::Iterator::getPrice() const {
    return curr->getPrice();
}

const char *List::Iterator::getName() const {
    return curr->getName();
}

const float &List::Iterator::getValue() const {
    return curr->getValue();
}



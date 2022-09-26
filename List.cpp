#include <iostream>
#include "Package.h"
#include "List.h"
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
    node * temp = L.first;
    while(temp != 0){
        Insert(temp->data,1);
        temp = temp->next;
    }
}

//деструктор
List::~List() {
 Destruction();
}
void List::Destruction(){
    while(len != 0) Del(1);
}
void List::Del(const int pos) {
    if(pos < 1 || pos > len){
#if DEBUG==1
        cout << "Incorrect position !!!\n";
#endif
        return;
    }
    node *toDelete = first;
    for(int i=1;i < pos;i++){
        toDelete = toDelete->next;
    }
    node *prev = toDelete->prev;
    node *next = toDelete->next;
    if(prev!= 0 && len != 1) prev->next = next;
    if(next!= 0 && len != 1) next->prev = prev;
    if(pos == 1) first = next;
    if(pos == len) last = prev;
    delete toDelete;
    len--;
}

//вывод количества эл-тов, элементов или элемента
int List::GetLen() const {
    return len;
}

void List::Print() const{
    if(len != 0){
        node * temp = first;
        cout << "( ";
        while(temp->next != 0){
            cout << temp->data.getName() << ", ";
            temp = temp->next;
        }
        cout << temp->data.getName() << " )\n";
    }
}

void List::Print(int pos) const {
    if(pos < 1 || pos > len){
#if DEBUG==1
        cout << "Incorrect position\n";
#endif
        return;
    }
    node * temp;
    if(pos <= len / 2){
        temp = first;
        for(int i=1;i<pos;i++){
            temp = temp->next;
        }
    }
    else{
        temp = last;
        for(int i=1;i <= len - pos;i++){
            temp = temp->prev;
        }
    }
    cout << pos << " element: ";
    cout << temp->data.getName() << endl;
}

//Добавление элемента
void List::Insert(const Package n) {
    node * temp = new node;
    temp->next = 0;
    temp->data = n;
    temp->prev = last;
    if(last != 0) last->next = temp;
    if(len == 0) first = last = temp;
    else last = temp;
    len++;
}
void List::Insert(const Package n, const int pos) {
    if(pos == len + 1){
        Insert(n);
        return;
    }
    else if(pos == 1){
        node * temp = new node;
        temp->prev = 0;
        temp->data = n;
        temp->next = first;
        if(first != 0) first->prev = temp;
        if(len == 0) first = last = temp;
        else first = temp;
        len++;
        return;
    }
    node * Ins = first;
    for(int i=1;i < pos;i++){
        Ins = Ins->next;
    }
    node * PrevIns = Ins->prev;
    node * temp = new node;
    temp->data=n;
    if(PrevIns != 0 && len != 1) PrevIns->next = temp;
    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;
    len++;
}

node *List::GetElem(int pos) const {
    node *curr = first;
    if(pos < 1 || pos > len){
#if DEBUG==1
        cout << "Incorrect position !!!\n";
#endif
        return 0;
    }
    int i = 1;
    while(i < pos && curr != 0){
        curr = curr->next;
        i++;
    }
    if(curr == 0) return 0;
    else return curr;
}




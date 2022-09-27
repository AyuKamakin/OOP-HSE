#include <iostream>
#include <fstream>
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
    node *temp = L.first;
    while (temp != 0) {
        InsertWSort(temp->data);
        temp = temp->next;
    }
}

//деструктор
List::~List() {
    Destruction();
}
void List::FromFile(const string filename){
    ifstream file;
    file.open(filename);
    string name;
    int32_t size, price;
    Package temp;
    while(file>>name>>size>>price){
        temp.setInfo(name.c_str(),size,price);
        InsertWSort(temp);
    }
    file.close();
}
void List::ToFile(const string filename) {
    ofstream file;
    file.open(filename);
    node* temp=first;
    if(file.is_open()) {
        while (temp != 0) {
            file << temp->data.getName() <<" "<< temp->data.getSize() <<" "<< temp->data.getPrice()<<"\n";
            temp = temp->next;
        }
    }
    file.close();
}
void List::Destruction() {
    while (len != 0) Del(1);
}

void List::Del(const int pos) {
    if (pos < 1 || pos > len) {
#if DEBUG == 1
        cout << "Incorrect position !!!\n";
#endif
        return;
    } else if (len == 1) {
        delete first;
        len--;
    } else {
        node *toDelete = first;
        for (int i = 1; i < pos; i++) {
            toDelete = toDelete->next;
        }
        node *prev = toDelete->prev;
        node *next = toDelete->next;
        if (prev != 0 && len != 1) prev->next = next;
        if (next != 0 && len != 1) next->prev = prev;
        if (pos == 1) first = next;
        if (pos == len) last = prev;
        delete toDelete;
        len--;
    }
}

//вывод количества эл-тов, элементов или элемента
const int &List::GetLen() const {
    return len;
}

void List::Print() const {
    if (len != 0) {
        node *temp = first;
        int i = 1;
        while (temp->next != 0) {
            cout << "num " << i << ": " << temp->data.getName() << ", size " <<
                 temp->data.getSize() << ", price " << temp->data.getPrice() << ", value " << temp->data.getValue()
                 << endl;
            temp = temp->next;
            i++;
        }
        cout << "num " << i << ": " << temp->data.getName() << ", size " <<
             temp->data.getSize() << ", price " << temp->data.getPrice() << ", value " << temp->data.getValue() << endl;
    }
}

void List::Print(int pos) const {
    if (pos < 1 || pos > len) {
#if DEBUG == 1
        cout << "Incorrect position\n";
#endif
        return;
    }
    node *temp;
    if (pos <= len / 2) {
        temp = first;
        for (int i = 1; i < pos; i++) {
            temp = temp->next;
        }
    } else {
        temp = last;
        for (int i = 1; i <= len - pos; i++) {
            temp = temp->prev;
        }
    }
    cout << "size " << temp->data.getSize() << ", price " << temp->data.getPrice() << ", value "
         << temp->data.getValue() << endl;

}

//Добавление элемента
void List::Insert(const Package n) {
    node *temp = new node;
    temp->next = 0;
    temp->data = n;
    temp->prev = last;
    if (last != 0) last->next = temp;
    if (len == 0) first = last = temp;
    else last = temp;
    len++;
}

void List::Insert(const Package n, const int pos) {
    if (pos == len + 1) {
        Insert(n);
        return;
    } else if (pos == 1) {
        node *temp = new node;
        temp->prev = 0;
        temp->data = n;
        temp->next = first;
        if (first != 0) first->prev = temp;
        if (len == 0) first = last = temp;
        else first = temp;
        len++;
        return;
    }
    node *Ins = first;
    for (int i = 1; i < pos; i++) {
        Ins = Ins->next;
    }
    node *PrevIns = Ins->prev;
    node *temp = new node;
    temp->data = n;
    if (PrevIns != 0 && len != 1) PrevIns->next = temp;
    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;
    len++;
}

void List::InsertWSort(const Package n) {
    node *temp = new node;
    temp->data = n;
    if (len == 0) {
        first = last = temp;
        temp->next = 0;
        temp->prev = 0;
    } else if (len == 1) {
        if (temp->data.getValue() > first->data.getValue()) {
            first->next = temp;
            temp->prev = first;
            temp->next = 0;
            last = temp;
        } else {
            last = first;
            first = temp;
            temp->next = last;
            temp->prev = 0;
            last->next = 0;
            last->prev = temp;
        }
    } else {
        if (temp->data.getValue() <= first->data.getValue()) {
            temp->next = first;
            temp->prev = 0;
            first = temp;
        } else if (temp->data.getValue() >= last->data.getValue()) {
            last->next = temp;
            temp->next = 0;
            temp->prev = last;
            last = temp;
        } else {
            node *curr = first;
            node *ncurr = curr->next;
            while (!(curr->data.getValue() <= temp->data.getValue() &&
                     ncurr->data.getValue() >= temp->data.getValue())) {
                curr = ncurr;
                ncurr = curr->next;
            }
            temp->prev = curr;
            temp->next = ncurr;
            curr->next = temp;
            ncurr->prev = temp;
        }
    }
    len++;
}

node *List::GetElem(int pos) const {
    node *curr = first;
    if (pos < 1 || pos > len) {
        return 0;
    }
    int i = 1;
    while (i < pos && curr != 0) {
        curr = curr->next;
        i++;
    }
    if (curr == 0) return 0;
    else return curr;
}

node *List::Head() const {
    return first;
}
node *List::Tail() const {
    return last;
}
bool List::IfSorted() const {
    node *temp = first;
    while (temp->next != 0) {
        if (temp->next->data.getValue() < temp->data.getValue()) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

void List::Sort() const {
    node *curr = first;
    node *ncurr = first->next;
    Package temp = Package(ncurr->data.getName(), ncurr->data.getSize(), ncurr->data.getPrice());
    ncurr->data.setInfo(curr->data.getName(), curr->data.getSize(), curr->data.getPrice());
    curr->data.setInfo(temp.getName(), temp.getSize(), temp.getPrice());
    curr = ncurr;
    ncurr = ncurr->next;
    while (!IfSorted()) {
        if (ncurr->data.getValue() < curr->data.getValue()) {
            temp.setInfo(ncurr->data.getName(), ncurr->data.getSize(), ncurr->data.getPrice());
            ncurr->data.setInfo(curr->data.getName(), curr->data.getSize(), curr->data.getPrice());
            curr->data.setInfo(temp.getName(), temp.getSize(), temp.getPrice());
        }
        if (ncurr->next != 0) {
            curr = ncurr;
            ncurr = ncurr->next;
        }
        else{
            curr = first;
            ncurr = first->next;
        }
    }
}
void GetFromFile(const string s){
    ifstream file;
    file.open("toFrom");
    Package temp=Package();
    char* a;
    float b;
    float c;
    while(file.is_open()){
        file>>b>>c>>a;
    }
    file.close();
}


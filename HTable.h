#include <functional>
#include <cstdint>
#include <string>
#include <vector>
#include <list>

using namespace std;
#define STARTSIZE 1000

template<typename K, typename V>
class HTable {
public:
    struct hList {
        V value;
        K key;
        hList *next = nullptr;
    };

    HTable() {
        count = 0;
        sum = 0;
        hashConst = 1;
        table.resize(STARTSIZE);
    };

    HTable(const HTable &other) {
        table.resize(other.table.size());
        hashConst = other.hashConst;
        int i = 0;
        sum = 0;
        count = 0;
        while (i < other.table.size()) {
            if (other.table[i] != nullptr) {
                //insert(other.table[i]->key,other.table[i]->value);
                auto *newNode = new hList;
                newNode->key = other.table[i]->key;
                newNode->value = other.table[i]->value;
                sum += other.table[i]->value;
                count++;
                table[i] = newNode;
                if (other.table[i]->next != nullptr) {
                    auto ref = other.table[i];
                    auto prev = newNode;
                    while (ref->next != nullptr) {
                        ref = ref->next;
                        auto *nNode = new hList;
                        nNode->key = ref->key;
                        nNode->value = ref->value;
                        sum += nNode->value;
                        count++;
                        prev->next = nNode;
                        prev = nNode;
                    }
                } else newNode->next = nullptr;
            }
            i++;
        }
    } //готово

    ~HTable() {
        clearTable();
        table.clear();
    } // деструктор
    void clearTable() {
        for (int i = 0; i < table.size(); i++) {
            while (table[i] != nullptr) {
                auto curr = table[i];
                hList *prev = nullptr;
                while (curr->next != nullptr) {
                    prev = curr;
                    curr = curr->next;
                }
                count--;
                sum = sum - curr->value;
                if (prev != nullptr) prev->next = nullptr;
                else if (curr == table[i]) table[i] = nullptr;
                delete curr;
                curr = nullptr;
            }
        }
    } //очиститель содержимого

    void contentsCheck() {
        if (count > table.size() / 2) {
            table.resize(table.size() * 10);
            hashConst = hashConst * 10;
            for (int i = 0; i < table.size() / 10; i++) {
                if (table[i] != nullptr) {
                    table[hashPos(table[i]->key)] = table[i];
                    table[i] = nullptr;
                }
            }
        } else return;
    } //готово

    const int getPos(K key) {
        return hashPos(key);
    } //готово

    const bool inTable(K nkey) {
        if (table[hashPos(nkey)] != nullptr) {
            if (table[hashPos(nkey)]->key == nkey) {
                return true;
            } else {
                auto curr = table[hashPos(nkey)];
                while (curr->key != nkey && curr->next != nullptr) {
                    curr = curr->next;
                }
                if (curr->key == nkey) return true;
                else return false;
            }
        } else return false;
    }// готово
    /*const bool inTable(K nkey, int pos) {
        if (table[pos] != nullptr) {
            if (table[pos]->key == nkey) {
                return true;
            } else {
                auto curr = table[pos];
                while (curr->key != nkey && curr->next != nullptr) {
                    curr = curr->next;
                }
                if (curr->key == nkey) return true;
                else return false;
            }
        } else return false;
    } */
    const bool isEmpty(int pos) {
        if (table[pos] == nullptr) return true;
        else return false;
    }//готово

    const int hashPos(K key) const {
        return abs(static_cast<int>(std::hash<K>()(key) % (STARTSIZE * hashConst)));
    } //готово

    int insert(K nkey, V data) {
        int pos = hashPos(nkey);
        auto *newNode = new hList;
        newNode->value = data;
        newNode->key = nkey;
        newNode->next = nullptr;
        if (table[pos] == nullptr) {
            table[pos] = newNode;
            count++;
            contentsCheck();
            sum += data;
            return pos;
        } else if (table[pos]->key == nkey) {
            delete newNode;
            return 0;
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (curr->key == nkey) {
                    delete newNode;
                    return 0;
                } else curr = curr->next;
            }
            if (curr->next == nullptr && curr->key != nkey) {
                curr->next = newNode;
                sum += data;
                count++;
                contentsCheck();
                return 2;
            }
        }
    } // готово
    int insertByPos(K nkey, V data, int pos) {
        auto *newNode = new hList;
        newNode->value = data;
        newNode->key = nkey;
        newNode->next = nullptr;
        if (table[pos] == nullptr) {
            table[pos] = newNode;
            count++;
            sum += data;
            return pos;
        } else if (table[pos]->key == nkey) {
            delete newNode;
            return 0;
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (curr->key == nkey) {
                    delete newNode;
                    return 0;
                } else curr = curr->next;
            }
            if (curr->next == nullptr && curr->key != nkey) {
                curr->next = newNode;
                sum += data;
                return 2;
            }
        }
    }

    int8_t removePair(K nkey) {
        int pos = hashPos(nkey);
        if (table[pos] == nullptr) {
            return 0;
        } else {
            auto curr = table[pos];
            hList *prev = nullptr;
            while (curr->next != nullptr && curr->key != nkey) {
                prev = curr;
                curr = curr->next;
            }
            if (curr->key == nkey) {
                if (curr->next == nullptr) {
                    if (prev != nullptr) prev->next = nullptr;
                    else table[pos] = nullptr;
                } else {
                    if (prev != nullptr) prev->next = curr->next;
                    else table[pos] = curr->next;
                }
                sum = sum - curr->value;
                delete curr;
                count--;
                return 1;
            }
        }
    }//готово
    int8_t removePairByPos(K nkey, int pos) {
        if (table[pos] == nullptr) {
            return 0;
        } else {
            auto curr = table[pos];
            hList *prev = nullptr;
            while (curr->next != nullptr && curr->key != nkey) {
                prev = curr;
                curr = curr->next;
            }
            if (curr->key == nkey) {
                if (curr->next == nullptr) {
                    if (prev != nullptr) prev->next = nullptr;
                    else table[pos] = nullptr;
                } else {
                    if (prev != nullptr) prev->next = curr->next;
                    else table[pos] = curr->next;
                }
                sum = sum - curr->data;
                delete curr;
                count--;
                return 1;
            }
        }
    }// готово
    const int getCount() const {
        return count;
    }// готово

    const int getSum() const {
        return sum;
    }// готово
/*
    const V &getV(K nkey) const {
        int pos = hashPos(nkey);
        if (table[pos]->key == nkey) {
            return table[pos]->value;
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (curr->key == nkey) {
                    return curr->value;
                }
                curr = curr->next;
            }
        }
    }// готово
    */
    const V &getVbypos(int pos, K nkey) {
        if (table[pos]->key == nkey) {
            return table[pos]->value;
        } else {
            auto curr = table[pos];
            while (curr->key != nkey && curr->next != nullptr) {
                curr = curr->next;
            }
            if (curr->key == nkey) return curr->value;
            else return 0;
        }
    }// готово

    V &operator[](const K &nkey) {
        int pos = hashPos(nkey);
        if (table[pos] != nullptr) {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (curr->key == nkey) {
                    return curr->value;
                }
                curr = curr->next;
            }
            if (curr->key != nkey) {
                throw std::exception();
            }
        }
        throw std::exception();
    }

    bool operator==(const HTable &other) {
       if (count == other.count && table.size() == other.table.size() && sum == other.sum) {
            for(int i=0;i<table.size();i++) {
                if (table[i] != nullptr) {
                    auto curr = table[i];
                    while (curr != nullptr) {
                   if (other.table[hashPos(table[i]->key)] == nullptr ||
                      other.table[hashPos(table[i]->key)]->value != table[i]->value) return false;
                     curr=curr->next;
                     }
                }
          }
            return true;
        } else return false;
    } // готово

public:
    vector<hList *> table;
    std::size_t count;
    int sum;
    int16_t hashConst;
};

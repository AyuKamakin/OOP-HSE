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

    HTable(const HTable &other) {};

    ~HTable() {

    }

    void clearTable() {
        table.clear();
        count = 0;
    }

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
    }

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
    const bool inTable(K nkey, int pos) {
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
    } //готово
    const bool isEmpty(int pos) {
        if (table[pos] == nullptr) return true;
        else return false;
    }

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
    } // готово
    int insert(K nkey, V data, int pos) {
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
    } // готово



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
                delete curr;
                count--;
                return 1;
            }
        }
    }//готово
    int8_t removePair(K nkey, int pos) {
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
public:
    vector<hList *> table;
    std::size_t count;
    int sum;
    int16_t hashConst;
};

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
        V *value = nullptr;
        K *key = nullptr;
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
            for (int i = 0; i < table.size / 10; i++) {
                if (table[i] != nullptr) {
                    table[hashPos(*(table[i]->key))] = table[i];
                    table[i] = nullptr;
                }
            }
            return;
        } else return;
    }

    const int hashPos(K key) const {
        return abs(static_cast<int>(std::hash<K>()(key) % (STARTSIZE * hashConst)));
    }

    int insert(K nkey, V data) {
        int pos = hashPos(nkey);
        auto *newNode = new hList;
        auto *dat = new V;
        auto *k = new K;
        *k = nkey;
        *dat = data;
        newNode->value = dat;
        newNode->key = k;
        newNode->next = nullptr;
        if (table[pos] == nullptr) {
            table[pos] = newNode;
            count++;
            sum += data;
            return pos;
        } else if (*(table[pos]->key) == nkey) {
            delete newNode;
            delete dat;
            delete k;
            return 0;
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (*(curr->key) == nkey) {
                    delete newNode;
                    return 0;
                } else curr = curr->next;
            }
            if (curr->next == nullptr && *(curr->key) != nkey) {
                curr->next = newNode;
                sum += data;
                return 2;
            }
        }
    }

    int8_t inserttest(K nkey, V data, const int pos) {

        auto *newNode = new hList;
        auto *dat = new V;
        auto *k = new K;
        *k = nkey;
        *dat = data;
        newNode->value = dat;
        newNode->key = k;
        newNode->next = nullptr;
        if (table[pos] == nullptr) {
            table[pos] = newNode;
            count++;
            sum += data;
            return pos;
        } else if (*(table[pos]->key) == nkey) {
            delete newNode;
            delete dat;
            delete k;
            return 0;
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (*(curr->key) == nkey) {
                    delete newNode;
                    delete dat;
                    delete k;
                    return 0;
                } else curr = curr->next;
            }
            if (curr->next == nullptr && *(curr->key) != nkey) {
                curr->next = newNode;
                sum += data;
                return 2;
            }
        }
    }

    int8_t removePair(K nkey) {
        int pos = hashPos(nkey);
        if (table[pos] == nullptr) {
            return 1;
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (*(table[pos]->key) == nkey) {
                    if (table[pos]->next == nullptr) {
                        delete table[pos];
                        table[pos] = nullptr;
                    } else {
                        auto next = table[pos]->next;
                        delete table[pos];
                        table[pos] = next;
                    }
                    count--;
                    return 0;
                }
            }
        }
    }

    const int getCount() const {
        return count;
    }

    const int getSum() const {
        return sum;
    }

    const V &getV(K nkey) const {
        int pos = hashPos(nkey);
        if (*(table[pos]->key) == nkey) {
            return *(table[pos]->value);
        } else {
            auto curr = table[pos];
            while (curr->next != nullptr) {
                if (*(curr->key) == nkey) {
                    return *(curr->value);
                }
                curr = curr->next;
            }
        }
    }

    const V &getVbypos(int pos, K nkey) {
        if (*(table[pos]->key) == nkey) {
            return *(table[pos]->value);
        } else {
            auto curr = table[pos];
            while(*(curr->key)!=nkey&&curr->next!= nullptr){
                curr=curr->next;
            }
            if(*(curr->key)==nkey)  return *(curr->value);
            else return 0;
        }
    };
public:
    vector<hList *> table;
    std::size_t count;
    int sum;
    int16_t hashConst;
};

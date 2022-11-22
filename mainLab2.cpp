#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include "Package.h"
#include "PackOfCoins.h"
#include <typeinfo>
#include <cstdint>
#include <random>
#include "HTable.cpp"

using namespace std;

#define DEBUG 4
#define incorrectNum1 10000000000000000
#define incorrectNum2 -100
#define correctNum1 10
#define correctNum2 99
#define correctNum3 50
#define correctNum4 75
#define correctNum5 6843
#define correctNum6 3
#define correctNum7 5
#define correctNum8 863
#define bigNum 10000000
#define one 1
#define correctName1 "box"
#define correctName2 "fridge"
#define correctName3 "package"
#define correctName4 "What"
#define correctName5 "orange"
#define correctName6 "small"
#define coinsName1 "coins1"
#define coinsName2 "coins2"
#define coinsName3 "coins3"
#define coinsName4 "coins4"
#define incorrectName "aaaaaaaaaaaar"

#include "List.h"

int main() {
     HTable<string, int > table;
    int pos=table.insert("rererere",111);
    table.inserttest("bebebe",10,pos);
    table.insert("абдыщба", 228);

    cout<<pos<<" is position of inserted element"<<endl;
   // cout<<table.insert("rererere",111)<<" res of inserting existing element; \n 1 if inserted as new \n 0 if already exists \n 2 if collision occured & solved"<<endl;
    cout<<"sum = "<<table.getSum()<<endl;
    cout<<table.getVbypos(pos,"bebebe")<<endl;
}

#include <map>
#include <iostream>
#include "info.h"

using namespace std;

map<string,int> symMap;
Info::Info(string n, int addr, int l){
    name = n;
    address = addr;
    length = l;
}

void Info::PutIntoSymbolMap(string symbolName, int address){
    symMap.insert(pair<string, int>(symbolName, address));
}

void Info::PrintSymbolMap(){
    for (auto const& x : symMap)
    {
        std::cout <<"                      " << x.first  // string (key)
                << "                " << x.second << endl;
    }
}
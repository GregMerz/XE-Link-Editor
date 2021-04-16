#include <iostream>
#include <map>
#include <iterator>
#include <utility>

#include "estab.h"

using namespace std;
map<string,Info> Estab::hmap;
Info* info;

Estab::Estab(string name, int address, int length){
    Info i(name,address,length);
    info = &i;
    hmap.insert(pair<string, Info>(name, i));
}

void Estab::PutIntoEstab(string name, string symbolName, int address, int length){
    if(hmap.find(name) == hmap.end()){
        Info in(name, address, length);
        hmap.insert(pair<string,Info>(name,in));
        info = &in;
    }
    
    //At this point the control section name is inserted
    if(symbolName != ""){
        PutIntoSymbolMap(name, symbolName, address);
    }
}

void Estab::PutIntoSymbolMap(string name, string symbolName, int address){
    //Point to symbolMap (put it into vairable)
    Info* ff = &(hmap.at(name));
    ff->PutIntoSymbolMap(symbolName, address);
}

void Estab::PrintEstab(){
    cout << endl;

    cout << "Control Section     | Symbol Name        | Address            |Length" << endl;


    for (auto const& x : hmap)
    {
        Info infocurr = x.second;
        cout << x.first;
        cout << "                                      " << infocurr.address;
        cout << "                 " << infocurr.length << endl;
        
        infocurr.PrintSymbolMap();
    }
}

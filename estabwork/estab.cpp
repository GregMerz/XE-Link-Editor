#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <utility>

#include "estab.h"

using namespace std;
map<string,Info> Estab::hmap;
Info* info;

Estab::Estab(string name, string address, string length){
    Info i(name,address,length);
    info = &i;
    hmap.insert(pair<string, Info>(name, i));
}

void Estab::PutIntoEstab(string name, string symbolName, string address, string length){
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

void Estab::PutIntoSymbolMap(string name, string symbolName, string address){
    //Point to symbolMap (put it into vairable)
    Info* ff = &(hmap.at(name));
    ff->PutIntoSymbolMap(symbolName, address);
}

void Estab::WriteEstab(){
    ofstream myfile;
    myfile.open("name.st");

    myfile << "Control Section     | Symbol Name        | Address            |Length" << endl;
    myfile.close();
    for (auto const& x : hmap)
    {
        myfile.open("name.st", ios::app);
        Info infocurr = x.second;
        myfile << x.first;
        myfile << "                                      " << infocurr.address;
        myfile << "                 " << infocurr.length << endl;
        myfile.close();
        infocurr.WriteSymbolMap();
    }
}

void Estab::PrintEstab(){
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

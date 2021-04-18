#include <map>
#include <iostream>
#include <fstream>
#include "info.h"

using namespace std;

map<string,string> symMap;
Info::Info(string n, string addr, string l){
    name = n;
    address = addr;
    length = l;
}

void Info::PutIntoSymbolMap(string symbolName, string address){
    symMap.insert(pair<string, string>(symbolName, address));
}

void Info::PrintSymbolMap(){
    for (auto const& x : symMap)
    {
        std::cout <<"                      " << x.first  // string (key)
                << "                " << x.second << endl;
    }
}

void Info::WriteSymbolMap(){
    ofstream myfile;
    myfile.open("name.st", ios::app);
    for (auto const& x : symMap)
    {
        myfile <<"                      " << x.first  // string (key)
               << "                " << x.second << endl;
    }
    myfile.close();
}
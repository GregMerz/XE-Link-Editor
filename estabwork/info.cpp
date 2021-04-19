#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "info.h"

using namespace std;

map<string,string> symMap;

Info::Info(string n, string addr, string l){
    name = n;
    address = addr;
    length = l;
}

void Info::PutIntoSymbolMap(string symbolName, string address){
    vectorMap.push_back(symbols(symbolName, address));
}

void Info::PrintSymbolMap(){
    for(symbols curr: vectorMap){
        cout << "                      " << curr.name;
        cout << "               " << curr.location << endl;
    }
}

void Info::WriteSymbolMap(){
    ofstream myfile;
    myfile.open("name.st", ios::app);
    for(symbols curr: vectorMap){
        myfile << "                      " << curr.name;
        myfile << "               " << curr.location << endl;
    }
    myfile.close();
}
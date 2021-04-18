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
        //curr.name.insert(curr.name.begin(), 6 - curr.name.length(), ' ');
        cout << "                      " << curr.name;
        cout << "               " << curr.location << endl;
    }

    // for (auto const& x : symMap)
    // {
    //     cout << setw(27) << setfill(' ')  << x.first;  // string (key)
    //     cout << setw(20) << setfill(' ')  << x.second << endl;
    // }
}

void Info::WriteSymbolMap(){
    ofstream myfile;
    myfile.open("name.st", ios::app);
    for (auto const& x : symMap)
    {
        myfile << setw(27) << setfill(' ')   << x.first  // string (key)
               << setw(20) << setfill(' ')   << x.second << endl;
    }
    myfile.close();
}
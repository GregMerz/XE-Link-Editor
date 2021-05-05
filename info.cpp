#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "info.h"

using namespace std;

map<string, string> symMap;

Info::Info(string n, string addr, string l)
{
    name = n;
    address = addr;
    length = l;
}

void Info::PutIntoSymbolMap(string symbolName, string address)
{
    vectorMap.push_back(symbols(symbolName, address));
}

void Info::PrintSymbolMap()
{

    for (int i = 0; i < vectorMap.size(); i++)
    {
        cout << "                      " << vectorMap.at(i).name;
        cout << "               " << vectorMap.at(i).location << endl;
    }
}

void Info::WriteSymbolMap()
{
    ofstream myfile;
    myfile.open("name.st", ios::app);

    for (int i = 0; i < vectorMap.size(); i++)
    {
        myfile << "                      " << vectorMap.at(i).name;
        myfile << "               " << vectorMap.at(i).location << endl;
    }
    myfile.close();
}
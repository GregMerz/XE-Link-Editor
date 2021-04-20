#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <utility>
#include <iomanip>
#include <vector>
#include <iterator>

#include "estab.h"

using namespace std;
map<string, Info> Estab::hmap;
vector<string> hvector;

Info *info;

void Estab::InitEstab(string name, string address, string length)
{
    Info i(name, address, length);
    info = &i;
    hmap.insert(pair<string, Info>(name, i));
    hvector.push_back(name);
}

void Estab::PutIntoEstab(string name, string symbolName, string address, string length)
{
    symbolName = symbolName.append(6 - symbolName.size(), ' ');
    name = name.append(4 - name.size(), ' ');

    //If not in map, place
    if (hmap.find(name) == hmap.end())
    {
        Info in(name, address, length);
        hmap.insert(pair<string, Info>(name, in));
        hvector.push_back(name);
        info = &in;
    }

    //At this point the control section name is inserted
    //Extra space in check since I am appending
    if (symbolName != "      ")
    {
        PutIntoSymbolMap(name, symbolName, address);
    }
}

void Estab::PutIntoSymbolMap(string name, string symbolName, string address)
{
    //Point to symbolMap (put it into vairable)
    Info *ff = &(hmap.at(name));
    ff->PutIntoSymbolMap(symbolName, address);
}

void Estab::WriteEstab()
{
    ofstream myfile;
    myfile.open("name.st");

    myfile << "Control Section     | Symbol Name        | Address            |Length" << endl;

    myfile.close();

    map<string, Info>::iterator it = hmap.begin();

    while (it != hmap.end())
    {
        myfile.open("name.st", ios::app);
        Info infocurr = it->second;
        myfile << it->first;
        myfile << setw(42) << setfill(' ') << infocurr.address;
        myfile << setw(18) << setfill(' ') << infocurr.length << endl;
        myfile.close();
        infocurr.WriteSymbolMap();

        it++;
    }
}

void Estab::PrintEstab()
{
    cout << "Control Section     | Symbol Name        | Address            |Length" << endl;

    for (string curr : hvector)
    {
        Info infocurr = hmap.at(curr);
        cout << curr;
        cout << setw(42) << setfill(' ') << infocurr.address;
        cout << setw(18) << setfill(' ') << infocurr.length << endl;

        infocurr.PrintSymbolMap();
    }
}

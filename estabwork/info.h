#ifndef INFO_H
#define INFO_H

#include <string>
#include <map>

using namespace std;
class Info{
    public:
        string name;
        int length; 
        int address;

        Info(string n, int addr = 0, int l = 0);
        void PrintSymbolMap();
        void PutIntoSymbolMap(string symbolName, int address);
    private:
        map<string,int> symMap;
};
#endif
#ifndef INFO_H
#define INFO_H

#include <string>
#include <map>

using namespace std;
class Info{
    public:
        string name;
        string length; 
        string address;

        Info(string n, string addr = "-1", string l = "-1");
        void PrintSymbolMap();
        void PutIntoSymbolMap(string symbolName, string address);
        void WriteSymbolMap();
    private:
        map<string,string> symMap;
};
#endif
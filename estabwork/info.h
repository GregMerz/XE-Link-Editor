#ifndef INFO_H
#define INFO_H

#include <string>
#include <map>
#include <vector>

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

        struct symbols{
            string name;
            string location;

            symbols(string n, string loc){
                // name = n.append(6 - n.size(), ' ');
                // loc.insert(loc.begin(), 6 - loc.length(), '0');
                // location = loc;

                name = n;
                location = loc;
            }
        };

        vector<symbols> vectorMap;
    private:
        map<string,string> symMap;
};
#endif
#include <map>
#include <fstream>
#include "info.h"

using namespace std;
class Estab{

    public: 
        Estab(string name, string address, string length);
        static void PutIntoEstab(string csName, string symbolName, string address = "-1", string length = "-1");
        static void PutIntoSymbolMap(string controlSectionName, string symbolName, string address = "-1");

        static map<string, Info> hmap;

        Info* in;

        static void PrintEstab();
        void WriteEstab();
};
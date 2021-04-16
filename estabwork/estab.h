#include <map>
#include "info.h"

using namespace std;
class Estab{

    public: 
        Estab(string name, int address, int length);
        static void PutIntoEstab(string csName, string symbolName, int address = 0, int length = 0);
        static void PutIntoSymbolMap(string controlSectionName, string symbolName, int address = 0);

        static map<string, Info> hmap;

        Info* in;

        static void PrintEstab();
};
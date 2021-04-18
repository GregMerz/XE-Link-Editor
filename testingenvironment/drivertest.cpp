#include <iostream>
#include "objectprogram.h"

using namespace std;

int main(){
    cout << "Hello World\n";

    ObjectProgram obj("ProgA", "000000", "6C");
    obj.AddEXTDEF("LISTA", "40");
    obj.AddEXTDEF("ENDA", "54");
    obj.AddEXTREF("LISTB");
    obj.AddEXTREF("ENDB");
    obj.AddEXTREF("LISTC");
    obj.AddEXTREF("ENDC");
    obj.SetLength("7F");
    obj.WriteToFile("testfile.txt");
    
    
    return 1;
}
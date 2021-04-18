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

    obj.AddTextRecord("1000");
    obj.AddTextRecord("1000","141033");
    obj.AddTextRecord("1000","482039");
    obj.AddTextRecord("1000","001036");
    
    obj.SetTextRecordLength("1000", "1E");
    obj.SetTextRecordLength("2000", "-1");

    obj.AddTextRecord("2000","141033");
    obj.AddTextRecord("2000","482039");
    obj.AddTextRecord("2000","001036");

    obj.WriteToFile("testfile.txt");
    
    return 1;
}
#include "estab.h"
#include "info.h"
#include <iostream>
using namespace std;

int main(){
    cout << "Hello World\n";
    //cout << "Storing address and length as ints for now.\n";
    Estab estab("ProgA", "4000", "63");
    estab.PutIntoEstab("ProgA", "ListA", "4040");
    
    estab.PutIntoEstab("ProgB", "", "4063", "67");
    estab.PutIntoEstab("ProgB", "ListB", "4099");

    estab.PrintEstab();
    estab.WriteEstab();
}
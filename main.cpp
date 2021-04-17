#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

map<string, string> symTab;
string getInfo(int startIdx, string data){
    string delimiter = " ";
    string info = data.substr(startIdx, data.find(delimiter)+4); //4 for 4 bytes? string or char?
    //Strip string if do use.
    //cout << info << endl;
    return info;
}

void recordInfo(int startIdx, int endIdx, char *info, char *data)
{   
    for (int i = startIdx; i < endIdx; i++)
    {
        info[i - startIdx] = data[i];
    }
    info[endIdx] = 0;
}

int main(int argc, char **argv)
{
    char line[80];
    string *addresses;
    string *symbols;
    string* opcodes;
    string* arguments;
    string* objectCodes;
    addresses = new string[20];
    symbols = new string[20];
    opcodes = new string[20];
    arguments = new string[20];
    objectCodes = new string[20];
    ifstream myfile("P2sampleAdder.lis");

    if (!myfile.is_open())
    {
       cout << "Unable to open file" << endl; 
    }else{
        
        int idx = 0;
        char *address;
        char* symbol;
        char* opcode;
        char* argument;
        char* objectCode;

        // Get addresses and symbols and place them into symTab<string,string>
        while (myfile.getline(line, 80))
        {
            address = new char[4];
            symbol = new char[10];
            opcode = new char[10];
            argument = new char[24];
            objectCode = new char[9];
            recordInfo(0, 4, address, line);    
            //getSymbol(8, line);
            recordInfo(8, 16, symbol, line);
            //recordInfo(16, 25, opcode,line);      //<---------------------------- Can't get this working for some reason
            opcode = &getInfo(16, line)[0];
            recordInfo(25, 48, argument, line);
            //argument = &getInfo(20, line)[0];
            //recordInfo(49, 57, objectCode, line);
            //objectCode = &getInfo(27, line)[0];
            addresses[idx] = address;
            symbols[idx] = symbol;
            opcodes[idx] = opcode;  
            arguments[idx] = argument;
            //objectCodes[idx] = objectCode;
            symTab.insert(pair<string,string>(symbol,address)); //Book says error flags?         
            idx++;                                     
        }
        
        //Print for debugging
        for (int i = 0; i < 20; i++)
        {
            cout << arguments[i] << endl;
        }
        myfile.close();
    }
    
    return 0;
}

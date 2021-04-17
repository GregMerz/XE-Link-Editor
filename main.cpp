#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

map<string, string> symTab;
void getSymbol(int startIdx, string data){
    string delimiter = " ";
    string symbol = data.substr(startIdx, data.find(delimiter)+4);
    //Strip string if do use.
    //cout << symbol << endl;
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
    addresses = new string[20];
    symbols = new string[20];
    ifstream myfile("P2sampleAdder.lis");

    if (!myfile.is_open())
    {
       cout << "Unable to open file" << endl; 
    }else{
        
        int idx = 0;
        char *address;
        char* symbol;

        // Get addresses and symbols and place them into symTab<string,string>
        while (myfile.getline(line, 80))
        {
            address = new char[4];
            symbol = new char[10];
            recordInfo(0, 4, address, line);    
            getSymbol(8, line);
            recordInfo(8,16, symbol, line);
            addresses[idx] = address;
            symbols[idx] = symbol;  
            symTab.insert(pair<string,string>(symbol,address)); //Book says error flahs?         
            idx++;                                     
        }
        
        //Print for debugging
        // for (int i = 0; i < 20; i++)
        // {
        //     cout << symbols[i] << endl;
        // }
        myfile.close();
    }
    
    return 0;
}

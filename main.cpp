#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <unordered_map>
using namespace std;

map<string, string> symTab; //<----------------- Add Flags
string getInfo(int startIdx, string data)
{
    string delimiter = " ";
    string info = data.substr(startIdx, data.find(delimiter) + 4); //4 for 4 bytes? string or char?
    //Strip string if do use.
    //cout << info << endl;
    return info;
}

void recordInfo(int startIdx, int endIdx, char *info, char *data)
{
    info[0] = data[startIdx];
    for (int i = startIdx + 1; i < endIdx; i++)
    {
        if (!isspace(data[i]))
            info[i - startIdx] = data[i];
        else
            break;
    }
    info[endIdx] = 0;
}

int main(int argc, char **argv)
{
    char line[80];
    string *addresses;
    string *symbols;
    string *opcodes;
    string *arguments;
    string *objectCodes;
    unordered_map<string, char> extMap;
    string extrefs;
    addresses = new string[20];
    symbols = new string[20];
    opcodes = new string[20];
    arguments = new string[20];
    objectCodes = new string[20];
    ifstream myfile("P2sampleAdder.lis");

    if (!myfile.is_open())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {

        int lineIdx = 0;
        

        // Get addresses and symbols and place them into symTab<string,string>
        while (myfile.getline(line, 80))
        {

            string address;
            string symbol;
            string opcode;
            string argument;
            string objectCode;

            opcode.push_back(' ');
            argument.push_back(' ');

            int idx = 0;
            while (isprint(line[idx]))
            {
                if (isspace(line[idx]))
                {
                    idx++;
                    continue;
                }
                if (idx < 8)
                {
                    address.push_back(line[idx]);
                    
                }

                if (idx > 7 && idx < 16)
                {
                    symbol.push_back(line[idx]);
                    
                }

                if (idx > 15 && idx < 25)
                {
                    opcode.push_back(line[idx]);
                    
                }

                if (idx > 24 && idx < 51)
                {
                    argument.push_back(line[idx]);
                    
                }

                if (idx > 50 && idx < 57)
                {
                    objectCode.push_back(line[idx]);
                    
                }

                idx++;
            }

            if (opcode.compare(" EXTDEF") == 0)
            {
                char *extdef = new char[10];

                int beginExtdef = 0;

                for (int i = 0; i < argument.size() + 1; i++)
                {
                    if (i < argument.size())
                    {
                        if (argument.at(i) != ',')
                        {
                            extdef[i - beginExtdef] = argument[i];
                        }
                        else
                        {
                            extdef[i - beginExtdef] = 0;
                            pair<string, char> extdefMapEntry(extdef, 'D');
                            extMap.insert(extdefMapEntry);
                            beginExtdef = i + 1;
                        }
                    }
                    else
                    {
                        extdef[i - beginExtdef] = 0;
                        pair<string, char> extdefMapEntry(extdef, 'D');
                        extMap.insert(extdefMapEntry);
                    }
                }
            }

            else if (opcode.compare(" EXTREF") == 0)
            {
                char *extref = new char[10];

                int beginExtref = 0;

                for (int i = 0; i < argument.size() + 1; i++)
                {
                    if (i < argument.size())
                    {
                        if (argument.at(i) != ',')
                        {
                            extref[i - beginExtref] = argument[i];
                        }
                        else
                        {
                            extref[i - beginExtref] = 0;
                            pair<string, char> extrefMapEntry(extref, 'R');
                            extMap.insert(extrefMapEntry);
                            beginExtref = i + 1;
                        }
                    }
                    else
                    {
                        extref[i - beginExtref] = 0;
                        pair<string, char> extrefMapEntry(extref, 'R');
                        extMap.insert(extrefMapEntry);
                    }
                }

                
            }

            addresses[lineIdx] = address;
            symbols[lineIdx] = symbol;
            opcodes[lineIdx] = opcode;
            arguments[lineIdx] = argument;
            objectCodes[lineIdx] = objectCode;
            symTab.insert(pair<string, string>(symbol, address)); //Book says error flags?
            lineIdx++;
        }

        //Print for debugging
        for (int i = 0; i < 20; i++)
        {
            cout << addresses[i] << " " << symbols[i] << " " << opcodes[i] << " " << arguments[i] << " " << objectCodes[i] << endl;
        }

        myfile.close();
    }

    return 0;
}

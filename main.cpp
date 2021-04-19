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
    string line;
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
        char *address;
        char *symbol;
        char *opcode;
        char *argument;
        char *objectCode;

        // Get addresses and symbols and place them into symTab<string,string>
        while (myfile.getline(line, 80))
        {

            address = new char[4];
            symbol = new char[10];
            opcode = new char[10];
            argument = new char[24];
            objectCode = new char[9];

            int addressCounter = 0;
            int symbolCounter = 0;
            int opcodeCounter = 1;
            int argumentCounter = 1;
            int objectCounter = 0;

            opcode[0] = ' ';
            argument[0] = ' ';

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
                    address[idx] = line[idx];
                    addressCounter++;
                }

                if (idx > 7 && idx < 16)
                {
                    symbol[idx - 8] = line[idx];
                    symbolCounter++;
                }

                if (idx > 15 && idx < 25)
                {
                    opcode[idx - 16] = line[idx];
                    opcodeCounter++;
                }

                if (idx > 24 && idx < 51)
                {
                    argument[idx - 25] = line[idx];
                    argumentCounter++;
                }

                if (idx > 50 && idx < 57)
                {
                    objectCode[idx - 49] = line[idx];
                    objectCounter++;
                }

                idx++;
            }

            address[addressCounter] = 0;
            symbol[symbolCounter] = 0;
            opcode[opcodeCounter] = 0;
            argument[argumentCounter] = 0;
            objectCode[objectCounter] = 0;

            if (strcmp(opcode, " EXTDEF") == 0)
            {
                char *extdef = new char[10];

                int beginExtdef = 0;

                for (int i = 0; i < argumentCounter + 1; i++)
                {
                    if (i < argumentCounter)
                    {
                        if (argument[i] != ',')
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

            if (strcmp(opcode, " EXTREF") == 0)
            {
                char *extref = new char[10];

                int beginExtref = 0;

                for (int i = 0; i < argumentCounter + 1; i++)
                {
                    if (i < argumentCounter)
                    {
                        if (argument[i] != ',')
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

            /*
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
            recordInfo(25, 51, argument, line);
            //argument = &getInfo(20, line)[0];
            recordInfo(49, 57, objectCode, line);
            //objectCode = &getInfo(27, line)[0];
            */
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

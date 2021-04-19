#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <unordered_map>

#include "objectprogram.h"

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
    ObjectProgram obj;
    int bytes = 0;
    string headerName;
    string headerAddress;
    string textRecordAddress;
    string textRecordLength;
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

            // loop through each character in each line
            int idx = 0;
            while (isprint(line[idx]))
            {
                if (isspace(line[idx]))
                {
                    idx++;
                    continue;
                }

                // Add character to address if it is from col 0-7
                if (idx < 8)
                {
                    address.push_back(line[idx]);
                }
                // Add character to symbol if it is from col 8-15
                if (idx > 7 && idx < 16)
                {
                    symbol.push_back(line[idx]);
                }
                // Add character to opcode if it is from col 16-24
                if (idx > 15 && idx < 25)
                {
                    opcode.push_back(line[idx]);
                }
                // Add character to argument if it is from col 25-50
                if (idx > 24 && idx < 51)
                {
                    argument.push_back(line[idx]);
                }
                // Add character to objectCode if it is from col 51-58
                if (idx > 50 && idx < 59)
                {
                    objectCode.push_back(line[idx]);
                }

                idx++;
            }

            // If the opcode is START, we can set header name and header address information
            if (opcode.compare("START") == 0)
            {
                headerName = symbol;
                headerAddress = address;
                obj.InitHeader(headerName, headerAddress);
            }

            // If opcode is EXTDEF, we need to store all the extdef in a map
            else if (opcode.compare("EXTDEF") == 0)
            {
                string extdef;

                int beginExtdef = 0;
                for (int i = 0; i < argument.size(); i++)
                {
                    if (argument.at(i) == ',')
                    {
                        extdef = argument.substr(beginExtdef, i - beginExtdef);
                        pair<string, char> extdefMapEntry(extdef, 'D');
                        extMap.insert(extdefMapEntry);
                        beginExtdef = i + 1;
                    }
                }

                extdef = argument.substr(beginExtdef, argument.size() - beginExtdef);
                pair<string, char> extdefMapEntry(extdef, 'D');
                extMap.insert(extdefMapEntry);
            }
            // If opcode is EXTREF, we need to store all the extref in a map
            else if (opcode.compare("EXTREF") == 0)
            {
                string extref;

                int beginExtref = 0;

                for (int i = 0; i < argument.size(); i++)
                {

                    if (argument.at(i) == ',')
                    {
                        extref = argument.substr(beginExtref, i - beginExtref);
                        pair<string, char> extrefMapEntry(extref, 'R');
                        extMap.insert(extrefMapEntry);
                        beginExtref = i + 1;
                    }
                }

                extref = argument.substr(beginExtref, argument.size() - beginExtref);
                pair<string, char> extrefMapEntry(extref, 'D');
                extMap.insert(extrefMapEntry);
            }

            // Lines that declare variables
            else if (symbol.size() != 0 && objectCode.size() == 0)
            {
                for (auto &[key, value] : extMap)
                {
                    if (value == 'R')
                    {
                        int index = argument.find(key);

                        if (index != string::npos)
                        {
                            if (index == 0 || argument[index - 1] == '+')
                            {
                                obj.AddModificationRecord(key, address, "+", objectCode.size() / 2);
                            }
                            else
                            {
                                obj.AddModificationRecord(key, address, "-", objectCode.size() / 2);
                            }
                        }
                    }

                    else
                    {
                        int index = argument.find(key);

                        if (index != string::npos)
                        {
                            if (index == 0 || argument[index - 1] == '+')
                            {
                                obj.AddModificationRecord(headerName, address, "+", objectCode.size() / 2);
                            }
                            else
                            {
                                obj.AddModificationRecord(headerName, address, "-", objectCode.size() / 2);
                            }
                        }
                    }
                }
            }

            // If opcode is not START, EXTDEF, or EXTREF, check for extref for modification records
            else
            {
                for (auto &[key, value] : extMap)
                {
                    if (value == 'R')
                    {
                        int index = argument.find(key);

                        if (index != string::npos)
                        {
                            if (index == 0 || argument[index - 1] == '+')
                            {
                                obj.AddModificationRecord(key, address, "+", objectCode.size() / 2);
                            }
                            else
                            {
                                obj.AddModificationRecord(key, address, "-", objectCode.size() / 2);
                            }
                        }
                    }
                }
            }

            // Get how many bytes we are using from each opcode
            bytes += objectCode.size() / 2;

            addresses[lineIdx] = address;
            symbols[lineIdx] = symbol;
            opcodes[lineIdx] = opcode;
            arguments[lineIdx] = argument;
            objectCodes[lineIdx] = objectCode;
            symTab.insert(pair<string, string>(symbol, address)); //Book says error flags?
            lineIdx++;
        }

        string bytesstring = to_string(bytes);
        obj.SetLength(bytesstring);

        obj.WriteToFile("test.obj");

        //Print for debugging
        for (int i = 0; i < 20; i++)
        {
            cout << addresses[i] << " " << symbols[i] << " " << opcodes[i] << " " << arguments[i] << " " << objectCodes[i] << endl;
        }

        myfile.close();
    }

    return 0;
}

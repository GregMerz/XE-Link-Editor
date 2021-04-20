#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdlib.h>

#include "estab.h"
#include "objectprogram.h"
#include "info.h"

using namespace std;

map<string, string> symTab; //<----------------- Add Flags
string getInfo(int startIdx, string data)
{
    string delimiter = " ";
    string info = data.substr(startIdx, data.find(delimiter) + 4); //4 for 4 bytes? string or char?
    return info;
}

string ConvertToHexString(int address)
{
    stringstream stream;
    stream << hex << address;
    string result(stream.str());

    string hexidecimal;

    for (int i = 0; i < result.length(); i++)
        result.push_back(toupper(result.at(i)));
    return hexidecimal;
}

int ConvertToInt(string address)
{
    int x;
    stringstream ss;
    ss << hex << address;
    ss >> x;

    return x;
}

void AddTR(vector<string> objectCodes, vector<string> addresses, set<int> s1, string progname, ObjectProgram *obj)
{
    string currenttextrecord = "-1";
    int currentlinecharactercount = 0;
    int charactercount = 0;
    bool isTooManyCharacters = false;
    int length;

    //Iterate through parsed object codes
    set<int>::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        //start text record
        if (charactercount == 0)
        {
            if (currenttextrecord == "-1")
            {
                currenttextrecord = addresses.at(*itr);
                obj->AddTextRecord(currenttextrecord);
            }
        }

        if ((charactercount + objectCodes.at(*itr).size()) > 60)
        {
            isTooManyCharacters = true;
        }

        if (isTooManyCharacters || charactercount >= 55)
        {
            //Add currentlinecharactercount/2 + address
            obj->SetTextRecordLength(currenttextrecord, ConvertToHexString(charactercount / 2));

            int addressValue = ConvertToInt(currenttextrecord);

            int nextAddressInteger = addressValue + charactercount / 2;

            //Set and start new current text record
            currenttextrecord = ConvertToHexString(nextAddressInteger);
            charactercount = 0;
            isTooManyCharacters = false;
            obj->AddTextRecord(currenttextrecord);
        }

        obj->AddTextRecord(currenttextrecord, objectCodes.at(*itr));
        charactercount += objectCodes.at(*itr).size();
    }

    obj->SetTextRecordLength(currenttextrecord, ConvertToHexString(charactercount / 2));
}

void MemoryMapping(string *addresses, string *objectCodes)
{
    string starting_address = addresses[0];
    string ending_address = addresses[addresses->size() - 1];

    int starting_address_int = ConvertToInt(starting_address);
    int ending_address_int = ConvertToInt(ending_address);

    string tmp;
    for (int i = 0; i < 20; i++)
    {
        if (objectCodes[i].size() == 6)
        { //If it's format 3 get the last 2 characters
            tmp = objectCodes[i].substr(4, 6);
            int num = ConvertToInt(tmp);
            if (num < starting_address_int && num > ending_address_int)
            { //See if the characters are out of bounds
                if (num < 0)
                {                                           //If it's a negative number it may be jumping back
                    num = ConvertToInt(addresses[i]) - num; //If it is, see if after jump back it's still in range
                    if (num > starting_address_int)
                    {
                        continue;
                    }
                }
                if (num > 0)
                {
                    num = ConvertToInt(addresses[i]) + num;
                    if (num < ending_address_int)
                    {
                        continue;
                    }
                }
                cout << "Out of program memory space\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (objectCodes[i].size() == 8)
        { //If it's format 4 get the last 4 characters
            tmp = objectCodes[i].substr(6, 8);
            int num = ConvertToInt(tmp);
            if (num < starting_address_int && num > ending_address_int)
            { //See if the characters are out of bounds
                if (num < 0)
                {
                    num = ConvertToInt(addresses[i]) - num;
                    if (num > starting_address_int)
                    {
                        continue;
                    }
                }
                if (num > 0)
                {
                    num = ConvertToInt(addresses[i]) + num;
                    if (num < ending_address_int)
                    {
                        continue;
                    }
                }
                cout << "Out of program memory space\n";
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char **argv)
{
    Estab est;
    for (int clIdx = 1; clIdx < argc; clIdx++)
    {
        char line[80];
        vector<string> addresses;
        vector<string> symbols;
        vector<string> opcodes;
        vector<string> arguments;
        vector<string> objectCodes;
        vector<string> EXDEFS;
        vector<string> EXDEFaddresses;
        ObjectProgram obj;
        int bytes = 0;
        string headerName;
        string headerAddress;
        string textRecordAddress;
        string textRecordLength;
        map<string, char> extMap;
        string extrefs;
        set<int> s1;
        char *fileName = argv[clIdx];

        ifstream myfile(fileName);

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
                        s1.insert(lineIdx);
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
                            obj.AddEXTREF(extref);
                            pair<string, char> extrefMapEntry(extref, 'R');
                            extMap.insert(extrefMapEntry);
                            beginExtref = i + 1;
                        }
                    }

                    extref = argument.substr(beginExtref, argument.size() - beginExtref);
                    obj.AddEXTREF(extref);
                    pair<string, char> extrefMapEntry(extref, 'R');
                    extMap.insert(extrefMapEntry);
                }

                // Lines that declare variables
                else if (symbol.size() != 0 && objectCode.size() == 0)
                {
                    map<string, char>::iterator it = extMap.begin();

                    while (it != extMap.end())
                    {
                        string key = it->first;
                        char value = it->second;

                        if (value == 'R')
                        {
                            int index = argument.find(key);

                            if (index + key.size() >= argument.size() || argument.at(index + key.size()) == ',' || argument.at(index + key.size()) == '-' || argument.at(index + key.size()) == '+')
                            {
                                if (index != string::npos)
                                {
                                    if (index == 0 || argument[index - 1] == '+' || argument[index - 1] == '#')
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

                        else
                        {
                            int index = argument.find(key);

                            if (index + key.size() >= argument.size() || argument.at(index + key.size()) == ',' || argument.at(index + key.size()) == '-' || argument.at(index + key.size()) == '+')
                            {
                                if (index != string::npos)
                                {
                                    if (index == 0 || argument[index - 1] == '+' || argument[index - 1] == '#')
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

                        it++;
                    }
                }

                // If opcode is not START, EXTDEF, or EXTREF, check for extref for modification records
                else
                {
                    // Checking extref in text record space
                    map<string, char>::iterator it = extMap.begin();

                    while (it != extMap.end())
                    {
                        string key = it->first;
                        char value = it->second;

                        if (value == 'R')
                        {
                            int index = argument.find(key);

                            if (index + key.size() >= argument.size() || argument.at(index + key.size()) == ',')
                            {

                                if (index != string::npos)
                                {
                                    if (index == 0 || argument[index - 1] == '+' || argument[index - 1] == '#')
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

                        it++;
                    }
                }

                if (extMap[symbol] == 'D')
                {
                    obj.AddEXTDEF(symbol, address);
                    EXDEFS.push_back(symbol);
                    EXDEFaddresses.push_back(address);
                }

                // Get how many bytes we are using from each opcode
                bytes += objectCode.size() / 2;

                addresses.push_back(address);
                symbols.push_back(symbol);
                opcodes.push_back(opcode);
                arguments.push_back(argument);
                objectCodes.push_back(objectCode);

                symTab.insert(pair<string, string>(symbol, address)); //Book says error flags
                lineIdx++;
            }

            string bytesstring = ConvertToHexString(bytes);

            obj.SetLength(bytesstring);
            AddTR(objectCodes, addresses, s1, symbols.at(0), &obj);
            string outputFile = headerName + ".obj";
            obj.WriteToFile(outputFile);
            est.PutIntoEstab(headerName, "", headerAddress, bytesstring);
            for (int i = 0; i < EXDEFS.size(); i++)
            {
                est.PutIntoEstab(headerName, EXDEFS[i], EXDEFaddresses[i]);
            }
            myfile.close();
        }
        est.WriteEstab();
    }

    return 0;
}

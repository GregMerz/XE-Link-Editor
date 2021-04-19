#include <iostream>
#include <fstream>

using namespace std;

/*
string *addresses;
    string *symbols;
    string* opcodes;
    string* arguments;
    string* objectCodes;
*/

void makeObjectFile(string *addresses, string *symbols, string *opcodes, string *arguments, string *objectCodes)
{
    ofstream objectFile("made.obj");
}

void printHeaderRecord(ofstream *m_objectFile, string programLabel, string startAddress, string programLength)
{
    *m_objectFile << "H" << programLabel << startAddress << programLength << endl;
}

void printEXTDEF(ofstream *m_objectFile, string *extdef, string *extdefAddresses, int extdefLength)
{
    *m_objectFile << "D";

    for (int idx = 0; idx < extdefLength; idx++)
    {
        *m_objectFile << extdef[idx] << extdefAddresses[idx];
    }

    *m_objectFile << endl;
}

void printEXTREF(ofstream *m_objectFile, string *extref, int extrefLength)
{
    *m_objectFile << "R";

    for (int idx = 0; idx < extrefLength; idx++)
    {
        *m_objectFile << extref[idx];
    }

    *m_objectFile << endl;
}

void printTextRecord(ofstream *m_objectFile, string *addresses, string *symbols, string *opcodes, string *arguments, string *objectCodes)
{
}

void printModifiedRecord()
{
}

void printEndRecord()
{
}
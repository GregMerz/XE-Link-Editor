  
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "objectprogram.h"

using namespace std;

void ObjectProgram::InitHeader(string name, string address) {
    //Append spaces to the END name to make name equal to 7 characters
    control_section_name = name.append(6 - name.size(), ' ');

    //Insert 0s in the beginning of string to make equal to length of six
    address.insert(address.begin(), 6 - address.length(), '0');
    control_section_address = address;
}

// Add EXTDEF to Object Program, vector of objects with name and location
void ObjectProgram::AddEXTDEF(string name, string loc)
{
    vectorEXTDEF.push_back(EXTDEF(name, loc));
}

//Add EXTREF to Object Program, vector
void ObjectProgram::AddEXTREF(string name)
{
    vectorEXTREF.push_back(name.append(6 - name.size(), ' '));
}

//Set the length of the Object Program
void ObjectProgram::SetLength(string length)
{
    length.insert(length.begin(), 6 - length.length(), '0');
    control_section_size = length;
}

//Add new Text Record
void ObjectProgram::AddTextRecord(string starting, string entryaddress, string length)
{
    if (TextRecordMap.find(starting) == TextRecordMap.end())
    {
        //If starting doesn't exist
        //Insert a new TextRecord
        TextRecordMap.insert(pair<string, TextRecord>(starting, TextRecord(starting, length)));
        TextRecordsVector.push_back(starting);
    }

    if (entryaddress != "-1")
    {
        // Place into TextRecord struct list.
        TextRecord *curr = &TextRecordMap.at(starting);
        curr->AddAddressToTextRecord(entryaddress);
    }
}

void ObjectProgram::SetTextRecordLength(string start, string length)
{
    if (TextRecordMap.find(start) == TextRecordMap.end())
    {
        cout << "There is no text record by that name yet!\n";
        return;
    }
    else
    {
        TextRecord *curr = &TextRecordMap.at(start);
        curr->SetTextRecordLength(length);
    }
}

void ObjectProgram::AddModificationRecord(string symbol, string address, string sign, int format)
{
    ModificationRecordList.push_back(ModificationRecord(symbol, address, format, sign));
}

void ObjectProgram::WriteToFile(string filename, string line, string action)
{
    char carrot = '^';
    ofstream myfile;

    myfile.open(filename);

    myfile << "H^" << control_section_name << carrot << control_section_address << carrot << control_section_size << endl;
    myfile << "D";

    for (EXTDEF curr : vectorEXTDEF)
    {
        myfile << carrot << curr.name << carrot << curr.location;
    }

    myfile << "\nR";
    for (string curr : vectorEXTREF)
    {
        myfile << carrot << curr;
    }

    //Text Record order is in Vector
    //Text Recrod Information is in Map
    for (string curr : TextRecordsVector)
    {
        TextRecord *trInfo = &(TextRecordMap.at(curr));
        myfile << "\nT";
        myfile << carrot << trInfo->startingAddress;
        myfile << carrot << trInfo->size;

        // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // ////////Printing for debugging purposes
        //         cout << "\nT";
        //         cout << carrot << trInfo->startingAddress;
        //         cout << carrot << trInfo->size;
        //         trInfo->showlist();

        // ////////Printing for debugging purposes
        // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Print out line to file
        list<string>::iterator it;
        for (it = trInfo->AddressesInTextRecords.begin(); it != trInfo->AddressesInTextRecords.end(); ++it)
            myfile << '^' << *it;
    }

    //Print Modification Records
    for (const ModificationRecord &curr : ModificationRecordList)
    {
        string str;
        if (curr.format == 3)
        {
            str = "06";
        }
        else
        {
            str = "05";
        }
        myfile << "\nM^" << curr.address << carrot << str << carrot << curr.sign << curr.symbol;
    }
    myfile.close();
}
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "objectprogram.h"

using namespace std;

ObjectProgram::ObjectProgram(string name, string address, string length){
    //Append spaces to name to make name equal to 7 characters
    control_section_name = name.append(6 - name.size(), ' ');

    //Insert 0s in the beginning of string to make equal to length of six
    address.insert(address.begin(), 6 - address.length(), '0');
    control_section_address = address;

    //Insert 0s in the beginning of string to make equal to length of six
    length.insert(length.begin(), 6 - length.length(), '0');
    control_section_size = length;
}

// We can also get information from file.
void ObjectProgram::AddEXTDEF(string name, string loc){
    vectorEXTDEF.push_back(EXTDEF(name, loc));
}

void ObjectProgram::AddEXTREF(string name){
    vectorEXTREF.push_back(name.append(6 - name.size(), ' '));
}

void ObjectProgram::SetLength(string length){
    length.insert(length.begin(), 6 - length.length(), '0');
    control_section_size = length;
}

void ObjectProgram::WriteToFile(string filename, string line, string action){
    char carrot = '^';
    ofstream myfile;

    myfile.open(filename);
    
    myfile << "H^" << control_section_name << carrot << control_section_address << carrot << control_section_size << endl;
    myfile << "D";

    for(EXTDEF curr: vectorEXTDEF){
        myfile << carrot << curr.name << carrot << curr.location;
    }

    myfile << "\nR";
    for(string curr: vectorEXTREF){
        myfile << carrot << curr;
    }
    
    myfile.close();
}
#ifndef OBJECTPROGRAM_H
#define OBJECTPROGRAM_H

#include <string>
#include <vector>

using namespace std;

class ObjectProgram{
    public: 
        string control_section_name;
        string control_section_address;
        string control_section_size;
        vector<string> lines;
        

        ObjectProgram(string name, string address, string size = "-1");

        void WriteToFile(string filename, string line = "-1", string action = "-1");
        void AddEXTDEF(string name, string loc);
        void AddEXTREF(string name);
        void SetLength(string length);

        struct EXTDEF{
            string name;
            string location;

            EXTDEF(string n, string loc){
                name = n.append(6 - n.size(), ' ');
                loc.insert(loc.begin(), 6 - loc.length(), '0');
                location = loc;
            }
        };

        vector<EXTDEF> vectorEXTDEF;
        vector<string> vectorEXTREF;
};
#endif
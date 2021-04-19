#ifndef OBJECTPROGRAM_H
#define OBJECTPROGRAM_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>

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
        void AddTextRecord(string start, string entryaddress = "-1",string length = "-1");
        void SetTextRecordLength(string start, string length);
        void SetLength(string length);
        void AddModificationRecord(string symbol, string address, string sign, int format = 3);

        struct EXTDEF{
            string name;
            string location;

            EXTDEF(string n, string loc){
                name = n.append(6 - n.size(), ' ');
                loc.insert(loc.begin(), 6 - loc.length(), '0');
                location = loc;
            }
        };

        
        struct TextRecord{
            string startingAddress;
            string size;
            list<string> AddressesInTextRecords;

            TextRecord(string start, string s = "-1"){
                //Set starting address string to atleast 6 characters
                start.insert(start.begin(), 6 - start.length(), '0');
                startingAddress = start;

                //Make size string atleast two characters
                s.insert(s.begin(), 2 - s.length(), '0');
                size = s;
            }

            void SetTextRecordLength(string s){
                //Make size string atleast two characters
                s.insert(s.begin(), 2 - s.length(), '0');
                size = s;
            }

            void AddAddressToTextRecord(string addr){
                AddressesInTextRecords.push_back(addr);
            }

            void showlist()
            {
                list <string> :: iterator it;
                for(it = AddressesInTextRecords.begin(); it != AddressesInTextRecords.end(); ++it)
                    cout << '^' << *it;
                //cout << '\n';
            }
        };

        struct ModificationRecord{
            string symbol;
            string address;
            string sign;
            int format;
            ModificationRecord(string sym, string addr, int f, string s){
                symbol = sym;
                addr.insert(addr.begin(), 6 - addr.length(), '0');
                address = addr;
                format = f;
                sign = s;
            }
        };

        vector<EXTDEF> vectorEXTDEF;
        vector<string> vectorEXTREF;
        vector<string> TextRecordsVector;
        map<string, TextRecord> TextRecordMap;
        list<ModificationRecord> ModificationRecordList;
        
};
#endif
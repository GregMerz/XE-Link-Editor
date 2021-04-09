#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void recordInfo(int startIdx, int endIdx, char* info, char *data)
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
    addresses = new string[20];
    ifstream myfile("P2sampleAdder.lis");

    if (myfile.is_open())
    {
        int idx = 0;
        char *address;

        // Get 80 bytes of the line and place into variable called "line"
        // Then get the first four bytes of the line 
        // and place into an array of strings called "Address"
        // Then place that address into addresses
        while (myfile.getline(line, 80))
        {
            address = new char[4];
            recordInfo(0, 4, address, line);             // Is this going to be one pass or two?
            addresses[idx] = address;           
            idx++;                                     
        }
        
        //Print for debugging
        for (int i = 0; i < 20; i++)
        {
            cout << addresses[i] << endl;
        }
        myfile.close();
    }else
    {
        cout << "Unable to open file";
    }
    return 0;
}

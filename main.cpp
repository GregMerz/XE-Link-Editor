#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    string line;
    string *addresses;
    addresses = new string[20];
    ifstream myfile("P2sampleAdder.lis");

    if (!myfile.is_open())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {

        int idx = 0;
        string address;

        // Get 80 bytes of the line and place into variable called "line"
        // Then get the first four bytes of the line
        // and place into an array of strings called "Address"
        // Then place that address into addresses
        while (getline(myfile, line))
        {
            address = line.substr(0, 4); // Is this going to be one pass or two?
            addresses[idx] = address;
            idx++;
        }

        //Print for debugging
        for (int i = 0; i < 20; i++)
        {
            cout << addresses[i] << endl;
        }

        myfile.close();
    }

    return 0;
}

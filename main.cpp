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
    string * addresses;
    addresses = new string[20];
    ifstream myfile("P2sampleAdder.lis");

    if (myfile.is_open())
    {
        int idx = 0;
        char* address;

        while (myfile.getline(line, 80))
        {
            address = new char[4];
            recordInfo(0, 4, address, line);
            addresses[idx] = address;
            idx++;
        }
        
        for (int i = 0; i < 20; i++)
        {
            cout << addresses[i] << endl;
        }
        myfile.close();
        delete[] address;
        delete[] addresses;
    }else
    {
        cout << "Unable to open file";
    }
    return 0;
}

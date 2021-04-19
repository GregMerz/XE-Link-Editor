#include <sstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;
int main() {
    set<int> s1;

    s1.insert(3);
    s1.insert(4);
    s1.insert(5);

    set<int, greater<int> >::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        cout << *itr <<" ";
    }

    string* objectCodes = new string[3];

    cout << endl << objectCodes[6];

    cout << endl;
}
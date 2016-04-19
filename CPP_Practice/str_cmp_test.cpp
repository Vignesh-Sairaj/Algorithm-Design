#include <iostream>
using namespace std;


int main(void) {
    string s1, s2;

    cout << "Enter string 1: ";
    getline(cin, s1);

    cout << "\nEnter string 2: ";
    getline(cin, s2);

    cout << endl << "s1: " << s1 << "\ns2: " << s2 << endl;

    if(s1 == s2 ) {
        cout << "\nThe 2 stings are equal\n" << endl;
    }

    else {
        cout << "\nThe 2 stings are NOT equal\n" << endl;
    }
    return 0;
}


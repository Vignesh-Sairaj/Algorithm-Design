#include <iostream>
using namespace std;


int main(void) {
    string name;

    cout << "Enter name: ";
    getline(cin, name);
    cout << endl << "Hello, " << name << "!" << endl;
    return 0;
}

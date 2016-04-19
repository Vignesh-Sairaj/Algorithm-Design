#include<iostream>
using namespace std;


int main(void) {
    int test = 3;

    if(test == 3) {
        cout << "test treated as 3" << "; test = " << test << endl;
    }

    if(test = 2) {
        cout << "test treated as 2" << "; test = " << test << endl;
    }

    return 0;
}

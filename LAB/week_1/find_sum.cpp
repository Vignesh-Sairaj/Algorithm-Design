#include <iostream>
using namespace std;
const int SIZE = 20;

void print(const int [], const int len);

int main(void) {
    int a[SIZE];
    int num;
    bool exists = false;

    cout << "\nEnter number of elts in array: ";
    cin >> num;

    for(int i = 0; i < num; i++){
        cout << "Enter elt " << i << ": ";
        cin >> a[i];
    }

    cout << endl;
    
    print(a, num);

    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++){
            for(int k = 0; (i != j) && (k < num); k++) { //Also checks to make sure i!=j
                if( (j != k) && ( a[i] == (a[j]+a[k]) ) ){ //Checks for sum and for repitition
                    exists = true; //Such a sum exists
                    break;
                }
            }
        }
    }

    if(exists) {
        cout << endl << "\nThere exists elements: x, y, and z such that: x = y+z\n" << endl;
    } else {
        cout << endl << "\nThere exists NO such elements: x, y, and z such that: x = y+z\n" << endl;
    }


    return 0;
}


void print(const int a[], const int len) {
    cout << "\n{";
    
    for(int i = 0; i < len; ++i) {
        cout << " " << a[i] << " ";
    }
    
    cout << "}" << endl;
}







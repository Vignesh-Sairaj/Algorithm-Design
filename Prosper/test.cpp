#include <iostream>

#include "M_1_InsertionSort.cpp"

using namespace std;

int main (void) {

    int size;
    cout << "Enter array size: ";
    cin >>  size;

    cout << endl << endl;

    Sorter qObj(size);

    for(int i = 0; i < size ; i++) {

        cout << "Enter val at ind" << i << ": ";
        cin >> qObj[i];
    }

    cout << endl  << endl <<"Your Array: ";
    qObj.disp();
    cout << endl << endl;

    cout << "NumInversions = " << qObj.countInversions(0, size-1) << endl << endl;

    cout << "sorting..." << endl;
    qObj.insertion_sort_iterative(0,size-1);



    cout << "Your Array (sorted): ";
    qObj.disp();
    cout << endl << endl;




    cout << "\n\nOkThnxBye!" << endl << endl;
    return 0;
}

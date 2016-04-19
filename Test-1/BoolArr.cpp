#include <iostream>
#include <vector>

using namespace std;

class BoolArr {

    private:
        vector<int> boolArr;
        int len;

    public:
        BoolArr(int n);
        void disp();
        int count1(int start, int stop); //First and last indexes (both included)
        int& operator[](int i);
};

BoolArr::BoolArr(int n) {

    len = n;
    boolArr.resize(n);
}

int& BoolArr::operator[](int i) {

    if ( i < 0 ) {
        cout << "Error, index below range, returning first elt...";
        return boolArr[0];
    }

    else if ( i >= len) {
        cout << "Error, index below range, returning last elt...";
        return boolArr[len-1];
    }
    else
        return boolArr[i];


}

void BoolArr::disp() {

    cout << "<";

    for(int i = 0; i < len; i++) {

        cout << " " << boolArr[i] << " ";
    }

    cout << ">" << endl;
}

int BoolArr::count1(int start, int stop) {

    if (stop > start) {

        int q = (start + stop)/2;

        return count1(start, q) + count1(q+1, stop);
    }

    else if (stop == start) {
        return boolArr[start];
    }

    else {
        cout << "Invalid index access, returning 0..." << endl;
        return 0;
    }
}


int main (void) {

    int len;

    cout << "Enter size of bool-array: ";
    cin >> len;

    BoolArr boolVec(len);

    int temp;

    for(int i = 0; i < len; i++) {

        do {

            cout << "Enter bool element at index " << i << ": ";
            cin >> temp;
        } while (temp < 0 || temp > 1);

        boolVec[i] = temp;
    }

    cout << endl << endl;

    cout << "Num of ones = " << boolVec.count1(0, len-1) << endl << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM = 500;


void set_random(vector<int>& arr);
void disp(vector<int> const &arr);

bool ternSearch(vector<int>& arr, int start, int stop, int key);
bool binSearch(vector<int>& arr, int start, int stop, int key);


double avg_time_tern(int n);
double time_tern(int n);

double avg_time_bin(int n);
double time_bin(int n);


int main(void) {

    srand(time(NULL));

/*
    int len, key;

    cout << "Enter size of int-array: ";
    cin >> len;

    vector<int> arr(len);

    for(int i = 0; i < len; i++) {

        cout << "Enter elt at ind" << i << ": ";
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    cout << "Array (sorted) : " ;
    disp(arr);
    cout << endl;

    cout << "Enter key: ";
    cin >> key;

    cout << "?(key in arr) : " << ternSearch(arr, 0, len-1, key);

*/
    ofstream outFile;

    outFile.open("sim.csv");

    int start, step, stop;

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;

    outFile << "\"n\",\"Tern\",\"Bin\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << avg_time_tern(n) << ","  << avg_time_bin(n) << endl;
    }

    outFile.close();


    return 0;
}

void disp(vector<int> const &arr) {

    int len = arr.size();

    cout << "<";
    for(int i = 0; i < len; i++) {

        cout << " " << arr[i] << " ";
    }

    cout << ">";
}

bool binSearch(vector<int>& arr, int start, int stop, int key) {

    if(start > stop)
        return false;

    else if (start == stop)
        return (key == arr[start]);

    else{

        int q = (start + stop)/2;

        if(arr[q] == key)
            return true;

        else if (key < arr[q])
            return binSearch(arr, start, q-1, key);

        else
            return binSearch(arr, q+1, stop, key);
    }
}

bool ternSearch(vector<int>& arr, int start, int stop, int key) {

    if(start > stop)
        return false;

    else if (start == stop)
        return (key == arr[start]);

    else if (start == stop - 1)
        return (key == arr[start]) || (key == arr[stop]);

    else{

        int n = stop-start;
        int p = start + n/3;
        int q = start + (2*n)/3;

        if( (arr[p] == key) || (arr[q] == key) )
            return true;

        else if (key < arr[p])
            return ternSearch(arr, start, p-1, key);

        else if (key < arr[q])
            return ternSearch(arr, p+1, q-1, key);

        else
            return ternSearch(arr, q+1, stop, key);
    }

}


void set_random(vector<int>& arr) {

    for(auto i = arr.begin(); i < arr.end(); i++) {
        *i = rand();
    }

    sort(arr.begin(), arr.end());
}


double avg_time_tern(int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: Tern :: i = " << i << endl;
        sum += time_tern(n);
    }

    return (sum / (1.0*NUM));
}

double time_tern(int n) {

    int key = rand();

    vector<int> arr(n);
    set_random(arr);

    clock_t start, stop;

    start = clock();
    cout << "\t" << ternSearch(arr, 0, arr.size(), key) << endl;
    stop = clock();

    return ((double)(stop-start))/CLOCKS_PER_SEC;
}

double avg_time_bin(int n) {

    double sum = 0;


    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: Bin :: i = " << i << endl;
        sum += time_bin(n);
    }

    return (sum / (1.0*NUM));
}

double time_bin(int n) {

    int key = rand();

    vector<int> arr(n);
    set_random(arr);

    clock_t start, stop;

    start = clock();
    cout << "\t" << binSearch(arr, 0, arr.size(), key) << endl;
    stop = clock();

    return ((double)(stop-start))/CLOCKS_PER_SEC;
}

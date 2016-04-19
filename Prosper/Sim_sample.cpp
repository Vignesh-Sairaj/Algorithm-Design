#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "Sorter.cpp"

const int NUM = 100;


using namespace std;

double sort_avg_time(void (Sorter::*sortPtr) (int first, int last), int n);
double sort_time(void (Sorter::*sortPtr) (int first, int last), int n);

double search_avg_time(bool (Sorter::*searchPtr) (int item, int first, int last), int n);
double search_time(bool (Sorter::*searchPtr) (int item, int first, int last), int n);



double sort_avg_time(void (Sorter::*sortPtr) (int first, int last), int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: " << (void*)(sortPtr) << " :: i = " << i << endl;
        sum += sort_time(sortPtr, n);
    }

    return (sum / (1.0*NUM));
}

double sort_time(void (Sorter::*sortPtr) (int first, int last), int n) {

    Sorter arr(n);
    arr.set_random();

    clock_t start, stop;

    start = clock();

    (arr.*sortPtr)(0, n-1);

    stop = clock();


    return ((double)(stop-start))/CLOCKS_PER_SEC;
}

double search_avg_time(bool (Sorter::*searchPtr) (int item, int first, int last), int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: " << (void*)(searchPtr) << " :: i = " << i << endl;
        sum += search_time(searchPtr, n);
    }

    return (sum / (1.0*NUM));

}

double search_time(bool (Sorter::*searchPtr) (int item, int first, int last), int n) {


    Sorter arr(n);
    arr.set_random();
    sort(&arr[0], (&arr[n-1])+1);

    int item = rand();

    clock_t start, stop;

    start = clock();

    (arr.*searchPtr)(item, 0, n-1);

    stop = clock();


    return ((double)(stop-start))/CLOCKS_PER_SEC;
}



int main(void) {
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
    srand(time(NULL));

    ofstream outFile;

    outFile.open("sim_sample_sort.csv");

    int start, step, stop;

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;


    outFile << "\"n\",\"Insertion\",\"Quick\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << sort_avg_time(&Sorter::quick_sort, n)
                << ","  << sort_avg_time(&Sorter::insertion_sort_iterative, n) << endl;
    }

    outFile.close();

    outFile.open("sim_sample_search.csv");

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;


    outFile << "\"n\",\"Linear\",\"Variant\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << search_avg_time(&Sorter::linear_search, n)
                << ","  << search_avg_time(&Sorter::variant_linear_search, n) << endl;
    }

    return 0;
}

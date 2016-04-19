#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int NUM = 500;



class Sorter {
private:
    int len;
    vector<int> arr;
public:
    Sorter(int length);
    void set_at(int index, int val);
    void randomize();

    void bubble_sort();
    int find_max(int start, int end); // returns index to max [start included,  end excluded]
    int find_min(int start, int end); // returns index to min ['', '']

    void sort_max();
    void sort_min();
    void sort_min_max();

    int get_len(); //return len
    int& operator[] (int i); //Safe indexing
    void disp();
};

double time_bubble(int n);

double time_max(int n);

double time_min_max(int n);


double avg_time_bubble(int n);

double avg_time_max(int n);

double avg_time_min_max(int n);




int main (void) {
    srand(time(NULL));
    /*
    cout << "\nEnter no of elts: ";
    int num;
    cin >> num;

    Sorter v1(num);
    v1.randomize();

    cout << endl;
    v1.disp();
    cout << endl << endl;

    cout << "Max = " << v1[v1.find_max(0, v1.get_len())] << endl;

    cout << "Min = " << v1[v1.find_min(0, v1.get_len())] << endl;

    v1.sort_min_max();

    cout << endl;
    v1.disp();
    cout << endl << endl;
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

    outFile << "\"n\",\"Bubble\",\"Max\",\"Min-Max\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {
    
        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << avg_time_bubble(n) << ","  << avg_time_max(n) << "," << avg_time_min_max(n) << endl;
    }

    outFile.close();

    return 0;
}




Sorter::Sorter(int length) {
    len = length;
    arr.resize(len);
}
void Sorter::bubble_sort() {
    int temp;

    for(auto j = arr.end()-1; j > arr.begin(); j--) { // j is the index after which the elts will be in place after pass
        for(auto i = arr.begin(); i < j; ++i) { // i: primary var of iteration
            if(*i > *(i+1)) { //Swap
                temp = *i;
                *i = *(i+1);
                *(i+1) = temp;
            }
        }
    }
}
int Sorter::find_max(int start, int end) {
    int maxInd = start;

    for(int i = start; i < end; i++) {
        if(arr[i] > arr[maxInd]){
            maxInd = i;
        }
    }
    return maxInd;
}

int Sorter::find_min(int start, int end) {
    Sorter dupl(end - start); // Create duplicate of reqd size

    for(int i = 0; i < end - start; i++){
        dupl.set_at(i, arr[start + i]);
    }

    for(int i = 0; i < end - start; i++) {
        dupl[i] = -dupl[i];
    }


    return dupl.find_max(0, end-start) + start;
}
void Sorter::sort_max() {
    if (len ==  0) {
        return;
    }

    for(int i = len-1; i >= 0; i--) {
        int temp = arr[i];
        arr[i] = arr[find_max(0, i+1)];
        arr[find_max(0, i+1)] = temp;
    }
}
void Sorter::sort_min() {
    if (len ==  0) {
        return;
    }

    for(int i = 0; i < len; i++) {
        //cout << "\n";
        int temp = arr[find_min(i, len)];
        //cout << "index: " << i << "  ::  "<< arr[i] << "  ::  min: "  << temp <<endl;

        arr[find_min(i, len)] = arr[i];
        arr[i] = temp;

    }
}

void Sorter::sort_min_max() {
    int i = 0, j = len-1, temp;

    if(j < 0) return;

    while(true) {

        if(j <= i) break;

        temp = arr[find_min(i, j+1)];
        arr[find_min(i, j+1)] = arr[i];
        arr[i] = temp;
        i++;

        if(j <= i) break;

        temp = arr[find_max(i, j+1)];
        arr[find_max(i, j+1)] = arr[j];
        arr[j] = temp;
        j--;
    }
}


void Sorter::randomize() {

    for(auto i = arr.begin(); i < arr.end(); i++) {
        *i = rand();
    }
}

void Sorter::set_at(int index, int val) {
    *(arr.begin() + index) = val;
}

int Sorter::get_len() {
    return len;
}

void Sorter::disp() {
    cout << "\n<";
    for(int i = 0; i <len; ++i) {
        cout << " " << arr[i] << " ";
    }
    cout << ">" << endl;
}

int& Sorter::operator[] (int i) {
    if(i < 0 ) {
        cout << "\nInvalid call returning first elt..." << endl;
        return arr.front();
    }
    else if (i > len ) {
        cout << "\nInvalid call returning last elt..." << endl;
        return arr.back();
    }

    else
        return arr[i];
}


double avg_time_bubble(int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: Bubble :: i = " << i << endl;
        sum += time_bubble(n);
    }

    return (sum / (1.0*NUM));
}

double avg_time_max(int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: Max :: i = " << i << endl;
        sum += time_max(n);
    }

    return (sum / (1.0*NUM));
}

double avg_time_min_max(int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: Min-Max :: i = " << i << endl;
        sum += time_min_max(n);
    }

    return (sum / (1.0*NUM));
}



double time_bubble(int n) {

    Sorter v(n);

    v.randomize();

    time_t start, stop;

    time(&start);
    v.bubble_sort();
    time(&stop);

    return difftime(stop, start);
}

double time_max(int n) {

    Sorter v(n);

    v.randomize();

    time_t start, stop;

    time(&start);
    v.sort_max();
    time(&stop);

    return difftime(stop, start);
}

double time_min_max(int n) {

    Sorter v(n);

    v.randomize();

    time_t start, stop;

    time(&start);
    v.sort_min_max();
    time(&stop);

    return difftime(stop, start);
}

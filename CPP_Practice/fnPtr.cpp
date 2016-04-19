#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "Sorter.cpp"

const int NUM = 800;


using namespace std;

double sort_avg_time(void (Sorter::*sortPtr) (int first, int last), int n);
double sort_time(void (Sorter::*sortPtr) (int first, int last), int n);

double search_avg_time(bool (Sorter::*searchPtr) (int item, int first, int last), int n);
double search_time(bool (Sorter::*searchPtr) (int item, int first, int last), int n);

double count_avg_time(int n);
double count_time(int n);


void plot_insertion_sort(void);
void plot_quick_sort(void);
void plot_hybrid_sort(void);
void plot_variant_linear(void);





void plot_variant_linear(void) {

    srand(time(NULL));

    ofstream outFile;

    outFile.open("plot_variant_linear.csv");

    int start, step, stop;

    cout << "plot_variant_linear" << endl;
    cout << "To run simulation, enter the start, stop (excluded) and step values for size(s) of array:" << endl;

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;


    outFile << "\"n\",\"Variant-Linear-Search\",\"Linear-Search\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << search_avg_time(&Sorter::variant_linear_search, n)
                << ","  << search_avg_time(&Sorter::linear_search, n) << endl;
    }
/*
plot Variant-Linear-Search() and Linear-Search()
*/

    outFile.close();

}




void plot_hybrid_sort(void) {

    srand(time(NULL));

    ofstream outFile;

    outFile.open("plot_hybrid_sort.csv");

    int start, step, stop;

    cout << "plot_hybrid_sort" << endl;
    cout << "To run simulation, enter the start, stop ((excluded)) and step values for size(s) of array:" << endl;

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;


    outFile << "\"n\",\"Insertion-Sort-Iterative\",\"Quick-Sort\",\"Quick-Insertion-Sort\",\"Merge-Insertion-Sort\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << sort_avg_time(&Sorter::insertion_sort_iterative, n)
                << ","  << sort_avg_time(&Sorter::quick_sort, n)
                << ","  << sort_avg_time(&Sorter::quick_insertion_sort, n)
                << ","  << sort_avg_time(&Sorter::merge_insertion_sort, n) << endl;
    }


/*
plot Insertion-Sort-Iterative(), Quick-Sort(), Quick-Insertion-Sort(), Merge-
Insertion-Sort()
*/

    outFile.close();

}


void plot_quick_sort(void) {

    srand(time(NULL));

    ofstream outFile;

    outFile.open("plot_quick_sort.csv");

    int start, step, stop;

    cout << "plot_quick_sort" << endl;
    cout << "To run simulation, enter the start, stop (excluded) and step values for size(s) of array:" << endl;

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;


    outFile << "\"n\",\"Quick-Sort\",\"Quick-Sort-Pivot-Middle\",\"Quick-Sort-Pivot-First\",\"Quick-Sort-Pivot-Random\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << sort_avg_time(&Sorter::quick_sort, n)
                << ","  << sort_avg_time(&Sorter::quick_sort_pivot_middle, n)
                << ","  << sort_avg_time(&Sorter::quick_sort_pivot_first, n)
                << ","  << sort_avg_time(&Sorter::quick_sort_pivot_random, n) << endl;
    }


/*
Quick-Sort(), Quick-Sort-Pivot-Middle(), Quick-Sort-Pivot-First(), Quick-Sort-
Pivot-Random()
*/

    outFile.close();
}

void plot_insertion_sort(void) {

    srand(time(NULL));

    ofstream outFile;

    outFile.open("plot_insertion_sort.csv");

    int start, step, stop;

    cout << "plot_insertion_sort" << endl;
    cout << "To run simulation, enter the start, stop (excluded) and step values for size(s) of array:" << endl;

    cout << "Enter start: ";
    cin >> start;

    cout << "Enter step: ";
    cin >> step;

    cout << "Enter stop: ";
    cin >> stop;


    outFile << "\"n\",\"Insertion-Sort-Iterative\",\"Insertion-Sort-Recursive\",\"Insertion-Sort-Binary\",\"Counting-Inversions\"" << endl;

    outFile.precision(10);

    for(int n = start; n < stop; n += step) {

        cout << "\nn = " << n << endl;
        outFile << n << "," << fixed  << sort_avg_time(&Sorter::insertion_sort_iterative, n)
                << ","  << sort_avg_time(&Sorter::insertion_sort_recursive, n)
                << ","  << sort_avg_time(&Sorter::insertion_sort_binary, n)
                << ","  << count_avg_time(n) << endl;
    }

/*
Insertion-Sort-Iterative(), Insertion-Sort-Recursive(),
Binary-Search-based-Insertion-Sort(), Counting-Inversions().
*/
    outFile.close();
}




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

    (arr.*searchPtr) (item, 0, n-1);

    stop = clock();


    return ((double)(stop-start))/CLOCKS_PER_SEC;
}


double count_avg_time(int n) {

    double sum = 0;

    for(int i = 0; i < NUM; i++) {
        cout << "\tn = " << n << " :: " << "Count" << " :: i = " << i << endl;
        sum += count_time(n);
    }

    return (sum / (1.0*NUM));

}
double count_time(int n) {

    Sorter arr(n);
    arr.set_random();

    clock_t start, stop;

    start = clock();

    arr.countInversions(0, n-1);

    stop = clock();

    return ((double)(stop-start))/CLOCKS_PER_SEC;
}


int main (void) {

    plot_insertion_sort();
    plot_quick_sort();
    plot_hybrid_sort();
    plot_variant_linear();
    return 0;
}

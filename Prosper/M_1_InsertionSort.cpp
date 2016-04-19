#include<iostream>

#include "Sorter.hpp"

using namespace std;


Sorter::Sorter(size_t n) {

    size = n;
    arr.resize(n);
}

int& Sorter::operator[](int index) {

    if(index < 0 || index >= static_cast<int>(size)) {
        cout << "ERROR: Index out of range, returning last elt..."  << endl;
        return arr[size-1];
    }

    else {
        return arr[index];
    }
}

void Sorter::disp() {

    cout << "<";

    for(size_t i = 0; i < size; i++) {

        cout << " " << arr[i] << " ";
    }

    cout  << ">" << endl;
}



//Module-1 Insertion Sort

void Sorter::insertion_sort_iterative(int first, int last) {

    for(int j = first+1; j <= last; j++ ) {

        int x = arr[j]; //new elt to be inserted in already sorted subarray

        int i = j-1; //prev elt

        while(i > first-1 && x < arr[i] ) {

            arr[i+1] = arr[i];
            i--;
        }

        arr[i+1] = x;
    }
}

void Sorter::insertion_sort_recursive(int first, int last) {

    if ((last-first) > 1) {

        insertion_sort_recursive(first, last - 1);
    }

    else if ((last-first) < 0) {

        cout << "Error: index out of range!" << endl;
        return;
    }

    int k = arr[last];
    int i = last - 1;

    while (i >= first  &&  arr[i] > k) {

        arr[i+1] = arr[i];
        i--;
    }

    arr[i+1] = k;

}
int Sorter::countInversions(int first, int last) {

    int count = 0;

    for(int j = first+1; j <= last; j++) {

        for(int i = first; i < j; i++) {

            if(arr[i] > arr[j]) {

                count++;
            }
        }
    }


    return count;
}


int Sorter::binarySearch(int item, int low, int high) {
    if (high <= low)
        return (item > arr[low])?  (low + 1): low;

    int mid = (low + high)/2;

    if(item == arr[mid])
        return mid+1;

    if(item > arr[mid])
        return binarySearch(item, mid+1, high);

    return binarySearch(item, low, mid-1);
}

void Sorter::insertion_sort_binary(int first, int last) {

	int loc, j, selected;

    for (int i = first+1; i <= last; i++){

		j = i - 1;
        selected = arr[i];

        loc = binarySearch(selected, first, j);

        while (j >= loc){

			arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = selected;
    }
}


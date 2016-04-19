#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

#include "Sorter.hpp"

using namespace std;


double avg_time_tern(int n);
double time_tern(int n);



Sorter::Sorter(size_t n) {

    size = n;
    arr.resize(n);
}

void Sorter::resize(size_t n) {
    arr.resize(n);
    size = n;
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

void Sorter::set_random() {


    for(int i = 0 ; i < static_cast<int>(size); i++) {

        arr[i] = rand()%size;
    }
}


//Module-2: QuickSort variants


void Sorter::quick_sort(int first, int last) {

    /*
        Implements classical quick-sort,
        with pivot = last element
    */


	if(first < last) {

		int pivotInd = partion(first, last);
		quick_sort(first, pivotInd-1);
		quick_sort(pivotInd+1, last);
	}
}

int Sorter::partion(int first, int last) {

	int pivot = arr[last];

	int i = first - 1;

	/*
        Loop Invariant(s):
        >> All elements in arr[start, i] {ends included} are <= arr[pivot]
        >> All elements in arr[i, j] {ends excluded are > arr[pivot]}
	*/

	for(int j = first ; j < last ; j++) {

		if(arr[j] <= pivot) {

			i++;
			//Swap elts at i and j
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

    //Swap elts at i+1 and last (pivot)
	int temp = arr[i+1];
	arr[i+1] = pivot;
	arr[last] = temp;

	return i+1;
}


void Sorter::quick_sort_pivot_first(int first, int last) {

	if(first < last) {

        //Swap fist and last elts
        int temp = arr[first];
        arr[first] = arr[last];
        arr[last] = temp;

        //Normal quick-sort
		int pivotInd = partion(first, last);
		quick_sort_pivot_first(first, pivotInd-1);
		quick_sort_pivot_first(pivotInd+1, last);
	}
}

void Sorter::quick_sort_pivot_middle(int first, int last) {

	if(first < last) {

        int mid = (first + last)/ 2;

        //Swap elts at mid and last
        int temp = arr[mid];
        arr[mid] = arr[last];
        arr[last] = temp;

        //Classical Quick-Sort
		int pivotInd = partion(first, last);
		quick_sort_pivot_middle(first, pivotInd-1);
		quick_sort_pivot_middle(pivotInd+1, last);
	}
}

void Sorter::quick_sort_pivot_random(int first, int last) {

	if(first < last) {

        int randInd = first + rand()%(last-first+1);

        //Swap randInd and Last
        int temp = arr[randInd];
        arr[randInd] = arr[last];
        arr[last] = temp;

        //Classical Quick-Sort
        int pivotInd = partion(first, last);
		quick_sort_pivot_random(first, pivotInd-1);
		quick_sort_pivot_random(pivotInd+1, last);
	}
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



//Module-3 Hybrid

void Sorter::quick_20_sort(int first, int last) {


    //Stops when sub-array is of size 20 or less
    if((last - first) > 20) {

		int pivotInd = partion(first, last);
		quick_20_sort(first, pivotInd-1);
		quick_20_sort(pivotInd+1, last);
	}
}

void Sorter::quick_insertion_sort(int first, int last) {

    quick_20_sort(first, last);
    insertion_sort_iterative(first, last);
}


void Sorter::merge(int first, int mid, int last) {

    if((first > mid) || (mid > last) || (first > last)) {

        cout << "Invalid call!" << endl;
        return;
    }

    int nL = mid - first + 1; //Number of elements in left subarray
    int nR = last - mid; //Number of elements in right subarray

    vector<int> L(nL+1);
    vector<int> R(nR+1);

    for (int i = 0; i < nL; ++i){

        L[i] = arr[first + i];
    }

    for (int i = 0; i < nR; ++i){

        R[i] = arr[mid + 1 + i];
    }

    L[nL] = INT_MAX;
    R[nR] = INT_MAX;

    int i = 0, j = 0; //iterators for left and right sub-arrays respectively

    for(int k = first; k <= last; k++) {

        if(L[i] <= R[j]) {

            arr[k] = L[i];
            i++;
        }
        else {

            arr[k] = R[j];
            j++;
        }
    }
}


void Sorter::merge_insertion_sort(int first, int last) {

    if((last-first) > 20) {

        int mid = (first + last)/2;
        merge_insertion_sort(first, mid);
        merge_insertion_sort(mid+1, last);
        merge(first, mid, last);
    }

    else if (last > first) {

        insertion_sort_iterative(first, last);
    }
}

bool Sorter::variant_linear_search(int item, int first, int last) {

    if(first > last) {

        return false;
    }

    else  {

        return (arr[first] == item) || (arr[last] == item) || variant_linear_search(item, first+1, last-1);
    }
}

bool Sorter::linear_search(int item, int first, int last) {

    if(first > last) {
        return false;
    }

    else {
        return (item == arr[first]) || linear_search(item, first+1, last);
    }
}

//// Test
//
//
//int main (void) {
//
//    int size;
//    cout << "Enter array size: ";
//    cin >>  size;
//
//    cout << endl << endl;
//
//    Sorter qObj(size);
//
//    for(int i = 0; i < size ; i++) {
//
//        cout << "Enter val at ind" << i << ": ";
//        cin >> qObj[i];
//    }
//
//    cout << endl  << endl <<"Your Array: ";
//    qObj.disp();
//    cout << endl << endl;
//
//    cout << "NumInversions = " << qObj.countInversions(0, size-1) << endl << endl;
//
//    cout << "sorting..." << endl;
//    qObj.quick_sort_pivot_random(0,size-1);
//
//
//
//    cout << "Your Array (sorted): ";
//    qObj.disp();
//    cout << endl << endl;
//
//
//    int item;
//    cout << "Enter item to look for: ";
//    cin >>  item;
//
//    cout << "(Item is in array)?  " << qObj.linear_search(item, 0, size-1) << endl << endl;
//
//    cout << "\n\nOkThnxBye!" << endl << endl;
//    return 0;
//}
//
//

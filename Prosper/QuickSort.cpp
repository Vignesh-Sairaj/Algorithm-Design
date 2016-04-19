#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class QuickSort {

	private:
		vector<int> arr;
		size_t size;
	public:
		QuickSort(int n);
		void quick_sort(int first, int last);
		void quick_sort_pivot_middle(int first, int last);
		int partion_middle(int first, int last);
		void quick_sort_pivot_first(int first, int last);
		int partion_first(int first, int last);
		void quick_sort_pivot_random(int first, int last);
		int partion(int first, int last);
		int partion_random(int first, int last);

		int& operator[](int index);
        void disp();
};

QuickSort::QuickSort(int n) {

    size = n;
    arr.resize(n);
}



int& QuickSort::operator[](int index) {

    if(index < 0 || index >= size) {
        cout << "ERROR: Index out of range, returning last elt..."  << endl;
        return arr[size-1];
    }

    else {
        return arr[index];
    }
}


void QuickSort::disp() {

    cout << "<";

    for(int i = 0; i < size; i++) {

        cout << " " << arr[i] << " ";
    }

    cout  << ">" << endl;
}
void QuickSort::quick_sort(int first, int last) {
    int pivotInd;
	if(first < last) {

		pivotInd = partion(first,last);
		quick_sort(first, pivotInd-1);
		quick_sort(pivotInd+1, last);
	}
}
int QuickSort::partion(int first, int last) {

	int pivot;
	pivot = arr[last];
	int i;
	i = first - 1;
	for(int j = first ; j < last ; j++) {

		if(arr[j] < pivot) {

			i=i+1;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	int temp = arr[i+1];
	arr[i+1] = pivot;
	arr[last] = temp;

	return i+1;
}

int QuickSort::partion_first(int first, int last) {

    int temp = arr[first];
	arr[first] = arr[last];
	arr[last] = temp;

	int pivot = arr[last];

	int i = first - 1;
	for(int j = first ; j < last ; j++) {

		if(arr[j] < pivot) {

			i=i+1;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	 temp = arr[i+1];
	arr[i+1] = pivot;
	arr[last] = temp;

	return i+1;
}
int QuickSort::partion_middle(int first, int last) {
	int temp,mid;
	mid = (first + last) / 2;
	temp = arr[mid];
	arr[mid] = arr[last];
	arr[last] = temp;
	int pivot;
	pivot = arr[last];
	int i;
	i = first - 1;
	for(int j = first ; j < last ; j++) {

		if(arr[j] < pivot) {

			i=i+1;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	temp = arr[i+1];
	arr[i+1] = pivot;
	arr[last] = temp;

	return i+1;
}
int QuickSort::partion_random(int first, int last) {

	srand(time(NULL));
	int temp,mid;
	mid = rand()%size;
	temp = arr[mid];
	arr[mid] = arr[last];
	arr[last] = temp;

	int pivot;
	pivot = arr[last];
	int i;
	i = first - 1;
	for(int j = first ; j < last ; j++) {

		if(arr[j] < pivot) {

			i=i+1;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	temp = arr[i+1];
	arr[i+1] = pivot;
	arr[last] = temp;

	return i+1;
}

void QuickSort::quick_sort_pivot_first(int first, int last) {




	int pivotInd;

	if(first < last) {

		pivotInd = partion_first(first,last);
		quick_sort_pivot_first(first, pivotInd-1);
		quick_sort_pivot_first(pivotInd+1, last);
	}
}

void QuickSort::quick_sort_pivot_middle(int first, int last) {


	int pivotInd;

	if(first < last) {

		pivotInd = partion(first,last);
		quick_sort_pivot_middle(first, pivotInd-1);
		quick_sort_pivot_middle(pivotInd+1, last);
	}
}

void QuickSort::quick_sort_pivot_random(int first, int last) {



	int pivotInd;

	if(first < last) {

		pivotInd = partion(first,last);
		quick_sort_pivot_random(first, pivotInd-1);
		quick_sort_pivot_random(pivotInd+1, last);
	}
}














int main (void) {

    int size;
    cout << "Enter array size: ";
    cin >>  size;

    cout << endl << endl;

    QuickSort qObj(size);

    for(int i = 0; i < size ; i++) {

        cout << "Enter val at ind" << i << ": ";
        cin >> qObj[i];
    }

    cout << endl  << endl <<"Your Array: ";
    qObj.disp();
    cout << endl << endl;



    cout << "sorting..." << endl;
    qObj.quick_sort_pivot_random(0,size-1);



    cout << "Your Array (sorted): ";
    qObj.disp();
    cout << endl << endl;




    cout << "\n\nOkThnxBye!" << endl << endl;
    return 0;
}




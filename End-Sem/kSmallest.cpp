#include <iostream>
#include <vector>
#include <algorithm>






int partition(std::vector<int>& arr, int first, int last) {

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


int quickSelectMin(std::vector<int>& arr, int first, int last, int k) { //returns val of kth min

    /*
        Implements classical quick-select
        with pivot = last element
    */

    if (first == last) {
    	return arr[first];
    }


    int pivotInd = partition(arr, first, last);

    if (pivotInd == k-1) {
    	return arr[pivotInd];
    }

	else if(pivotInd < k-1) {
		return quickSelectMin(arr, pivotInd+1, last, k);
	}

	else {
		return quickSelectMin(arr, first, pivotInd-1, k);
	}
}


std::vector<int> kSmallest(std::vector<int> v, int k) {

    int n = v.size();
	quickSelectMin(v, 0, n-1, k);
	std::swap(v[k-1], v[n-1]);
	partition(v, 0, n-1);

	return std::vector<int> (v.begin(), v.begin()+k);
}

std::vector<int> kLargest(std::vector<int> v, int k) {


    int n = v.size();
	quickSelectMin(v, 0, n-1, n-k+1);
	std::swap(v[n-k], v[n-1]);
	partition(v, 0, n-1);

	return std::vector<int> (v.end()-k, v.end());
}






void disp(const std::vector<int>& v) {

    std::cout << "(";

    for (auto x : v) {
            std::cout << " " << x << " ";
    }
    std::cout << ")" << std::endl;
}

int main() {

	std::cout << "Enter size of array: ";
	int size;
	std::cin >> size;

	std::cout << "Enter all element of the array: ";
	std::vector<int> v(size);

	for (int i = 0; i < size; ++i) {
		std::cin >> v[i];
	}

	std::cout << "\n";
	disp(v);

	std::cout << "Enter k: ";
	int k;
	std::cin >> k;

	std::cout << "\nK Smallest elements:\n";
	disp(kSmallest(v, k));

	std::cout << "\nK Largest elements:\n";
	disp(kLargest(v, k));

	return 0;
}

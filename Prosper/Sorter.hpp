#include <vector>

class Sorter {

	private:
		std::vector<int> arr;
		std::size_t size;

	public:

		Sorter(std::size_t n);
		void resize(std::size_t n);
		int& operator[](int index);
        void disp();
        void set_random();

        //QuickSort
		void quick_sort(int first, int last);
		int partion(int first, int last);

		void quick_sort_pivot_middle(int first, int last);
		void quick_sort_pivot_first(int first, int last);
		void quick_sort_pivot_random(int first, int last);

        //InsertionSort
	    void insertion_sort_iterative(int first, int last);
	    void insertion_sort_recursive(int first, int last);

	    void insertion_sort_binary(int first, int last);
	    int binarySearch(int item, int low, int high);

	    int countInversions(int first, int last);

	    //Hybrid
	    void quick_insertion_sort(int first, int last);
	    void quick_20_sort(int first, int last); // Stops when sub-array is of size 20

        void merge(int first, int mid, int last);
        void merge_insertion_sort(int first, int last);

        bool variant_linear_search(int item, int first, int last);
        bool linear_search(int item, int first, int last);
};

#include <vector>
#include <iostream>

using namespace std;

class InsertionSort {

    private:

	    vector<int> arr;
	    size_t size;
	    
    public:
		
		InsertionSort(int n);
	    void iterative();
	    void recursive(int last); //pass last index, i.e., size-1
	    void binary();
	    int countInversions();
	
        int& operator[](int index);
        void disp();
};


void InsertionSort::iterative() {

    for(int j = 1; j < size; j++ ) {
            
        int x = arr[j];
        
        int i = j-1;
        
        while(i > -1 && x < arr[i] ) {
        
            arr[i+1] = arr[i];
            i--;
        }
        
        arr[i+1] = x;
    }

}


void InsertionSort::recursive(int last) {

    int i;
    

    if (last > 1) {
    
        recursive(last - 1);    
    }
    
    int k = arr[last];
    i = last - 1;
        
    while (i >= 0  &&  arr[i] > k) {
        
        arr[i + 1] = arr[i];
        i = i-1;
    }
        
    arr[i + 1] = k;
}

void InsertionSort::binary() {

    for(int j = 1; j < size; j++ ) {
            
        int x = arr[j];
        
        int i = j-1;
        
        while(i > -1 && x < arr[i] ) {
        
            arr[i+1] = arr[i];
            i--;
        }
        
        arr[i+1] = x;
    }
}

int InsertionSort::countInversions() {

    int count = 0;

    for(int j = 1; j < size; j++) {
    
        for(int i = 0; i < j; i++) {
        
            if(arr[i] > arr[j]) {
                
                count++;
            }
        }
    }
    
    
    return count;
}


InsertionSort::InsertionSort(int n) {
    
    size = n;
    arr.resize(n);
}


int& InsertionSort::operator[](int index) {

    if(index < 0 || index >= size) {
        cout << "ERROR: Index out of range, returning last elt..."  << endl;
        return arr[size-1];
    }
    
    else {
        return arr[index];
    }
}


void InsertionSort::disp() {
    
    cout << "<";
    
    for(int i = 0; i < size; i++) {
    
        cout << " " << arr[i] << " ";
    }
    
    cout  << ">" << endl;
}



int main (void) {

    int size;
    cout << "Enter array size: ";  
    cin >>  size;
    
    cout << endl << endl;
    
    InsertionSort insObj(size);
    
    for(int i = 0; i < size ; i++) {
    
        cout << "Enter val at ind" << i << ": ";
        cin >> insObj[i];
    }
    
    cout << endl  << endl <<"Your Array: ";
    insObj.disp();
    cout << endl << endl;
    
    cout << "NumInversions = " << insObj.countInversions() << endl << endl;
    
    cout << "sorting..." << endl;
    
    //insObj.iterative();
    insObj.recursive(size-1);
    
    cout << "Your Array (sorted): ";
    insObj.disp();
    cout << endl << endl;
    
    
    cout << "NumInversions = " << insObj.countInversions() << endl << endl;
    
    cout << "\n\nOkThnxBye!" << endl << endl;
    return 0;  
}





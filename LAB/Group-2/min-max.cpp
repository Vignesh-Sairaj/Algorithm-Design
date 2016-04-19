#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    int val;
    Node* nodePtr;
    bool operator<(const Node& other) {return val < other.val;}
};

bool lessThan(Node n1, Node n2) {
    return n1.val < n2.val;
}

bool greaterThan(Node n1, Node n2) {
    return n1.val > n2.val;
}

class MinMaxHeap {
private:
    vector<Node> minHeap;
    vector<Node> maxHeap;

public:
    MinMaxHeap(vector<int>& arr);

    void insert(int elt);

    int getMin();
    int getMax();

    int popMin();
    int popMax();

    void dispMin();
    void dispMax();
};

MinMaxHeap::MinMaxHeap(vector<int>& arr) {

    minHeap.resize(arr.size());
    maxHeap.resize(arr.size());


    for(int i = 0; i < arr.size(); i++) {

        minHeap[i].val = arr[i];
        maxHeap[i].val = arr[i];

        minHeap[i].nodePtr = &maxHeap[i];
        maxHeap[i].nodePtr = &minHeap[i];
    }

    make_heap(minHeap.begin(), minHeap.end(), greaterThan);

    for(int i = 0; i < arr.size(); i++) {
        (minHeap[i].nodePtr)->nodePtr = &minHeap[i]; ///minHeap[i].nodePtr points to a location in maxHeap whose
                                                     ///nodePtr must be reset
    }



    make_heap(maxHeap.begin(), maxHeap.end(), lessThan);

    for(int i = 0; i < arr.size(); i++) {
        (maxHeap[i].nodePtr)->nodePtr = &maxHeap[i];
    }
}

int MinMaxHeap::getMin() {

    return minHeap.front().val;
}

int MinMaxHeap::getMax() {

    return maxHeap.front().val;
}

void MinMaxHeap::insert(int elt) {

    maxHeap.resize(minHeap.size()+1);
    minHeap.resize(maxHeap.size());

    minHeap.back().val = elt;
    maxHeap.back().val = elt;

    minHeap.back().nodePtr = &maxHeap.back();
    maxHeap.back().nodePtr = &minHeap.back();

    push_heap(minHeap.begin(), minHeap.end(), greaterThan);

    for(int i = 0; i < minHeap.size(); i++) {
        (minHeap[i].nodePtr)->nodePtr = &minHeap[i];
    }

    push_heap(maxHeap.begin(), maxHeap.end(), lessThan);

    for(int i = 0; i < maxHeap.size(); i++) {
        (maxHeap[i].nodePtr)->nodePtr = &maxHeap[i];
    }
}




int MinMaxHeap::popMin() {

    Node minNode = minHeap.front();

    pop_heap(minHeap.begin(), minHeap.end(), greaterThan);
    minHeap.pop_back();

    for(int i = 0; i < minHeap.size(); i++) {
        (minHeap[i].nodePtr)->nodePtr = &minHeap[i];
    }


    *(minNode.nodePtr) = maxHeap.back();
    maxHeap.pop_back();

    push_heap(maxHeap.begin(), static_cast<vector<Node>::iterator>(minNode.nodePtr+1), lessThan);

    for(int i = 0; i < maxHeap.size(); i++) {
        (maxHeap[i].nodePtr)->nodePtr = &maxHeap[i];
    }

    return minNode.val;
}



int MinMaxHeap::popMax() {

    Node maxNode = maxHeap.front();

    pop_heap(maxHeap.begin(), maxHeap.end(), lessThan);
    maxHeap.pop_back();

    for(int i = 0; i < maxHeap.size(); i++) {
        (maxHeap[i].nodePtr)->nodePtr = &maxHeap[i];
    }


    *(maxNode.nodePtr) = minHeap.back();
    minHeap.pop_back();

    push_heap(minHeap.begin(), static_cast<vector<Node>::iterator>(maxNode.nodePtr+1), greaterThan);

    for(int i = 0; i < minHeap.size(); i++) {
        (minHeap[i].nodePtr)->nodePtr = &minHeap[i];
    }

    return maxNode.val;
}


void disp(vector<int>& arr) {

    cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        cout << " " << arr[i] << " ";
    }
    cout << ">" <<endl;
}






int main (void) {

    cout << "Enter num elts: ";
    int n; cin >> n;

    vector<int> inpArr(n);

    for(int i = 0; i < n; i++) {
        cout << endl << "Enter the element at index " << i << ": ";
        cin >> inpArr[i];
    }

    cout << endl;

    disp(inpArr);


    MinMaxHeap H(inpArr);

    cout << "popMin: " << H.popMin() << "  Max: " << H.getMax() << endl << endl;

    cout << "Min: " << H.getMin() << "  Max: " << H.getMax() << endl;



    cout << "popMax: " << H.popMax() << "  Min: " << H.getMin() << endl << endl;

    cout << "Max: " << H.getMax() << "  Min: " << H.getMin() << endl;

    

    return 0;
}


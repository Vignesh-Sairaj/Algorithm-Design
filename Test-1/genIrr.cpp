#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

void disp(vector<pair<int, int>> const &arr);
void disp(vector<int> const &arr);




int main (void) {

    int n;
    cout << "Enter n: ";
    cin >> n;

    int N = n*(n-1);

    vector<pair<int, int>> arrPairs;

    arrPairs.reserve(N);

    for(int i = 1; i <= n; i++) { //1-indexed

        for(int j = 1; j <= n; j++) {

            if(i != j) {

                pair<int, int> p(i, j);
                arrPairs.push_back(p);
            }
        }
    }
/*
    cout << endl << "Size of array = n*(n-1) = " << arrPairs.size() << endl << endl;
    disp(arrPairs);
    cout << endl << endl;
*/
    vector<int> bitStr(N);

    for (int i = 0; i < pow(2, N); i++) {

        int iCpy = i;
        for(int j = 0; j < N; j++) {

            bitStr[N-1-j] = (iCpy%2);
            iCpy /= 2;
        }
/*
        cout << endl;
        disp(bitStr);
        cout << endl;
*/

        cout << endl << "----------SUBSET-" << i << "------------" << endl;

        cout << "{";
        for(int j = 0; j < N; j++) {

            if(bitStr[j] == 1) {
                cout << " (" << arrPairs[j].first << ", " << arrPairs[j].second << ") ";
            }
        }
        cout << "}" << endl;
    }

    cout << endl << endl;
    return 0;
}


void disp(vector<pair<int, int>> const &arr) {

    int len = arr.size();

    cout << "<";
    for(int i = 0; i < len; i++) {

        cout << " (" << arr[i].first << ", " << arr[i].second << ") ";
    }

    cout << ">";
}

void disp(vector<int> const &arr) {

    int len = arr.size();

    cout << "<";
    for(int i = 0; i < len; i++) {

        cout << " " << arr[i] << " ";
    }

    cout << ">";
}

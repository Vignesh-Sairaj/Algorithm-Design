#include <iostream>

int main() {
    int n, q;
    cin >> n >> q;
    int **A = new int*[n];
    int **Q = new int*[q];

    int k;

    for(int i=0; i < n; i++) {
        cin >> k;
        A[i] = new int[k];
        for(int j = 0; j < k; j++) {
            cin >> A[i][j];
        }
    }

    for(int i=0; i < q; i++) {
        Q[i] = new int[2];
        cin >> Q[i][0] >> Q[i][1];
    }    

    for(int i=0; i < q; i++) {
        cout << A[Q[i][0]][Q[i][1]] << endl;
    }

	return 0;
}

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

class Triomino {

private:
    int k; //log2(side)
    pair<int, int> missing;
    vector<vector<int> > board;

public:
    Triomino(int lg2n, int x, int y); //  of board lg2(side) = lg2n = k; x & y coordinates of missing (row, column)
    void disp();
    void tile(int x_start, int x_end, int y_start, int y_end, pair<int, int> miss);
};


Triomino::Triomino(int lg2n, int x, int y) {

    k = lg2n;

    missing.first = x;
    missing.second = y;

    board.resize(pow(2, k));

    for(int i = 0; i < pow(2, k); i++) {
        board[i].resize(pow(2, k));
    }

    board[x][y] = 1;
}

void Triomino::disp() {

    for(int x = 0; x < pow(2, k); x++) {

        cout << "|";

        for(int y = 0; y < pow(2, k); y++) {

            char symbol;

            if( x == missing.first && y == missing.second) {
                symbol = 'M';
            }

            else if(board[x][y] == 1) {
                symbol = 'X';
            }

            else {
                symbol = 'O';
            }
            cout << " " << symbol << " ";
        }

        cout << "|" << endl;
    }

    cout << endl;
}

void Triomino::tile(int x_start, int x_end, int y_start, int y_end, pair<int, int> miss) {

    if((x_end - x_start) != (y_end - y_start)) {
        cout << "Error: Mismatched size";
        return;
    }

    else if(x_end < x_start) {
        cout << "Error: Negative size";
        return;
    }

    else if(x_end == x_start) {
        cout << "Base Case: (" << x_start << ", " << y_start << ")" << endl;
        return;
    }

    int x_mid = (x_start + x_end)/2, y_mid = (y_start + y_end)/2;

    //Xdivide

    if(miss.first <= (x_mid)) { // 1st or 2nd Quad

        if(miss.second <= (y_mid)) { //1st Quad

            board[x_mid][y_mid+1] = 1; //Q2
            board[x_mid+1][y_mid] = 1; //Q3
            board[x_mid+1][y_mid+1] = 1; //Q4

            cout << endl;
            disp();

            //Update Quad 1
            tile(x_start, x_mid, y_start, y_mid, miss);

            //Update Quad 2
            tile(x_start, x_mid, y_mid+1, y_end, make_pair(x_mid, y_mid+1));

            //Update Quad 3
            tile(x_mid+1, x_end, y_start, y_mid, make_pair(x_mid+1, y_mid));

            //Update Quad 4
            tile(x_mid+1, x_end, y_mid+1, y_end, make_pair(x_mid+1, y_mid+1));

        }

        else { //2nd Quad


            board[x_mid][y_mid] = 1; //Q1
            board[x_mid+1][y_mid] = 1; //Q3
            board[x_mid+1][y_mid+1] = 1; //Q4

            cout << endl;
            disp();

            //Update Quad 1
            tile(x_start, x_mid, y_start, y_mid, make_pair(x_mid, y_mid));

            //Update Quad 2
            tile(x_start, x_mid, y_mid+1, y_end, miss);

            //Update Quad 3
            tile(x_mid+1, x_end, y_start, y_mid, make_pair(x_mid+1, y_mid));

            //Update Quad 4
            tile(x_mid+1, x_end, y_mid+1, y_end, make_pair(x_mid+1, y_mid+1));

        }

    }

    else {  // 3rd or 4th Quad

        if(miss.second <= (y_mid)) { //3rd Quad


            board[x_mid][y_mid] = 1; //Q1
            board[x_mid][y_mid+1] = 1; //Q2
            board[x_mid+1][y_mid+1] = 1; //Q4

            cout << endl;
            disp();

            //Update Quad 1
            tile(x_start, x_mid, y_start, y_mid, make_pair(x_mid, y_mid));

            //Update Quad 2
            tile(x_start, x_mid, y_mid+1, y_end, make_pair(x_mid, y_mid+1));

            //Update Quad 3
            tile(x_mid+1, x_end, y_start, y_mid, miss);

            //Update Quad 4
            tile(x_mid+1, x_end, y_mid+1, y_end, make_pair(x_mid+1, y_mid+1));

        }

        else { //4th Quad

            board[x_mid][y_mid] = 1; //Q1
            board[x_mid][y_mid+1] = 1; //Q2
            board[x_mid+1][y_mid] = 1; //Q3

            cout << endl;
            disp();

            //Update Quad 1
            tile(x_start, x_mid, y_start, y_mid, make_pair(x_mid, y_mid));

            //Update Quad 2
            tile(x_start, x_mid, y_mid+1, y_end, make_pair(x_mid, y_mid+1));

            //Update Quad 3
            tile(x_mid+1, x_end, y_start, y_mid, make_pair(x_mid+1, y_mid));

            //Update Quad 4
            tile(x_mid+1, x_end, y_mid+1, y_end, miss);
        }
    }

}


int main (void) {

    int k;
    cout << "Enter k where 2^k is the # of elts in a side of the chessboard: ";
    cin >> k;

    int x, y;
    cout << "Enter the 2 coordinates of the missing elt: ";
    cin >> x >> y;

    Triomino t1(k, x, y);

    cout << "Board:" << endl;
    t1.disp();


    t1.tile(0, pow(2, k)-1, 0, pow(2, k)-1, make_pair(x, y));

    return 0;
}

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool cmp(pair<int, int> p1, pair<int, int> p2); //person p1, height = first, weight = second;
int max_tower(vector<pair<int, int> > vec);

void disp(vector<pair<int, int> > const &arr);
void disp(vector<int> const &arr);



bool cmp(pair<int, int> p1, pair<int, int> p2) {

	return (p1.first < p2.first) || ( (p1.first == p2.first) && (p1.second <= p2.second) );
}

bool LT(pair<int, int> p1, pair<int, int> p2) { // Less Than

	return (p1.first <= p2.first) && (p1.second <= p2.second);
}


int max_tower(vector<pair<int, int> > vec) {

	vector<int> max_so_far(vec.size(), 1); //init to 1

	cout << endl;
	disp(vec);
	cout << endl;

	sort(vec.begin(), vec.end(), &cmp);

	cout << endl;
	disp(vec);
	cout << endl;

	for(int j = 1; j < vec.size(); j++) {

		for(int i = 0; i < j; i++) {

			if(LT(vec[i], vec[j]) ) {

				if(max_so_far[i] + 1 > max_so_far[j]) {

					max_so_far[j] = max_so_far[i] + 1;
				}
			}
		}
	}

	cout << endl;
	disp(max_so_far);
	cout << endl;
	
	return *max_element(max_so_far.begin(), max_so_far.end());

}


void disp(vector<pair<int, int> > const &arr) {

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




int main(void) {

	int n;
	cout << "Enter n: " << endl;
	cin >> n;

	vector<pair<int, int> > vec(n);

	int h, w;

	for(int i = 0; i < n; i++) {


		cout << "Enter height of person " << i << ": ";
		cin >> h;

		cout << "Enter weight of person " << i << ": ";
		cin >> w;

		vec.push_back(make_pair(h, w));
	}

	cout << "Height of max tower: " << max_tower(vec) << endl << endl;

	return 0;
}

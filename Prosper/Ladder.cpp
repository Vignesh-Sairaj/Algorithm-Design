#include <iostream>
#include <string> 

using namespace std;


void ladder(int n, string soFar) { // n = numSteps remaining; soFar = history of steps taken so far

	if(n < 0) {
		return;
	}

	else if(n == 0) {

		cout << soFar << endl;
	}

	else {

		ladder(n-1, (soFar + "1"));
		ladder(n-2, (soFar + "2"));
	}
}

int main(void) {

	int n;
	cout << "Enter n: ";
	cin >> n;
	cout << endl;

	ladder(n, "");

	cout << endl;
}
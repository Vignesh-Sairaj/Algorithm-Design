#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>

/*
	ai: assembly costs for line i
	ti: transfer costs from line i
	eni: entry costs for line i
	exi: exit costs for line i
*/

//NOTE: Every vector is One-indexed
int assemblyDP(std::vector<int> a1, std::vector<int> a2, std::vector<int> t1,
				std::vector<int> t2, int en1, int en2, int ex1, int ex2);

int assemblyG(std::vector<int> a1, std::vector<int> a2, std::vector<int> t1,
				std::vector<int> t2, int en1, int en2, int ex1, int ex2);


void disp(std::vector<int>& arr);

void setRandom(std::vector<int>& arr, int low, int high); //one-indexed
void testRandInp();


int main()
{
	//One-indexed
	std::vector<int> a1 = {0, 7, 9, 3, 4, 8, 4};
	std::vector<int> a2 = {0, 8, 5, 6, 4, 5, 7};
	std::vector<int> t1 = {0, 2, 3, 1, 3, 4};
	std::vector<int> t2 = {0, 2, 1, 2, 2, 1};
	int en1 = 2, en2 = 4, ex1 = 3, ex2 = 2;

	std::cout << "\n" << assemblyDP(a1, a2, t1, t2, en1, en2, ex1, ex2) <<  std::endl;
	std::cout << "\n" << assemblyG(a1, a2, t1, t2, en1, en2, ex1, ex2) <<  std::endl;

    freopen("AssemblyLineOut.txt", "w", stdout);

    testRandInp();
	return 0;
}







int assemblyDP(std::vector<int> a1, std::vector<int> a2, std::vector<int> t1,
				std::vector<int> t2, int en1, int en2, int ex1, int ex2) {

	int n = a1.size()-1;

	//One-indexed
	std::vector<int> f1(n+1); //min costs line 1
	std::vector<int> f2(n+1); //min costs line 2

	std::vector<int> l1(n+1); //from which line to get to station j in line 1
	std::vector<int> l2(n+1); //from which line to get to station j in line 1

	f1[1] = en1 + a1[1]; l1[1] = 1;
	f2[1] = en2 + a2[1]; l2[1] = 2;

	for(int j = 2; j <= n; j++) {
		//Line 1
		if(f1[j-1] <= f2[j-1] + t2[j-1]) { //same line better than switching
			f1[j] = f1[j-1] + a1[j];
			l1[j] = 1;
		}
		else { //switching better than same line
			f1[j] = f2[j-1] + t2[j-1] + a1[j];
			l1[j] = 2;
		}

		//Line 2
		if(f2[j-1] <= f1[j-1] + t1[j-1]) { //same line better than switching
			f2[j] = f2[j-1] + a2[j];
			l2[j] = 2;
		}
		else { //switching better than same line
			f2[j] = f1[j-1] + t1[j-1] + a2[j];
			l2[j] = 1;
		}
	}

	int optCost;
	int line;

	if(f1[n] + ex1 <= f2[n] + ex2) {
		optCost = f1[n] + ex1;
		line = 1;
	}

	else {
		optCost = f2[n] + ex2;
		line = 2;
	}

	std::vector<int> stations(n+1);

	for(int j = n; j >= 1; j--) {

		if (line == 1) {
			stations[j] = 1;
			line = l1[j];
		}
		else if (line == 2) {
			stations[j] = 2;
			line = l2[j];
		}

		else {

			return -1;
		}
	}

	std::cout << "DP selection: ";
	disp(stations);
	//disp(f1);
	//disp(f2);

	return optCost;
}

void disp(std::vector<int>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
}

int assemblyG(std::vector<int> a1, std::vector<int> a2, std::vector<int> t1,
				std::vector<int> t2, int en1, int en2, int ex1, int ex2) {

	int n = a1.size()-1;

	int cost = 0;
	std::vector<int> stations(n+1);

	if(en1 + a1[1] <= en2 + a2[1]) {
		stations[1] = 1;
		cost += en1 + a1[1];
	}

	else {
		stations[1] = 2;
		cost += en2 + a2[1];
	}

	for (int j = 2; j <= n ; ++j) {

		if (stations[j-1] == 1) { //currently in line 1

			if (a1[j] <= t1[j-1] + a2[j]) { //if the cost in the immediate neighbourhood is better in same line
				stations[j] = 1;
				cost += a1[j];
			}

			else { //if the cost in the immediate neighbourhood is better after switching
				stations[j] = 2;
				cost += t1[j-1] + a2[j];
			}
		}

		else {

			if(a2[j] <= t2[j-1] + a1[j]) { //if the cost in the immediate neighbourhood is better in same line
				stations[j] = 2;
				cost += a2[j];
			}

			else {
				stations[j] = 1;
				cost += t2[j-1] + a1[j];
			}
		}
	}

	if(stations[n] == 1) {
		cost += ex1;
	}

	else if (stations[n] == 2) {
		cost += ex2;
	}

	else {
		return -1;
	}

	std::cout << "Greedy selection: ";
	disp(stations);

	return cost;
}


void setRandom(std::vector<int>& arr, int low, int high) {

    for (int i = 1; i < arr.size(); ++i) //one-indexed
    {
        arr[i] = rand()%(high-low+1) + low;
    }
}

void testRandInp() {

	int numTrials = 25, size = 5, low = 1, high = 10;

    std::vector<int> a1(size+1);
	std::vector<int> a2(size+1);
	std::vector<int> t1(size);
	std::vector<int> t2(size);
	int en1, en2, ex1, ex2;

    srand(time(NULL));

    int count = 0;

    for (int i = 0; i < numTrials; ++i)
    {
        setRandom(a1, low, high);
        setRandom(a2, low, high);
        setRandom(t1, low, high);
        setRandom(t2, low, high);

        en1 = rand()%(high-low+1) + low;
        en2 = rand()%(high-low+1) + low;
        ex1 = rand()%(high-low+1) + low;
        ex2 = rand()%(high-low+1) + low;

        std::cout << "\n\na1: ";
        disp(a1);
        std::cout << "a2: ";
        disp(a2);
        std::cout << "t1: ";
        disp(t2);
        std::cout << "t2: ";
        disp(t2);

        std::cout << "entry costs: " << en1 << ", " << en2 << " || exit costs: " << ex1 << ", " << ex2 << std::endl;

        int greedy = assemblyG(a1, a2, t1, t2, en1, en2, ex1, ex2);
        int dp = assemblyDP(a1, a2, t1, t2, en1, en2, ex1, ex2);

        if(dp == greedy) count++;

        std::cout << "\nDP: " << dp << " && Greedy: " << greedy << "  ::  (DP == Greedy)?" << (dp == greedy) << std::endl;
    }

    std::cout << "\n\n\nNumTrials = " << numTrials << " :: Number of times matching outputs = " << count << "\n\n";
}

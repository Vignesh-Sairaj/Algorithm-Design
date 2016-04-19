#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdlib>


void disp(std::vector<std::pair<std::string, std::string> > const &arr);
void disp(std::vector<std::string>& arr);

int genBijFn(std::vector<std::string>& A, std::vector<std::string>& B);



int main()
{
	std::cout << "Enter cardinality of sets: ";
	int n;
	std::cin >> n;

	std::vector<std::string> A(n); std::vector<std::string> B(n);

	std::cout << "\n" << std::endl;

	for (int i = 0; i < n; ++i) {

		std::cout << "[Set A]Enter unique elt at index " << i << ": ";
		std::cin >> A[i];
	}

	std::cout << "\n" << std::endl;

	for (int i = 0; i < n; ++i) {

		std::cout << "[Set B]Enter unique elt at index " << i << ": ";
		std::cin >> B[i];
	}

    freopen("BijectiveOut.txt", "w", stdout);

	int count = genBijFn(A, B);

    std::cout << "Number of bijective functions = " << count << std::endl;

	return 0;
}








int genBijFn(std::vector<std::string>& A, std::vector<std::string>& B) {

	int n = B.size();

    std::cout << "Sets A & B:\n";
    disp(A); disp(B);
	std::cout << "Printing all " << n << "! bijective functions...\n\n";

	std::sort(B.begin(), B.end());

    int count = 0;

	do { //generate all n! permtations of B

		std::vector<std::pair<std::string, std::string> > fn(n);

		for (int i = 0; i < n; ++i) {

			fn[i] = make_pair(A[i], B[i]);
		}

		disp(fn);
		std::cout << std::endl;

        count++;

	} while(std::next_permutation(B.begin(), B.end()));

	std::cout << "\n\n"  << "Done!" << "\n" << std::endl;

    return count;
}



void disp(std::vector<std::pair<std::string, std::string> > const &arr) {

	std::cout << "< ";
	for (int i = 0; i < arr.size(); ++i) {

		std::cout << " (" << arr[i].first << ", " << arr[i].second << ") ";
    }

    std::cout << ">";
}


void disp(std::vector<std::string>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
}

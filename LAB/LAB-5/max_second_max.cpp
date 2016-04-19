#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <cmath>

template <typename Cmp>
std::pair<Cmp, Cmp> max_second_max(std::vector<Cmp>& v);

template<typename T, typename A>
void disp(std::vector<T, A>& arr);

template<typename T, typename A1, typename A2>
void disp(std::vector<std::vector<T, A1>, A2 >& arr);

int main(void)
{
	std::cout << "Enter type: ";
	std::string type;
	std::cin >> type;

	std::cout << "Enter size: ";
	int size;
	std::cin >> size;

	if(type == "int") {

		std::vector<int> v;
		for(int i = 0; i < size; ++i) {

			std::cout << "Enter element at position " << i << ": ";
			int temp;
			std::cin >> temp;
			v.push_back(temp);
		}

		std::pair<int, int> ans;
		ans = max_second_max(v);
		std::cout << "Max: " << ans.first << " $$ SecondMax: " << ans.second << "\n";
	}

	else if(type == "float") {

		std::vector<float> v;
		for(int i = 0; i < size; ++i) {

			std::cout << "Enter element at position " << i << ": ";
			float temp;
			std::cin >> temp;
			v.push_back(temp);
		}

		std::pair<float, float> ans;
		ans = max_second_max(v);
		std::cout << "Max: " << ans.first << " $$ SecondMax: " << ans.second << "\n";
	}

	else if(type == "double") {
		std::vector<double> v;
		for(int i = 0; i < size; ++i) {

			std::cout << "Enter element at position " << i << ": ";
			double temp;
			std::cin >> temp;
			v.push_back(temp);
		}

		std::pair<double, double> ans;
		ans = max_second_max(v);
		std::cout << "Max: " << ans.first << " $$ SecondMax: " << ans.second << "\n";
	}

	else if(type == "char") {
		std::vector<char> v;
		for(int i = 0; i < size; ++i) {

			std::cout << "Enter element at position " << i << ": ";
			char temp;
			std::cin >> temp;
			v.push_back(temp);
		}

		std::pair<char, char> ans;
		ans = max_second_max(v);
		std::cout << "Max: " << ans.first << " $$ SecondMax: " << ans.second << "\n";
	}

	else if(type == "string") {
		std::vector<std::string> v;
		for(int i = 0; i < size; ++i) {

			std::cout << "Enter element at position " << i << ": ";
			std::string temp;
			std::cin >> temp;
			v.push_back(temp);
		}

		std::pair<std::string, std::string> ans;
		ans = max_second_max(v);
		std::cout << "Max: " << ans.first << " $$ SecondMax: " << ans.second << "\n";
	}

	else {
        std::cout << std::endl << "\nError: Type not supported!\naborting..." << std::endl;
	}

	return 0;
}

template <typename Cmp>
std::pair<Cmp, Cmp> max_second_max(std::vector<Cmp>& v) {

	int n = v.size();
	int numLevels = ceil(log2(n)) + 1;

	std::vector<std::vector<Cmp> > tree;

	tree.push_back(v);

	for (int i = 1; i < numLevels; ++i)
	{
		std::vector<Cmp> temp(static_cast<int>(ceil(tree[i-1].size()/2.0)));

		for (int j = 0; j < tree[i-1].size()/2; ++j)
		{
			Cmp win = tree[i-1][2*j]; //Comparing adjascent elements and pasing winner to next stage

			if(win < tree[i-1][2*j + 1]) {

				win = tree[i-1][2*j + 1];
			}

			temp[j] = win;
		}

		if (tree[i-1].size() % 2 == 1) // if size of prev level is odd
		{
			temp[temp.size()-1] = tree[i-1][tree[i-1].size()-1]; //last elt gets appended as such
			std::cout << "aha! << " << tree[i-1][tree[i-1].size()-1] <<  " << \n";
		}

		tree.push_back(temp);
	}

	disp(tree);


	Cmp Max = tree[numLevels-1][0];
	Cmp secondMax = std::min(tree[numLevels-2][0], tree[numLevels-2][1]);

	std::cout << "Here secondMax: " << secondMax << "\n";

	int maxInd = 0;
	for (int i = numLevels-2; i >= 0; --i)
	{
		if (tree[i][2*maxInd] == Max) // check if left child is Max
		{
			if (2*maxInd+1 < tree[i].size()) // check if right is not greater than size of vector
			{
				secondMax = std::max(tree[i][2*maxInd+1], secondMax);
			}

			maxInd = maxInd*2;
		}

		else {

			secondMax = std::max(tree[i][2*maxInd], secondMax);
			maxInd = maxInd*2+1;
		}
	}





	return std::make_pair(Max, secondMax);
}


template<typename T, typename A>
void disp(std::vector<T, A>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
}

template<typename T, typename A1, typename A2>
void disp(std::vector<std::vector<T, A1>, A2 >& arr) {

	std::cout << std::endl;

    for(int i = 0; i < arr.size(); ++i) {

        for(int j = 0; j < arr[i].size(); j++) {
            std::cout << " " << arr[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

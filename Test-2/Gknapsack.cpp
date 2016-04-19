#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstdio>


class ProfitNode
{
    public:
        int index;
        int weight;
        int profit;
        ProfitNode(int ind, int w, int p) {index = ind; weight = w; profit = p;}
        ProfitNode(){;}
        bool operator<(const ProfitNode& other) const {return (profit) > (other.profit);}
};



int knapsackDP(int W, std::vector<int>& weights, std::vector<int>& profits);
int knapsackG(int W, std::vector<int>& weights, std::vector<int>& profits);


void setRandom(std::vector<int>& arr, int low, int high);

void testRandInp();

void disp(std::vector<int>& arr);


int main() {

    std::freopen("knapsackOut.txt", "w", stdout);
/*	std::cout << "\nEnter size: ";
    int size;
    std::cin >> size;

    std::cout << "Enter max weight: ";
    int W;
    std::cin >> W;

    std::cout << "\n" << std::endl;

    std::vector<int> weights(size+1);

    for (int i = 1; i <= size; ++i) { //one-indexed

        std::cout << "Enter weight at index" << i << ": ";
        std::cin >> weights[i];
    }

    std::cout << "\n" << std::endl;

    std::vector<int> profits(size+1);
    for (int i = 1; i <= size; ++i) { //one-indexed

        std::cout << "Enter profit at index" << i << ": ";
        std::cin >> profits[i];
    }

    std::cout << "weights: ";
    disp(weights);
    std::cout << "profits: ";
    disp(profits);

    int greedy = knapsackG(W, weights, profits);
    int dp = knapsackDP(W, weights, profits);*/

    testRandInp();

	return 0;
}





int knapsackG(int W, std::vector<int>& weights, std::vector<int>& profits) { //one-indexed

	int n = weights.size()-1;

    std::vector<ProfitNode> vec; //zero indexed

    for(int i = 1; i <= n; i++) {

        vec.push_back(ProfitNode(i, weights[i], profits[i]));
    }

    std::sort(vec.begin(), vec.end());

    //std::cout << (vec[0] < vec[1]);

    std::vector<int> ans(n+1);

    int sumWeights = 0;
    //while current contents does not exceed capacity
    for (int i = 0; sumWeights < W && i < n; ++i) //CAUTION: Zero-Indexed
    {
        if (sumWeights + vec[i].weight <= W) { //if addition does not exceed capacity

        	ans[vec[i].index] = 1;
        	sumWeights += vec[i].weight;
    	}
    }



    int cost = 0, gain = 0;

    for (int i = 1; i <= n ; ++i)
    {
        gain += ans[i]*profits[i];
        cost += ans[i]*weights[i];
    }

/*    std::cout << "\n\nGreedy:\n";
    std::cout << "Selection: " << std::endl;
    disp(ans);
    std::cout << "opt cost = " << cost << " && opt gain = " << gain << "\n\n";*/

    return gain;
}



int knapsackDP(int W, std::vector<int>& weights, std::vector<int>& profits) { // vectors are one-indexed

    int n = weights.size()-1;
    std::vector<std::vector<int> > M(n+1, std::vector<int>(W+1, 0));

    for (int i = 1; i <= n; ++i) //start from 1
    {
        for (int w = 0; w <= W; ++w) //Normal DP algo
        {
            if (w < weights[i])
            {
                M[i][w] = M[i-1][w];
            }

            else
            {
                M[i][w] = std::max(M[i-1][w-weights[i]] + profits[i], M[i-1][w]);
            }
        }
    }

    int w = W;
    std::vector<int> ans(n+1, 0);
    //Determine selection vector
    for(int j = weights.size()-1; j >= 1; j--) //until 1
    {
        if((w >= weights[j]) && (M[j][w] == (M[j-1][w-weights[j]] + profits[j])))
        {
            ans[j] = 1;
            w = w-weights[j];
        }
    }


    int cost = 0, gain = 0;

    for (int i = 1; i <= n ; ++i)
    {
        gain += ans[i]*profits[i];
        cost += ans[i]*weights[i];
    }

/*    std::cout << "\n\nDP:\n";
    std::cout << "Selection: " << std::endl;
    disp(ans);
    std::cout << "opt cost = " << cost << " && opt gain = " << gain << "\n";
    std::cout << "M[n][W] = " << M[n][W] << "\n\n";*/

    return M[n][W];
}

void disp(std::vector<int>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
}

void setRandom(std::vector<int>& arr, int low, int high) {

    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = rand()%(high-low+1) + low;
    }
}

void testRandInp() {
    int size = 10, W = 100, numTrials = 50;
    std::vector<int> weights(size+1);
    std::vector<int> profits(size+1);

    srand(time(NULL));

    int count = 0;

    for (int i = 0; i < numTrials; ++i)
    {
        setRandom(weights, 1, 50);
        setRandom(profits, 1, 50);

        std::cout << "\n\nweights: ";
        disp(weights);
        std::cout << "profits: ";
        disp(profits);

        int greedy = knapsackG(W, weights, profits);
        int dp = knapsackDP(W, weights, profits);

        if(dp == greedy) count++;

        std::cout << "\nDP: " << dp << " && Greedy: " << greedy << "  ::  (DP == Greedy)?" << (dp == greedy) << std::endl;
    }

    std::cout << "\n\n\nNumTrials = " << numTrials << " :: Number of times matching outputs = " << count << "\n\n";
}

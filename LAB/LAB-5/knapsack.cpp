#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

template<typename T, typename A1, typename A2>
void disp(std::vector<std::vector<T, A1>, A2 >& arr);

template<typename T, typename A>
void disp(std::vector<T, A>& arr);

class NoProfitNode
{
    public:
        int index;
        int weight;
        NoProfitNode(int ind, int w) {index = ind; weight = w;}
        NoProfitNode(){;}
        bool operator<(const NoProfitNode& other) const {return weight < other.weight;}
};

class ProfitNode
{
    public:
        int index;
        double weight;
        double profit;
        ProfitNode(int ind, double w, double p) {index = ind; weight = w; profit = p;}
        ProfitNode(){;}
        bool operator<(const ProfitNode& other) const {return (profit/weight) > (other.profit/other.weight);}
};



std::vector<int> knapsack(int W, std::vector<int>& weights);
std::vector<int> knapsack(int W, std::vector<int>& weights, std::vector<int>& profits);

std::vector<double> knapsack(double W, std::vector<double>& weights, std::vector<double>& profits, bool fractional = false);

int main(void)
{
    std::cout << "Enter type (_F_ractional/_I_ntegral weights): ";
    std::string Wtype;
    std::cin >> Wtype;

    std::cout << "Enter type (_F_ractional/_I_ntegral selection): ";
    std::string Stype;
    std::cin >> Stype;

    std::cout << "\nEnter size: ";
    int size;
    std::cin >> size;




    if (Wtype == "I") { //Integer wieghts and profits
        

        std::cout << "Enter max weight: ";
        int W;
        std::cin >> W;

        std::cout << std::endl;

        std::vector<int> weights(size+1);

        for (int i = 1; i <= size; ++i) { //one-indexed

            std::cout << "Enter weight at index" << i << ": ";
            std::cin >> weights[i];
        }

        if(Stype == "I") { //0/1 Knapsack

            std::cout << "\nEnter whether profits will be specified or not (1 = yes; 0 = no):  ";
            bool pGiven;
            std::cin >> pGiven;


            if(pGiven == true) { //profits specified

                std::vector<int> profits(size+1);

                for (int i = 1; i <= size; ++i) { //one-indexed

                    std::cout << "Enter profit at index" << i << ": ";
                    std::cin >> profits[i];
                }

                std::cout << "weights: ";
                disp(weights);
                std::cout << "profits: ";
                disp(profits);


                
                std::vector<int> ans = knapsack(W, weights, profits);
                std::cout << "\nresult:\n";
                disp(ans);

                int cost = 0, gain = 0;

                for (int i = 1; i <=size ; ++i)
                {
                    gain += ans[i]*profits[i];
                    cost += ans[i]*weights[i];
                }

                std::cout << "opt cost = " << cost << " && opt gain = " << gain << "\n\n";
            }

            else // variant-knapsack (without profits)
            {
                std::vector<int> ans = knapsack(W, weights);
                std::cout << "\nresult:\n";
                disp(ans);

                int cost = 0;

                for (int i = 1; i <=size ; ++i)
                {
                    cost += ans[i]*weights[i];

                }

                std::cout << "opt cost = " << cost << "\n\n";
            }


        }

        else if (Stype == "F"){

            std::cout << "Fractional selection for integral weights not supported.\nAborting...\n" << std::endl; 
        }

        else {
            std::cout << "Invalid response.\nAborting...\n" << std::endl;
            return 1;
        }


    }


    else if (Wtype == "F") {

        std::cout << "Enter max weight: ";
        double W;
        std::cin >> W;

        std::vector<double> weights(size+1);

        for (int i = 1; i <= size; ++i) { //one-indexed

            std::cout << "Enter weight at index" << i << ": ";
            std::cin >> weights[i];
        }

        std::vector<double> profits(size+1);

        for (int i = 1; i <= size; ++i) { //one-indexed

            std::cout << "Enter profit at index" << i << ": ";
            std::cin >> profits[i];
        }

        std::cout << "weights: ";
        disp(weights);
        std::cout << "profits: ";
        disp(profits);

        std::vector<double> ans;

        if (Stype == "F") { //fractional

            ans = knapsack(W, weights, profits, true);
        }

        else if (Stype == "I"){ // 0/1 knapsack

            ans = knapsack(W, weights, profits);
        }

        else {

            std::cout << "Invalid response.\nAborting...\n" << std::endl;
            return 1;
        }

        std::cout << "\nresult:\n";
        disp(ans);

        double cost = 0, gain = 0;
        for (int i = 1; i <=size ; ++i)
        {
            gain += ans[i]*profits[i];
            cost += ans[i]*weights[i];
        }

        std::cout << "opt cost = " << cost << " && opt gain = " << gain << "\n\n";

    }

    else {

        std::cout << "Invalid response.\nAborting...\n" << std::endl;
        return 1;
    }


    return 0;
}

std::vector<int> knapsack(int W, std::vector<int>& weights, std::vector<int>& profits) { // vectors are one-indexed

    int n = weights.size()-1;
    std::vector<std::vector<int> > M(n+1, std::vector<int>(W+1, 0));
    disp(M);

    for (int i = 1; i <= n; ++i) //start from 1
    {
        for (int w = 0; w <= W; ++w)
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
    for(int j = weights.size()-1; j >= 1; j--) //until 1
    {
        if(std::max(M[j-1][w-weights[j]] + profits[j], M[j-1][w]) == M[j-1][w-weights[j]] + profits[j])
        {
            ans[j] = 1;
            w = w-weights[j];
        }
    }

    std::cout << "Max gain = " << M[n][W] << std::endl;

    return ans;
}



std::vector<int> knapsack(int W, std::vector<int>& weights) { //one-indexed

    int n = weights.size()-1;

    std::vector<NoProfitNode> vec; //zero indexed

    for(int i = 1; i <= n; i++) {

        vec.push_back(NoProfitNode(i, weights[i]));
    }

    std::sort(vec.begin(), vec.end());

    //std::cout << (vec[0] < vec[1]);

    std::vector<int> ans(n+1);

    int sumWeights = 0;
    //while the new addition does not exceed capacity
    for (int i = 0; sumWeights + vec[i].weight <= W && i < n; ++i) //CAUTION: Zero-Indexed
    {
        ans[vec[i].index] = 1;
        sumWeights += vec[i].weight;
    }

    return ans;
}

std::vector<double> knapsack(double W, std::vector<double>& weights, std::vector<double>& profits, bool fractional) {
    if (fractional == true) {

        int n = weights.size()-1;

        std::vector<ProfitNode> vec; //zero indexed

        for(int i = 1; i <= n; i++) {

            vec.push_back(ProfitNode(i, weights[i], profits[i]));
        }

        std::sort(vec.begin(), vec.end());

        //std::cout << (vec[0] < vec[1]);

        std::vector<double> ans(n+1);

        double sumWeights = 0;
        //while the new addition does not exceed capacity
        int i = 0;
        for (i = 0; sumWeights + vec[i].weight <= W && i < n; ++i) //CAUTION: Zero-Indexed
        {
            ans[vec[i].index] = 1;
            sumWeights += vec[i].weight;
        }

        if (sumWeights < W && i < n) //There's still some room left and objects left (and the next obj is obviously too large to fit)
        {
            ans[vec[i].index] = (W-sumWeights)/vec[i].weight;
            sumWeights += ans[vec[i].index]*vec[i].weight;
        }

        std::cout << "CHECK: sumWeights (should be W) = " << sumWeights << "\n";

        return ans;
    }

    else {

        int n = weights.size()-1;
        std::vector<int> opt(n+1); //optimal so far
        std::vector<int> sub(n+1); //current sub-set

        double optGain = 0; //Best gain seen so far
        int iCpy;
        for (int i = 0; i < pow(2, n); i++) { //generate all subsets of n elts

            iCpy = i;
            for(int j = 0; j < n+1; j++) { //for all n+1 bits

                sub[n-j] = (iCpy%2);
                iCpy /= 2;
            }

            disp(sub);

            double cost = 0, gain = 0;
            for (int i = 1; i <= n ; ++i)
            {
                gain += sub[i]*profits[i];
                cost += sub[i]*weights[i];
            }


            if(cost <= W && gain > optGain) {
                opt = sub;
                optGain = gain;
            }
        }

        std::vector<double> ans(opt.begin(), opt.end());
        return ans;
    }
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

template<typename T, typename A>
void disp(std::vector<T, A>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
}


void disp(std::vector<int>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); i++) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
}


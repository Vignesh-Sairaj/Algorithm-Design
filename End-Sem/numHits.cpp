#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <cstdlib>
#include <ctime>

constexpr int numCards = 30;
constexpr int numSim = 100000;


void disp(const std::vector<int>& v) {

    std::cout << "(";

    for (auto x : v) {
            std::cout << " " << x << " ";
    }
    std::cout << ")" << std::endl;
}


void initialize_and_permute(std::vector<int>& permutation) {

    for (int i = 0; i < permutation.size(); i++) {
        int j = rand()%(i+1); //roughly uniform[0, i]
        permutation[i] = permutation[j];   /* Swap an existing element [j] to position [i] */
        permutation[j] = i;    /* ...and put newly-initialized element [i] in position [j] */
    }
}


int numHits(const std::vector<int>& v) {

    if(v.size() != numCards) throw std::runtime_error("Num of elts must be 30\n");

    int num = 0;

    for (int i = 0; i < numCards; ++i) {
        if (v[i] == i) {
            
            //std::cout << "Hit! at" << "(" << i << ")\t"; 
            ++num;
        }
    }

    return num;
}




std::pair<double, double> runSim() {

    std::vector<int> v(numCards);

    double sumNumHits = 0;
    double sumNumHitsSq = 0;

    for (int i = 0; i < numSim; ++i) {
        initialize_and_permute(v);
        //disp(v);


        int n = numHits(v);

        //std::cout << "num Hits = " << n  << "\n\n";

        sumNumHits += n;
        sumNumHitsSq += n*n;
    }

    double expect = sumNumHits/numSim;
    double var = (sumNumHitsSq/numSim) - expect*expect;

    return std::make_pair(expect, var);
}






int main(void) {
    srand(time(NULL));


    std::pair<double, double> p = runSim();

    std::cout << "Expectation: " << p.first << "    Variance: " << p.second << std::endl;

    return 0;
}
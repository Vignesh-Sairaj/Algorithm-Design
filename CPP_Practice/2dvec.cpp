#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main(void) {

    std::vector<std::vector<int> > dummy(4, std::vector<int>(4));

    for(int i = 0; i < dummy.size(); ++i) {

        for(int j = 0; j < dummy[i].size(); j++) {
            dummy[i][j] = i-j;
        }
    }
    for(int i = 0; i < dummy.size(); ++i) {

        for(int j = 0; j < dummy[i].size(); j++) {
            std::cout << " " << setw(3) << dummy[i][j] << " ";
        }

        std::cout << std::endl;
    }


    return 0;
}

#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>

std::pair<double, std::vector< std::vector<int> > > opt_BST(std::vector<double>& p, std::vector<double>& q);
void postorder(std::vector<std::vector<int> >& r, int i, int j, int indent = 0);

void disp(std::vector<std::vector<int> >& arr);
void disp(std::vector<double>& arr);
void disp(std::vector<std::vector<double> >& arr);

int main(void) {
	int n;
	std::cout << "Enter number of nodes in BST: ";
	std::cin >> n;

	std::vector<double> p(n+1); //p[i] probability of elt at index i !!NOTE: array is one-indexed!!
	std::vector<double> q(n+1); //q[i] probability of gap i between elts at indices i and i+1

	for (int i = 1; i <= n ; ++i) //ONE-INDEXED
	{
		std::cout << "Enter the probability that a search key would have the value of the node at index " << i << ": ";
		std::cin >> p[i];
	}

	std::cout << std::endl;

	for (int i = 0; i <= n ; ++i)
	{
		std::cout << "Enter the probability that a search key would have a value between the nodes at "
				  << i << " and " << i+1 << ": ";
		std::cin >> q[i];
	}

    disp(p); disp(q);

	std::pair<double, std::vector< std::vector<int> > > pr;
	pr = opt_BST(p, q);

	std::cout << std::endl << "\nMin Cost: " << pr.first << "\n\n";

    disp(pr.second);

    postorder(pr.second, 0, n);

	return 0;
}


std::pair<double, std::vector< std::vector<int> > > opt_BST(std::vector<double>& p, std::vector<double>& q) {

	int n = q.size() - 1;

	std::vector< std::vector<double> > w(n+1, std::vector<double>(n+1)); // vector of vectors of size n+1 X n+1
	std::vector< std::vector<double> > c(n+1, std::vector<double>(n+1)); // vector of vectors of size n+1 X n+1
	std::vector< std::vector<int> > r(n+1, std::vector<int>(n+1)); // vector of vectors of size n+1 X n+1

	/*
		w[i][j] = sum of all p[m] and q[n] with
		i <  m <= j and
		i <= n <= j

		r[i][j] = index of optimal root for subtree (i, j]
	*/


	for (int i = 0; i <= n; ++i)
	{
		w[i][i] = q[i]; r[i][i] = 0; c[i][i] = 0;
		w[i][i+1] = q[i] + q[i+1] + p[i+1];
		r[i][i+1] = i+1; //Only 1 elt in range
		c[i][i+1] = w[i][i+1];
	}

	for (int m = 2; m <= n; ++m) //m = size of subarray
	{
		for (int i = 0; i <= n-m; ++i) // i = start index
		{
			int j = i + m; // end index


			//Find k that minimises c[i][k-1] + c[k][j] ====== root in (i, j]
			int mink = i+1;
            double minSum = c[i][i] + c[i+1][j];
			for(int k = i+1; k <= j; ++k) {
				if (c[i][k-1] + c[k][j] < minSum) {
					mink = k;
                    minSum = c[i][k-1] + c[k][j];
				}
			}

			w[i][j] = w[i][j-1] +  p[j] + q[j];
			c[i][j] = w[i][j] + minSum;
			r[i][j] = mink;
		}
	}

    std::pair<double, std::vector< std::vector<int> > > pr(c[0][n], r);
    std::cout << "Min Cost (in Fn)" << pr.first << std::endl;
    disp(pr.second);
    std::cout << "Cost (in Fn)" << std::endl;
    disp(c);

    std::cout << "Going to exit" << std::endl;
	return pr;
}







void disp(std::vector<std::vector<int> >& arr) {

    for(int i = 0; i < arr.size(); ++i) {

        for(int j = 0; j < arr[i].size(); j++) {
            std::cout << " " << arr[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void disp(std::vector<std::vector<double> >& arr) {

	for(int i = 0; i < arr.size(); ++i) {

        for(int j = 0; j < arr[i].size(); j++) {
            std::cout << " " << arr[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void disp(std::vector<double>& arr) {

    std::cout << "<";

    for(int i = 0; i < arr.size(); ++i) {

        std::cout << " " << arr[i] << " ";
    }

    std::cout << ">" << std::endl;
    
}


void postorder(std::vector<std::vector<int> >& r, int i, int j, int indent)
{
    if(r[i][j]) {
        if(r[i][r[i][j]-1]) postorder(r, i, r[i][j]-1, indent+4);
        if(r[r[i][j]][j]) postorder(r, r[i][j], j, indent+4);

        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout<< r[i][j] << "\n ";
    }
}
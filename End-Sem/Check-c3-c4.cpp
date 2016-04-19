#include <vector>
#include <list>
#include <iostream>
#include <stdexcept>
#include <queue>

class Graph {
public:

    std::vector<std::vector<unsigned> > adjMat;
    size_t numVert;
    bool directed;

    Graph(unsigned numV, bool dir = true);
    bool addEdge(unsigned from, unsigned to); //indices
    bool removeEdge(unsigned from, unsigned to);

    void disp();
};




Graph::Graph(unsigned numV, bool dir) {

    numVert = numV;
    directed = dir;
    adjMat.resize(numVert + 1); //Extra row for in degree

    for(unsigned i = 0; i <= numVert; i++) {
        adjMat[i].resize(numVert+1); //Extra column for out degree
    }
}

bool Graph::addEdge(unsigned from, unsigned to) {

    if(from >= 1 && from <= numVert && to >=1 && to <= numVert && to != from ) { //check range

        if(adjMat[from][to]) { //if the edge currently does not exist
            return false;
        }

        else {

            adjMat[from][to] = 1;
            ++adjMat[from][0]; //incr out deg of from
            ++adjMat[0][to]; //incr in deg of to

            ++adjMat[0][0]; //SUM OF IN & OUT DEG

            if(!directed) { //If undirected, also add corresponding edge

                adjMat[to][from] = 1;
                ++adjMat[to][0];
                ++adjMat[0][from];

                ++adjMat[0][0]; //SUM OF IN & OUT DEG
            }

            return true;
        }

    }

    throw std::runtime_error("Error: Index out of range!\n");  //stopping the program
}

bool Graph::removeEdge(unsigned from, unsigned to) {
    if(from >= 1 && from <= numVert && to >=1 && to <= numVert) { //check range

        if(adjMat[from][to] == 0) { //No edge to remove
            return false;
        }

        else {

            adjMat[from][to] = 0;
            --adjMat[from][0]; //decr out deg of from
            --adjMat[0][to]; //decr in deg of to

            --adjMat[0][0]; //SUM OF IN & OUT DEG

            if(!directed) { //If undirected, also remove corresponding edge

                adjMat[to][from] = 0;
                --adjMat[to][0];
                --adjMat[0][from];

                --adjMat[0][0]; //SUM OF IN & OUT DEG
            }

            return true;
        }

    }

    throw std::runtime_error("Error: Index out of range!\n");
}

void Graph::disp() {

    std::cout << std::endl;

    for (unsigned i = 0; i <= numVert; i++) {
            for (unsigned j = 0; j <= numVert; j++) {
                std::cout << " " << adjMat[i][j] <<  " ";
            }

            std::cout << std::endl;
        }
}

void disp(std::list<std::vector<unsigned>>& v);
std::list<std::vector<unsigned>> findC3 (Graph g);
std::list<std::vector<unsigned>> findC4 (Graph g);



std::list<std::vector<unsigned>> findC3 (Graph g) {

    if(g.directed) {
        throw std::runtime_error("find C3 has been implemented for undirected graphs only.\n");
    }

    std::list<std::vector<unsigned>> ls;

    for (unsigned i = 1; i <= g.numVert; ++i) {

        for (unsigned j = 1; j < i; ++j) {

            if (g.adjMat[i][j]) {
                for (unsigned k = 1; k < j; ++k) {

                    if (g.adjMat[j][k] and g.adjMat[k][i]) {
                        std::vector<unsigned> v{i, j, k};
                        ls.push_back(v);
                    }
                }
            }
        }
    }

    return ls;
}

std::list<std::vector<unsigned>> findC4 (Graph g) {

    if(g.directed) {
        throw std::runtime_error("find C4 has been implemented for undirected graphs only.\n");
    }

    std::list<std::vector<unsigned>> ls;

    for (unsigned i = 0+1; i <= g.numVert; ++i) {

        for (unsigned j = i+1; j <= g.numVert; ++j) {

            for (unsigned k = j+1; k <= g.numVert; ++k) {

                for (unsigned l = k+1; l <= g.numVert; ++l) {

                    if(g.adjMat[i][j] and g.adjMat[j][k] and g.adjMat[k][l] and g.adjMat[l][i]) {
                        ls.push_back(std::vector<unsigned> {i, j, k, l});
                    }

                    if(g.adjMat[i][k] and g.adjMat[k][j] and g.adjMat[j][l] and g.adjMat[l][i]) {
                        ls.push_back(std::vector<unsigned> {i, k, j, l});
                    }

                    if(g.adjMat[i][j] and g.adjMat[j][l] and g.adjMat[l][k] and g.adjMat[k][i]) {
                        ls.push_back(std::vector<unsigned> {i, j, l, k});
                    }
                }
            }
        }
    }

    return ls;
}










void disp(const std::list<std::vector<unsigned>>& v) {

    std::cout << "(";

    for (auto x : v) {

        std::cout << " {";
        for (auto e : x) {
            std::cout << " " << e << " ";
        }
        std::cout << "} ";
    }

    std::cout << ")" << std::endl;
}





int main(void) {

    Graph g {5, false};
    g.addEdge(1, 3);
    g.addEdge(3, 2);
    g.addEdge(2, 4);
    g.addEdge(4, 1);
    g.disp();

    std::cout << std::endl;

    disp(findC4(g));
    return 0;
}

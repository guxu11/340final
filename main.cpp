#include <iostream>
#include "Graph.h"

int main() {
    // Create a Graph and manually set the adjList for testing
    Graph g1;
    g1.adjList = {new Node(1), new Node(2)};
    g1.adjList[0]->next = new Node(2);

    // Test assignment operator
    Graph g2;
    g2 = g1;

    // Check if the adjacency lists are equal
    if (g1.getAdjList() == g2.getAdjList()) {
        std::cout << "Test passed: Graph assignment operator works correctly." << std::endl;
    } else {
        std::cerr << "Test failed: Graph assignment operator does not work correctly." << std::endl;
    }

    return 0;
}

#include <iostream>
#include "Graph.h"
#include "unittests.h"

int main() {
    // Create a Graph and manually set the adjList for testing
    Graph g1;
//    Node* n1 = new Node(1);
//    Node* n2 = new Node(2);
//    g1.adjList = {n1, n2};
//    g1.adjList[0]->next = new Node(2);
//    g1.adjList[1]->next = new Node(1);
//    g1.adjList[1]->next->pi = n2;
//
//    // Test assignment operator
//    Graph g2;
//    g2.adjList = {new Node(100)};
//    g2 = g1;
//    g1.addEdge(1,2);
//    g1.addEdge(2,3);
//    g1.addEdge(1,4);
    std::vector<std::pair<int, int>> edges = {{1,2}, {2,3}, {1,4}};

    g1.addEdges(edges);
    // Check if the adjacency lists are equal
//    if (g1.getAdjList() == g2.getAdjList()) {
//        std::cout << "Test passed: Graph assignment operator works correctly." << std::endl;
//    } else {
//        std::cerr << "Test failed: Graph assignment operator does not work correctly." << std::endl;
//    }

    return 0;
}

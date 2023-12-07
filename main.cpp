#include <iostream>
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
    std::vector<std::pair<int, int>> edges = {{1,2}, {2,3}, {1,4}, {3,4},{3,5}};

    g1.addEdges(edges);
    BFSTree(g1, g1.getAdjList()[4]);
    // Check if the adjacency lists are equal
//    if (g1.getAdjList() == g2.getAdjList()) {
//        std::cout << "Test passed: Graph assignment operator works correctly." << std::endl;
//    } else {
//        std::cerr << "Test failed: Graph assignment operator does not work correctly." << std::endl;
//    }
    std::cout << std::boolalpha << "testNodeDefaultConstructor: " << UNIT_TESTS::testNodeDefaultConstructor() << std::endl;
    std::cout << std::boolalpha << "testNodeConstructor2: " << UNIT_TESTS::testNodeConstructor2() << std::endl;
    std::cout << std::boolalpha << "testNodeConstructor3: " << UNIT_TESTS::testNodeConstructor3() << std::endl;
    std::cout << std::boolalpha << "testGraphDefaultConstructor: " << UNIT_TESTS::testGraphDefaultConstructor() << std::endl;
    std::cout << std::boolalpha << "testGraphCopyConstructor: " << UNIT_TESTS::testGraphCopyConstructor() << std::endl;
    std::cout << std::boolalpha << "testGraphCopyAssignment: " << UNIT_TESTS::testGraphCopyAssignment() << std::endl;
    UNIT_TESTS::testGraphDestructor();
    std::cout << std::boolalpha << "testGraphAddEdge: " << UNIT_TESTS::testGraphAddEdge() << std::endl;
    std::cout << std::boolalpha << "testGraphAddEdges: " << UNIT_TESTS::testGraphAddEdges() << std::endl;
    std::cout << std::boolalpha << "testGraphAddVertex: " << UNIT_TESTS::testGraphAddVertex() << std::endl;
    std::cout << std::boolalpha << "testBFS: " << UNIT_TESTS::testBFS() << std::endl;
    UNIT_TESTS::testBFSTree();
    UNIT_TESTS::testPrintPath();
    return 0;
}

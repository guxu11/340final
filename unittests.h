//
// Created by gu xu on 12/1/23.
//

#ifndef FINALPROJ_UNITTESTS_H
#define FINALPROJ_UNITTESTS_H

#include "Graph.h"

namespace UNIT_TESTS {
    // unit test of Node class default constructor without parameters
    inline bool testNodeDefaultConstructor() {
        Node node;
        if (node.nodeId != 0) return false;
        if (node.next != nullptr) return false;
        if (node.color != "") return false;
        if (node.dist != -1) return false;
        if (node.pi != nullptr) return false;
        return true;
    }

    // unit test of Node class Constructor with 1 parameter
    inline bool testNodeConstructor2() {
        Node node(1);
        if (node.nodeId != 1) return false;
        if (node.next != nullptr) return false;
        if (node.color != "") return false;
        if (node.dist != -1) return false;
        if (node.pi != nullptr) return false;
        return true;
    }

    // unit test of Node class Constructor with 3 parameters
    inline bool testNodeConstructor3() {
        Node node(1, "WHITE", 2);
        if (node.nodeId != 1) return false;
        if (node.next != nullptr) return false;
        if (node.color != "WHITE") return false;
        if (node.dist != 2) return false;
        if (node.pi != nullptr) return false;
        return true;
    }

    // unit test of Graph class default Constructor
    inline bool testGraphDefaultConstructor() {
        Graph graph;
        if (graph.getAdjList().size() != 0) return false;
        return true;
    }

    // unit test of Graph class copy constructor
    inline bool testGraphCopyConstructor() {
        Graph graph1;
        graph1.addEdges({{1,2}, {2,3}, {1,3}});

        Graph graph2 = Graph(graph1);
        if (graph2.getAdjList().size() != 3) return false;
        if (graph2.getAdjList().at(0)->nodeId != 1) return false;
        if (graph2.getAdjList().at(1)->nodeId != 2) return false;
        if (graph2.getAdjList().at(2)->nodeId != 3) return false;

        // test if the copy constructor is a deep copy
        graph1.getAdjList().at(0)->nodeId = 100;
        if (graph2.getAdjList().at(0)->nodeId != 1) return false;

        return true;
    }

    // unit test of Graph class copy assignment
    inline bool testGraphCopyAssignment() {
        Graph graph1;
        graph1.addEdges({{1,2}, {2,3}, {1,3}});

        Graph graph2;
        graph1.addEdges({{1,2}, {1,1}});
        graph2 = graph1;
        if (graph2.getAdjList().size() != 3) return false;
        if (graph2.getAdjList().at(0)->nodeId != 1) return false;
        if (graph2.getAdjList().at(1)->nodeId != 2) return false;
        if (graph2.getAdjList().at(2)->nodeId != 3) return false;

        // test if the copy constructor is a deep copy
        graph1.getAdjList().at(0)->nodeId = 100;
        if (graph2.getAdjList().at(0)->nodeId != 1) return false;

        return true;
    }

    // unit test of Graph class destructor
    inline void testGraphDestructor() {
        Graph graph1;
        std::vector<Node*> adjList;
        adjList.push_back(new Node(1, "TEST", 2));
        graph1.getAdjList() = adjList;
    }

    // unit test of Grap class addEdge
    inline bool testGraphAddEdge() {
        Graph graph;
        graph.addEdge(1, 2);
        if (graph.getAdjList().size() != 2) return false;
        if (graph.getAdjList().at(0)->nodeId != 1
            || graph.getAdjList().at(0)->next->nodeId != 2) return false;
        if (graph.getAdjList().at(1)->nodeId != 2
            || graph.getAdjList().at(1)->next->nodeId != 1) return false;
        return true;
    }

    // unit test of Graph class addEdges
    inline bool testGraphAddEdges() {
        Graph graph;
        graph.addEdges({{1, 2}, {1,3}});
        if (graph.getAdjList().size() != 3) return false;
        if (graph.getAdjList().at(0)->nodeId != 1
            || graph.getAdjList().at(0)->next->nodeId != 2) return false;
        if (graph.getAdjList().at(1)->nodeId != 2
            || graph.getAdjList().at(1)->next->nodeId != 1) return false;
        if (graph.getAdjList().at(2)->nodeId != 3
            || graph.getAdjList().at(2)->next->nodeId != 1) return false;
        return true;
    }

    // unit test of Graph class addVertex
    inline bool testGraphAddVertex() {
        Graph graph;
        graph.addVertex(1);
        if (graph.getAdjList().size() != 1) return false;
        if (graph.getAdjList().at(0)->nodeId != 1) return false;
        if (graph.getAdjList().at(0)->next != nullptr) return false;

        return true;
    }

    // unit test of BFS()
    inline bool testBFS() {
        Graph graph;
        std::vector<std::pair<int, int>> edges = {{1,2}, {2,3}, {1,4}, {3,4},{3,5}};
        graph.addEdges(edges);
        BFS(graph, graph.getAdjList().at(0));
        std::vector<Node*> list = graph.getAdjList();
        if (list.at(0)->dist != 0 || list.at(0)->color != "BLACK" || list.at(0)->pi != nullptr) return false;
        if (list.at(1)->dist != 1 || list.at(1)->color != "BLACK" || list.at(1)->pi->nodeId != 1) return false;
        if (list.at(2)->dist != 2 || list.at(2)->color != "BLACK" || list.at(2)->pi->nodeId != 2) return false;
        if (list.at(3)->dist != 1 || list.at(3)->color != "BLACK" || list.at(3)->pi->nodeId != 1) return false;
        if (list.at(4)->dist != 3 || list.at(4)->color != "BLACK" || list.at(4)->pi->nodeId != 3) return false;
        return true;
    }

    // unit test of BFSTree
    inline void testBFSTree() {
    }

    // unit test of PrintPath
    inline void testPrintPath() {
        Graph graph;
        std::vector<std::pair<int, int>> edges = {
                {1,2},
                {2,3},
                {1,4},
                {3,4},
                {3,5}
        };
        graph.addEdges(edges);

        PrintPath(graph, 2, 100);
    }
}

#endif //FINALPROJ_UNITTESTS_H

//
// Created by gu xu on 12/1/23.
//

#ifndef FINALPROJ_GRAPH_H
#define FINALPROJ_GRAPH_H

#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <iostream>

class Node
{
public:
    int nodeId;
    Node *next;
    std::string color;
    int dist;
    Node *pi;

    Node();
    Node(int nId);
    Node(int nId, std::string c, int d);
};

class Graph
{
public:
    Graph();
    Graph(const Graph &graph);
    ~Graph();
    std::vector<Node*> getAdjList();
    void setAdjList(std::vector<Node*> list);
    Graph &operator=(const Graph &graph);
    void addEdge(int u, int v);
    void addEdges(std::vector<std::pair<int, int>> edges);
    Node* addVertex(int nodeId);
private:
    std::vector<Node*> adjList;
    void addEdgeOrdered(Node* src, int toAdd);
};

void BFS(Graph &graph, Node* s);
void BFSTree(Graph &graph, int NodeId);
void PrintPath(Graph &graph, int src, int dest);
void PrintPath(Graph &graph, Node* src, Node* dest, Node* pi);
#endif //FINALPROJ_GRAPH_H

//
// Created by gu xu on 12/1/23.
//

#ifndef FINALPROJ_GRAPH_H
#define FINALPROJ_GRAPH_H

#include <vector>
#include <string>
#include <limits>

class Node
{
public:
    int nodeId;
    Node *next;
    std::string color;
    int dist;
    Node *pi;

    Node(int nId);
    Node(int nId, std::string c, int d);
};
class Graph
{
public:
    Graph();
    Graph(const Graph &graph);
    ~Graph();
    Graph &operator=(const Graph &graph);
    std::vector<Node*> getAdjList() const
    {
        return adjList;
    }
    void addEdge(int u, int v);
    void addVertex(int nodeId);
//private:
    std::vector<Node*> adjList;
};

void BFS(Graph &graph, Node s);
void BFSTree(Graph &graph, Node s);
void PrintPath(Graph &graph, Node src, Node dest);
#endif //FINALPROJ_GRAPH_H

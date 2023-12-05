//
// Created by gu xu on 12/1/23.
//

#ifndef FINALPROJ_GRAPH_H
#define FINALPROJ_GRAPH_H

#include "vector"

class Node
{
public:
    int nodeId;
    Node *next;
    Node(int nId, Node *n = nullptr)
    {
        nodeId = nId;
        next = n;
    };
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
    void addEdge(int v, int w);
    void addVertex(int nodeId);
//private:
    std::vector<Node*> adjList;
};

void BFS(Graph graph, Node s);
void BFSTree(Graph graph, Node s);
void PrintPath(Node src, Node dest);
#endif //FINALPROJ_GRAPH_H

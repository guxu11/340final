//
// Created by gu xu on 12/1/23.
//

#include "Graph.h"

Graph::Graph()
{
    adjList = std::vector<Node*>(0);
}

Graph::Graph(const Graph &graph) //copy
{
    std::vector<Node*> adjList(graph.adjList.size());
    int n = static_cast<int>(graph.adjList.size());
    for (int i = 0; i < n; i++)
    {
        Node *head = graph.adjList[i];
        Node *newHead = new Node(head->nodeId);
        Node *newTail = newHead;
        while (head->next)
        {
            head = head->next;
            Node *newNode = new Node(head->nodeId);
            newTail->next = newNode;
            newTail = newNode;
        }
        adjList[i] = newHead;
    }
    this->adjList = adjList;
}

Graph::~Graph()
{
    int n = static_cast<int>(adjList.size());
    for(int i = 0; i < n; i++)
    {
        Node *head = adjList[i];
        Node *toDel = head;
        while (toDel)
        {
            head = toDel->next;
            delete toDel;
            toDel = head;
        }
    }
}

Graph &Graph::operator=(const Graph &graph) //operator
{
    // hi
    // guxu test
    if(this != &graph)
    {
        int n = static_cast<int>(adjList.size());
        for (int i = 0; i < n; i++)
        {
            if(adjList[i] != nullptr)
            {
                Node *head = adjList[i];
                Node *toDel = head;
                while (toDel)
                {
                    head = toDel->next;
                    delete toDel;
                    toDel = head;
                }
            }
        }
        n = static_cast<int>(graph.adjList.size());
        adjList.resize(n);
        for(int i = 0; i < n; i++)
        {
            Node *head = graph.adjList[i];
            Node *newHead = new Node(head->nodeId);
            Node *current = newHead;
            while (head->next)
            {
                head = head->next;
                current->next = new Node(head->nodeId);
                current = current->next;
            }
            adjList[i] = newHead;
        }
    }
    return *this;
}

void Graph::addEdge(int u, int v)
{
    int n = static_cast<int>(adjList.size());
    bool isVertice = false;
    Node *current;
    for(int i = 0; i < n; i++) // check v exist
    {
        if (adjList[i]->nodeId == u)
        {
            isVertice = true;
            current = adjList[i];
        }
    }
    if(!isVertice) // Not exist add vertex
        addVertex(v);

    isVertice = false; // Initialize isVertice
    while(current)
    {
        if(current->nodeId == v)
        {
            isVertice = true;
            break;
        }
        current = current->next;
    }
    if(!isVertice)
    {
        current->next = new Node(v);
    }
}

void Graph::addVertex(int nodeId)
{
    adjList.push_back(new Node(nodeId));
}

void BFS(Graph graph, Node s)
{

}
void BFSTree(Graph graph, Node s)
{

}
void PrintPath(Node src, Node dest)
{

}
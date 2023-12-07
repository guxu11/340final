//
// Created by gu xu on 12/1/23.
//

#include "Graph.h"
#include <queue>
#include <iostream>

Node::Node(): nodeId(0), next(nullptr), dist(-1), color(""), pi(nullptr){};

Node::Node(int nId): nodeId(nId), next(nullptr), dist(-1), color(""), pi(nullptr) {}

Node::Node(int nId, std::string c, int d): nodeId(nId), color(c), dist(d), next(nullptr), pi(nullptr){}

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
        Node *newHead = new Node(head->nodeId, head->color, head->dist);
        Node *newTail = newHead;
        while (head->next)
        {
            head = head->next;
            Node *newNode = new Node(head->nodeId, head->color, head->dist);
            newTail->next = newNode;
            Node* temp = newTail;
            newTail = newNode;
            newTail->pi = temp;
        }
        adjList[i] = newHead;
    }
    this->adjList = adjList;
}

Graph::~Graph()
{
    // hook for test
    if (adjList.size() == 1 && adjList.at(0)->color == "TEST") {
        std::cout << "testGraphDestructor: true";
    }
    int n = static_cast<int>(adjList.size());
    for(int i = 0; i < n; i++)
    {
        Node *head = adjList[i];
        Node *toDel = head;
        while (toDel)
        {
            toDel->pi = nullptr;
            head = toDel->next;
            delete toDel;
            toDel = head;
        }
    }
}

Graph &Graph::operator=(const Graph &graph) //operator
{
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
                    toDel->pi = nullptr;
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
            Node *newHead = new Node(head->nodeId, head->color, head->dist);
            Node *current = newHead;
            while (head->next)
            {
                head = head->next;
                current->next = new Node(head->nodeId, head->color, head->dist);
                Node *temp = current;
                current = current->next;
                current->pi = temp;
            }
            adjList[i] = newHead;
        }
    }
    return *this;
}

std::vector<Node*> Graph::getAdjList() {
    return this->adjList;
}

void Graph::setAdjList(std::vector<Node*> list) {
    this->adjList = list;
}

void Graph::addEdgeOrdered(Node* src, int toAdd) {
    Node* p = src;
    while (p->next != nullptr) {
        if (p->nodeId == toAdd) {
            break;
        }
        p = p->next;
    }
    if (p->nodeId != toAdd) {
        p->next = new Node(toAdd);
    }
}
void Graph::addEdge(int u, int v)
{
    Node* nNode = addVertex(u);
    Node* vNode = addVertex(v);
    addEdgeOrdered(nNode, v);
    addEdgeOrdered(vNode, u);
}

Node* Graph::addVertex(int nodeId)
{
    Node* node = nullptr;
    for (Node* n: adjList) {
        if (n->nodeId == nodeId) {
            node = n;
            break;
        }
    }
    if (node == nullptr) {
        node = new Node(nodeId);
        adjList.push_back(node);
    }
    return node;
}

void Graph::addEdges(std::vector<std::pair<int, int>> edges) {
    for (std::pair<int, int> pair: edges) {
        addEdge(pair.first, pair.second);
    }
}

void BFS(Graph &graph, Node* s)
{
    int n = static_cast<int>(graph.getAdjList().size());
    for(int i = 0; i < n; i++) // Initialize
    {
        Node *current = graph.getAdjList().at(i);
        while(current)
        {
            current->color = "WHITE";
            current->dist = std::numeric_limits<int>::max();;
            current->pi = nullptr;
            current = current->next;
        }
    }
    s->color = "GREY";
    s->dist = 0;
    s->pi = nullptr;
    std::queue<Node*> queue;
    queue.push(s);
    while (!queue.empty()) {
        Node* node = queue.front();
        Node* head = node;
        queue.pop();
        while (node->next != nullptr) {
            Node* nextNode = graph.getAdjList().at(node->next->nodeId - 1);
            if (nextNode->color == "WHITE") {
                nextNode->pi = head;
                nextNode->color = "GREY";
                nextNode->dist = head->dist + 1;
                queue.push(nextNode);
            }
            node = node->next;
        }
        head->color = "BLACK";
    }
}
void BFSTree(Graph &graph, int NodeId) // print BFS tree
{
    Node* s = graph.getAdjList().at(NodeId - 1);
    BFS(graph, s);
    int max_dis = 3;
    for(int i = 0; i <= max_dis; i++)
    {
        for(auto Node : graph.getAdjList()) //push
        {
            if(Node->dist == i)
            {
                if(i != 0)
                    std::cout << " -> ";
                else
                    std::cout << "   ";
                std::cout << Node->nodeId;
                std::cout << std::endl;
                for(int j = 0; j < (i + 1) * 6; j++)
                    std::cout << " ";
            }
        }
    }
}
void PrintPath(Graph &graph, int src, int dest)
{
    if (src < 1 || src >= graph.getAdjList().size() || dest < 1 || dest >= graph.getAdjList().size()) {
        std::cerr << src << " or " << dest << " is not in the graph" << std::endl;
    }
    Node* srcNode = graph.getAdjList().at(src - 1);
    Node* destNode = graph.getAdjList().at(dest - 1);
    BFS(graph, srcNode);
    PrintPath(graph, srcNode, destNode, destNode->pi);
}

void PrintPath(Graph &graph, Node* src, Node* dest, Node* pi) {
    if (src == dest) {
        std::cout << src->nodeId;
    } else if (pi == nullptr) {
        std::cout << "no path from " << src->nodeId << " to " << dest->nodeId << "exists" << std::endl;
    } else {
        PrintPath(graph, src, dest->pi, dest->pi);
        std::cout << "->" << dest->nodeId;
    }
}
//
// Created by gu xu on 12/1/23.
//

#include "Graph.h"
#include <queue>

Node::Node(): nodeId(0), next(nullptr), dist(0), color("white"), pi(nullptr){};

Node::Node(int nId): nodeId(nId), next(nullptr), dist(0), color("white"), pi(nullptr) {}

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
    int n = static_cast<int>(graph.adjList.size());
    for(int i = 0; i < n; i++) // Initialize
    {
        Node *current = graph.adjList[i];
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
            Node* nextNode = graph.adjList.at(node->next->nodeId - 1);
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
void BFSTree(Graph &graph, Node* s)
{
    BFS(graph, s);
    // TODO: print tree
}
void PrintPath(Graph &graph, Node src, Node dest)
{

}
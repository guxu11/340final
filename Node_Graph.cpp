//
// Created by gu xu on 12/1/23.
//

#include "Node_Graph.h"

// non-parameter constructor for Node
Node::Node(): nodeId(0), next(nullptr), dist(-1), color(""), pi(nullptr){};

// Node's constructor with nId as a parameter
Node::Node(int nId): nodeId(nId), next(nullptr), dist(-1), color(""), pi(nullptr) {}

// Node's constructor with 3 parameters
Node::Node(int nId, std::string c, int d): nodeId(nId), color(c), dist(d), next(nullptr), pi(nullptr){}

// non-parameter constructor for Graph
Graph::Graph(): adjList(std::vector<Node*>(0)) {}

// copy constructor for Graph
Graph::Graph(const Graph &graph)
{
    std::vector<Node*> adjList(graph.adjList.size());
    int n = static_cast<int>(graph.adjList.size());
    // deep copy of each Node
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

// Destructor for Graph
Graph::~Graph()
{
    // hook for test
    if (adjList.size() == 1 && adjList.at(0)->color == "TEST") {
        std::cout << "testGraphDestructor: true";
    }
    // delete each Node in the adjList
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

// copy assignment operation overloading
Graph &Graph::operator=(const Graph &graph) //operator
{
    if(this != &graph)
    {
        // delete the old adjList
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
        // resize the adjList into the scale of graph to be copied
        // and do the deep copy
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

// accessor of adjList
std::vector<Node*> Graph::getAdjList() {
    return this->adjList;
}

// mutator of adjList
void Graph::setAdjList(std::vector<Node*> list) {
    this->adjList = list;
}

// helper method for addEdge
void Graph::addEdgeOrdered(Node* src, int toAdd) {
    Node* p = src;
    // find a place in the Node* chain to connect the node
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

// add one edge to the graph
void Graph::addEdge(int u, int v)
{
    // add two vertices of the edge to the graph
    Node* nNode = addVertex(u);
    Node* vNode = addVertex(v);
    // connect the vertices in the adjList
    addEdgeOrdered(nNode, v);
    addEdgeOrdered(vNode, u);
}

// add one vertex to the graph
Node* Graph::addVertex(int nodeId)
{
    Node* node = nullptr;
    // find if the nodeId exist
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

// add a batch of edges to the graph
void Graph::addEdges(std::vector<std::pair<int, int>> edges) {
    for (std::pair<int, int> pair: edges) {
        addEdge(pair.first, pair.second);
    }
}

// Breadth-first search
void BFS(Graph &graph, Node* s)
{
    int n = static_cast<int>(graph.getAdjList().size());
    // Initialize the graph
    for(int i = 0; i < n; i++)
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
    // push start into the queue
    s->color = "GREY";
    s->dist = 0;
    s->pi = nullptr;
    std::queue<Node*> queue;
    queue.push(s);
    while (!queue.empty()) {
        Node* node = queue.front();
        Node* head = node;
        queue.pop();
        // traverse the adjList of current node
        while (node->next != nullptr) {
            Node* nextNode = graph.getAdjList().at(node->next->nodeId - 1);
            if (nextNode->color == "WHITE") {
                // if the node is unvisited, push it into queue
                nextNode->pi = head;
                nextNode->color = "GREY";
                nextNode->dist = head->dist + 1;
                queue.push(nextNode);
            }
            node = node->next;
        }
        // after traverse
        head->color = "BLACK";
    }
}

// print the BFS tree
void BFSTree(Graph &graph, int src) // print BFS tree
{
    std::cout << "BFS tree starts at " << src << ": " << std::endl;
    Node* s = graph.getAdjList().at(src - 1);
    BFS(graph, s);
    // find the max distance from the start
    int max_dis = 0;
    for (Node* node: graph.getAdjList()) {
        if (node->dist > max_dis) {
            max_dis = node->dist;
        }
    }
    // traverse all the layers
    for(int i = 0; i <= max_dis; i++)
    {
        // print nodes in the same layer
        for(auto Node : graph.getAdjList()) //push
        {
            if(Node->dist == i)
            {
                // print space
                for(int j = 0; j < (i-1) * 4; j++)
                {
                    std::cout << " ";
                }
                // print arrows
                if(i != 0)
                {
                    std::cout << " -> ";
                }
                // print nodeId
                std::cout << Node->nodeId << std::endl;
            }
        }
    }
}

// print the shortest path from src to dest in a graph
void PrintPath(Graph &graph, int src, int dest)
{
    // if src or dest is not in the graph, throw error
    if (src < 1 || src > graph.getAdjList().size() || dest < 1 || dest > graph.getAdjList().size()) {
        std::cerr << src << " or " << dest << " is not in the graph" << std::endl;
    }
    std::cout << "Shortest Path from " << src << " to " << dest << ": " << std::endl;
    // find the Node pointer in the adjList with their nodeId
    Node* srcNode = graph.getAdjList().at(src - 1);
    Node* destNode = graph.getAdjList().at(dest - 1);
    BFS(graph, srcNode);
    PrintPath(graph, srcNode, destNode, destNode->pi);
}

// a helper method of PrintPath, a recursive method
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
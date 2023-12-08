## Final Project DesignDoc - Group 5

### 0. Group Members
- Xu Gu
  - design doc
  - structure of the project, prototypes
  - code implementation
  - unit tests
  - code review
- Chan-Chun Yen
  - structure of the project
  - code implementation
- Joyce Fu
  - structure of the project
  - make presentation

### 1. The high-level design: a list of entities and operations

#### Type 1. Node -> class Node

**Relevant Properties**

- `nodeId` -> `int`, id of each node
- `next` -> `Node*`, pointing to next adjacent vertex
- `color` -> `string`, used as a memo for BFS
- `pi` -> `Node*`, record which Node is the predecessor
- `dist` -> `int`, distance from the current vertex to the starter

**Relevant data operations:**

- `Node()` -> default constructor:  initialize a Node object with default values
- `Node(int nId)` -> constructor with 1 parameter nId:  initialize a Node object with a specific nodeId and other default values
- `Node(int nId, string color, int dist)` -> constructor with 3 parameters  

#### Type 2. Graph -> class Graph

**Relevant Properties**

- `adjList` -> `vector<Node*>`, **private** property. adjacent list representation of a graph

**Relevant data operations**

- `Graph()` -> default constructor, initialize the adjList with a 0-size vector
- `Graph(const Graph &graph)` -> copy constructor
- `~Graph()` -> destrcutor, release the memories of the adjList and the nodes stored inside
- `Graph &operator=(const Graph &graph)` -> copy operator overloader
- `getAdjList()` -> accessor for the adjList
- `setAdjList(vector<Node*>)` -> mutator of the adjList
- `void addEdgeOrdered(Node* src, int toAdd)` -> private method, a helper method for of addEdge: add an Node to the tail of an existing Node 
- `void addEdge(int v, int w)` -> add an edge v-w to the graph
- `void addEdges(vector<pair<int, int>> pairs)` -> add an edge v-w to the graph
- `Node* addVertex(int nodeId)` -> add a vertex to the graph, return the node

#### free-standing methods
- `void BFS(Graph &graph, Node* s)` -> Breath-first search for a graph from a specified start
- `void BFSTree(Graph &graph, int src)` -> print the BFS tree
- `void PrintPath(Graph &graph, int src, int dest)` -> call the recursive function below to print the shortest path from a specified start to a specified end
- `void PrintPath(Graph &graph, Node* src, Node* dest, Node* pi)` -> helper method to print path, a recursive function to print the shortest path from a specified start to a specified end

### 2 Implementation details

#### File split
- **Node_Graph.h**: contains the method declaration of Node class and Graph class
- **Node_Graph.cpp**: implementation of `Node`, `Graph` and stand-alone functions
- **unittests.h**: contains inline unittest functions
- **main.cpp**: run the unittests

#### Data Structures
- `vector` and `Node*` -> represent the adjacent list of a graph. Node pointer can represent a 
series of connected nodes. In the case a graph, it's a choice to hold all the adjacent vertices.
And the we use a vector to hold all the nodes.
- `queue` -> It's used in BFS. Queue is a first-in-first out data structure, which a good 
match in BFS because it can help us keep the order of distance from the start node.

#### Implementation of core methods
- `Graph::Graph(const Graph &graph)` -> copy constructor of class Graph
  - Step 1: initialize a adjList with the size of graph to be copied
  - Step 2: Create deep copied nodes from graph to be copied, and add the nodes to the adjancent list
- `Graph &Graph::operator=(const Graph &graph)` -> copy assignment operator of class Graph
  - Step 1: delete nodes in the original adjacent list
  - Step 2: resize the original adjacent list to the size of adjList in the graph to be copied
  - Step 3: Create deep copied nodes from graph to be copied, and add the nodes to the adjancent list
- `Node* Graph::addVertex(int nodeId)`, pseudocode is as follows
    ```
  addVertex(nodeId):
        initialize a new Node newVertex = NULL
        for each vertex n in the graph:
            if vertex.id == nodeId:
                newVertex = vertex
                break
        if newVertex == NULL:
            newVertex = Node(nodeId)
        return newVertex
  ```
- `void Graph::addEdge(int u, int v)`, pseudocode is as follows
    ```
  addEdge(u, v):
        add vertexU to graph
        add vertexV to graph
        if vertexV not in adjacent list of nodeU:
            add vertexV to the last of vertexU's adjacent list 
        if vertexU not in adjacent list of nodeV:
            add vertexU to the last of vertexV's adjacent list 
  ```
- `void BFS(Graph &graph, Node* s)`, Breadth-first Search of the graph, pseudocode can be found in page 7 of the slide
- `void BFSTree(Graph &graph, int src)`, pseudocode is as follows
    ```
    PrintBFSTree(G, src):
        BFS(G, src)
        max_dis = max dist of all the vertics from src
        for i = 0, 1, ..., max_dis:
            for each node in G:
              if node.dist == i:
                  print " " * ((i-1) * 4)
                  print ->
                  print node.nodeId
                  print newLine
  ```
- `void PrintPath(Graph &graph, Node src, Node dest)`, print the shortest path, pseudocode can be found in page 10 of the slide
### 3. Code
#### `Node_Graph.h`
```c++
//
// Created by gu xu on 12/1/23.
//

#include "Node_Graph.h"

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
```
#### `Node_Graph.cpp`
```c++
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
```
#### `unittests.h`
```c++
//
// Created by gu xu on 12/1/23.
//

#ifndef FINALPROJ_UNITTESTS_H
#define FINALPROJ_UNITTESTS_H

#include "Node_Graph.h"

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
        Graph graph;
        std::vector<std::pair<int, int>> edges = {
                {1,2},
                {1,3},
                {3,4},
                {2,5},
                {5,6}
        };
        graph.addEdges(edges);
        BFSTree(graph, 3);
    }

    // unit test of PrintPath
    inline void testPrintPath() {
        Graph graph;
        std::vector<std::pair<int, int>> edges = {
                {1,2},
                {1,3},
                {3,4},
                {2,5},
                {5,6}
        };
        graph.addEdges(edges);

        PrintPath(graph, 1, 6);
    }
}

#endif //FINALPROJ_UNITTESTS_H
```
#### `main.cpp`
```c++
#include <iostream>
#include "unittests.h"

int main() {
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
    std::cout << std::endl;
    UNIT_TESTS::testBFSTree();
    UNIT_TESTS::testPrintPath();
    return 0;
}
```
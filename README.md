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

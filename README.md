## Final Project DesignDoc



### 1. The high-level design: a list of entities and operations

#### Type 1. Node -> class Node

**Relevant Properties**

- `nodeId` -> `int`, id of each node
- `next` -> `Node*`, pointing to next adjacent vertex
- `color` -> `string`
- `pi` -> `Node*`
- `dist` -> `int`, distance from the current vertex to the starter

**Relevant data operations:**

- `Node()` -> default constructor:  initialize a Node object with default values

#### Type 2. Graph -> class Graph

**Relevant Properties**

- `adjList` -> `vector<Node*>`,adjacent list representation of a graph

**Relevant data operations**

- `Graph()` -> default constructor, initialize the adjList with a 0-size vector
- `Graph(const Graph &graph)` -> assignment constructor, 
- `~Graph()` -> release the memories of the adjList and the nodes stored inside
- `Graph &operator=(const Graph &graph)` -> 
- `void addEdge(int v, int w)` -> add an edge v-w to the graph
- `void addVertex(int nodeId)` -> 

### 2 Implementation details


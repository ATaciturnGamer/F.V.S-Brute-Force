#include <vector>
#include <string>
#include <map>
struct Node
{
    int dest;
    struct Node *next;
};
struct AdjacencyList
{
    struct Node *head;
};

class Graph
{
public:
    int V;
    int E;
    struct AdjacencyList *adjlist;
    std::map<std::string, int> label;

    bool isCyclicHelper(int u, bool visited[], int parent, int exclude[]);
public:
    Graph();
    Graph(int V);
    int getVertexSize();
    struct Node* newAdjListNode(int dest);
    void addNode(std::string key, int node);
    void addEdge(std::string src, std::string dest);
    bool isCyclic(int exclude[]);
};

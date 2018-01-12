#include "graph.h"
#include <iostream>
#include <stdio.h>

Graph::Graph()
{
    this->V = 0;
    this->E = 0;
    adjlist = new AdjacencyList;
}
Graph::Graph(int v)
{
    V = v;
    E = 0;
    adjlist = new AdjacencyList[v];
    for (int i = 0; i<v; i++)
    {
        adjlist[i].head = NULL;
    }
}

int Graph::getVertexSize(){return this->V;}

Node* Graph::newAdjListNode(int dest)

{
    Node* new_node = new Node;
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

void printGraph(Graph G)
{
    for (int i=0; i< G.V; i++)
    {
        Node* next = G.adjlist[i].head;
        while (next!=NULL) printf("%d",next->dest);
        printf("\n");
    }
}

void Graph::addNode(std::string key, int node)
{
    label[key] = node;
}

void Graph::addEdge(std::string src, std::string dest)

{
    int s,d;
    s = this->label[src];
    d = this->label[dest];
    if (s>V || d>V) return;
    Node* new_node = newAdjListNode(d);
    new_node->next = adjlist[s].head;
    adjlist[s].head = new_node;
    new_node = newAdjListNode(s);
    new_node->next = adjlist[d].head;
    adjlist[d].head = new_node;
}

bool Graph::isCyclicHelper(int u, bool visited[], int parent, int exclude[])
{
    visited[u] = true;

    struct Node* node = this->adjlist[u].head;
    while (node!=NULL)
    {
        // printf("%d->%d",u,node->dest);
        if (!visited[node->dest] and exclude[node->dest]==0)
        {
            // printf("CLEAR\n");
            if (isCyclicHelper(node->dest, visited, u, exclude)) return true;
        }
        else if (node->dest!=parent and exclude[node->dest]==0)
        {
            // printf("GOTCHA\n");
            // std::cout << visited[node->dest];
            return true;
        }
        node = node->next;
    }
    return false;
}

bool Graph::isCyclic(int exclude[])//exclude is a bit array
{
    bool visited[this->V];
    for (int i=0; i<this->V; i++) visited[i]=false;

    for (int u=0; u<this->V; u++)
    {
        if (!visited[u] and exclude[u]==0)
        {
            // printf("AGAIN %d\n",u);
            if (isCyclicHelper(u,visited,-1, exclude)) return true;
        }
    }
    return false;

}




// int main(int argc, char const *argv[]) {
//     Graph gp(5);
//     gp.addEdge(1,3);
//     gp.addEdge(3,4);
//     gp.addEdge(2,4);
//     gp.addEdge(0,2);
//     if (gp.isCyclic()) printf("CYCLIC\n");
//     else printf("NOT CYCLIC\n");
//     return 0;
// }

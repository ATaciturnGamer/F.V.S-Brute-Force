#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono>
#include "graph.h"

using namespace std::chrono;

void powersetRecUtil(Graph *G, int s[], int k, int n, int current_set[], int &current_ct) {
    if (k == n-1) {
        s[k] = 0;
        if (!G->isCyclic(s))
        {
            int ct = 0;
            for (int i = 0; i<n; i++)
            {
                if (s[i]==1) ct++;
            }
            if (current_ct>ct)
            {
                current_ct = ct;
                for (int i = 0; i<n; i++)
                {
                    current_set[i] = s[i];
                }
            }
        }
        s[k] = 1;
        if (!G->isCyclic(s))
        {
            int ct = 0;
            for (int i = 0; i<n; i++)
            {
                if (s[i]==1) ct++;
            }
            if (current_ct>ct)
            {
                current_ct = ct;
                for (int i = 0; i<n; i++)
                {
                    current_set[i] = s[i];
                }
            }
        }
        return;
    }
    s[k] = 0;
    powersetRecUtil(G,s,k+1,n,current_set,current_ct);
    s[k] = 1;
    powersetRecUtil(G,s,k+1,n,current_set,current_ct);
}

int main()
{
    int size;
    std::string str;
    std::vector<std::string> V;
    std::ifstream fp;
    fp.open("test.txt");
    size = 0;
    while (fp >> str) {
        if (std::find(V.begin(), V.end(), str) == V.end())
        {
            V.push_back(str);
            size++;
        }
    }
    fp.close();
    std::cout << "Vertex Size: " << size << std::endl;
    Graph G(size);
    int j = 0;
    for (std::vector<std::string>::iterator i = V.begin(); i != V.end(); i++)
    {
        G.addNode(*i,j);
        j++;
    }
    std::string p,q;
    fp.open("test.txt");
    while (fp >> p)
    {
        if (!(fp >> q)) return 1;
        G.addEdge(p,q);
    }
    fp.close();
    int exc[size]={0};
    int c=size;
    int res[size]={1};
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    powersetRecUtil(&G,exc,0,size,res,c);

    std::vector<int> fvs;
    for (int i = 0; i < size; i++)
    {
        if (res[i]==1) fvs.push_back(i);
    }
    std::cout << "Minimum Feedback Vertex Set: ";
    for (std::vector<int>::iterator i = fvs.begin(); i != fvs.end(); i++)
    {
        std::cout << *i <<"\t";
    }
    std::cout << std::endl;


    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    std::cout <<"Finished in: "<< duration_cast<seconds>( t2 - t1 ).count() <<"."<<duration_cast<microseconds>( t2 - t1 ).count() << " seconds\n";

    return 0;
}

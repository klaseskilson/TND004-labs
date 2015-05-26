/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    vector<Edge> edges;
    bool done[size+1];
    for (int v = 1; v <= size; ++v)
        done[v] = false;

    // c = start
    int c = 1;
    done[c] = true;
    Node *e = array[c].getFirst();

    // while true
    while (true)
    {
        Edge smallest = Edge(0, 0, INFINITY);
        Node *res = nullptr;
        for (int i = 1; i <= size; ++i)
        {
            if (!done[i]) continue;

            e = array[i].getFirst();
            while (e)
            {
                Edge w = Edge(i, e->vertex, e->weight);
                if (!done[e->vertex] && w < smallest)
                {
                    smallest = w;
                    c = w.tail;
                    res = e;
                }
                e = e->next;
            }
        }

        // exit while (true) if we have found next child
        if (!res)
            break;

        edges.push_back(smallest);

        // done v = true
        done[c] = true;
    }

    // print every edge
    for (Edge e : edges)
    {
        if (e.head > 0)
            cout << e << endl;
    }
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

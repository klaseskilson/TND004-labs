/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    Queue<int> Q;

    for (int v = 1; v <= size; ++v)
    {
        dist[v] = INFINITY;
        path[v] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s);

    while (!Q.isEmpty())
    {
        int current = Q.getFront();
        Node *u = array[current].getFirst();
        Q.dequeue();

        while (u)
        {
            if (dist[u->vertex] == INFINITY)
            {
                dist[u->vertex] = dist[current] + 1;
                path[u->vertex] = current;
                Q.enqueue(u->vertex);
            }
            u = u->next;
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    // chooses the wrong path for vertex 3 when s = 5?
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    for (int v = 1; v <= size; ++v)
    {
        dist[v] = INFINITY;
        path[v] = 0;
        done[v] = false;
    }

    dist[s] = 0;
    done[s] = true;


    while (true)
    {
        Node *u = array[s].getFirst();
        while (u)
        {
            if (!done[u->vertex] && dist[u->vertex] > dist[s] + u->weight)
            {
                dist[u->vertex] = dist[s] + u->weight;
                path[u->vertex] = s;
            }
            u = u->next;
        }

        int smallest = INFINITY;
        for (int i = 1; i <= size; ++i)
        {
            if (!done[i])
                continue;

            Node *v = array[i].getFirst();
            while (v)
            {
                if (!done[v->vertex] && v->weight < smallest)
                {
                    smallest = v->weight;
                    u = v;
                    s = v->vertex;
                }
                v = v->next;
            }
        }

        if (smallest == INFINITY)
            break;

        done[u->vertex] = true;
    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    string s = " (" + to_string(dist[t]) + ")";

    while (path[t] > 0)
    {
        s = to_string(t) + " " + s;
        t = path[t];
    }
    s = " " + to_string(t) + " " + s;

    cout << s;
}

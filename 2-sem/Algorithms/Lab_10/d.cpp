#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Edge
{
public:
    short b;
    short e;
    int w;
    Edge(short b_, short e_, int w_)
    {
        b = b_;
        e = e_;
        w = w_;
    }
    Edge(const Edge& a)
    {
        b = a.b;
        e = a.e;
        w = a.w;
    }
};

class Vertex
{
public:
    int i;
    vector<Edge> v;
    vector<Edge> in;
    int group;
    Vertex(int i_)
    {
        i = i_;
        group = -2;
    }
};

void reachable(vector<Vertex>& list, int i)
{
    list[i].group = -1;
    for (int j = 0; j < list[i].v.size(); j++)
    {
        int v = list[i].v[j].e;
        if (list[v].group != -1)
            reachable(list, v);
    }
}

void dfs1(vector<Vertex>& graph, int v, vector<int>& ord)
{
    graph[v].group = 0;
    for (int i = 0; i < graph[v].v.size(); i++)
    {
        int j = graph[v].v[i].e;
        if (graph[j].group != 0)
        {
            dfs1(graph, j, ord);
        }
    }
    ord.push_back(v);
}
 
void dfs2(vector<Vertex>& graph, int v, int g)
{
    graph[v].group = g;
    for (int i = 0; i < graph[v].in.size(); i++)
    {
        int j = graph[v].in[i].e;
        if (graph[j].group == 0)
        {
            dfs2(graph, j, g);
        }
    }
}

vector<int> Condensation(vector<Vertex>& graph)
{
    int n = graph.size();
    vector<int> ord;
    for (int i = 0; i < n; i++)
    {
        if (graph[i].group != 0)
        {
            dfs1(graph, i, ord);
        }
    }
    int g = 1;
    for (int i = 0; i < n; i++)
    {
        int j = ord[n - 1 - i];
        if (graph[j].group == 0)
        {
            dfs2(graph, j, g);
            g++;
        }
    }
    vector<int> answ;
    for (int i = 0; i < n; i++)
    {
        answ.push_back(graph[i].group);
    }
    return answ;
}

long long findMST(vector<Vertex>& list, int vert)
{
    int n = list.size();
    long long res = 0;
    vector<int> minEdge;
    for (int i = 0; i < n; i++)
    {
        minEdge.push_back(INT32_MAX);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < list[i].in.size(); j++)
        {
            int v = list[i].in[j].w;
            if (minEdge[i] > v)
            {
                minEdge[i] = v;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i != vert)
            res += minEdge[i];
    }

    vector<Vertex> zeroEdges;
    for (int i = 0; i < n; i++)
    {
        zeroEdges.push_back(Vertex(i));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < list[i].in.size(); j++)
        {
            int v = list[i].in[j].w;
            if (v == minEdge[i])
            {
                zeroEdges[list[i].in[j].e].v.push_back(Edge(list[i].in[j].e, list[i].in[j].b, v - minEdge[i]));
                zeroEdges[list[i].in[j].b].in.push_back(Edge(list[i].in[j].b, list[i].in[j].e, v - minEdge[i]));
            }
        }
    }

    bool everyVReachable = true;
    reachable(zeroEdges, vert);
    for (int i = 0; i < n; i++)
    {
        if (zeroEdges[i].group != -1)
        {
            everyVReachable = false;
            break;
        }
    }
    if (everyVReachable)
        return res;
    vector<int> newComponents = Condensation(zeroEdges);
    vector<Vertex> newEdges;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < list[i].v.size(); j++)
        {
            int b = list[i].v[j].b;
            int e = list[i].v[j].e;
            if ((newComponents[b] != newComponents[e]))
            {
                Edge edge = Edge(newComponents[b] - 1, newComponents[e] - 1, list[i].v[j].w - minEdge[list[i].v[j].e]);
                int maxcomp = edge.b > edge.e ? edge.b : edge.e;
                for (int k = newEdges.size(); k <= maxcomp; k++)
                {
                    newEdges.push_back(Vertex(k));
                }
                newEdges[edge.b].v.push_back(edge);
                newEdges[edge.e].in.push_back(Edge(edge.e, edge.b, edge.w));
            }
        }
    }
    res += findMST(newEdges, newComponents[vert] - 1);
    return res;
}

int main()
{
    ifstream input("chinese.in");
    int n, m;
    input >> n >> m;
    vector<Vertex> list;
    for (int i = 0; i < n; i++)
    {
        list.push_back(Vertex(i));
    }
    for (int i = 0; i < m; i++)
    {
        int b, e, w;
        input >> b >> e >> w;
        list[b - 1].v.push_back(Edge(b - 1, e - 1, w));
        list[e - 1].in.push_back(Edge(e - 1, b - 1, w));
    }
    input.close();
    bool everyVReachable = true;
    reachable(list, 0);
    for (int i = 0; i < n; i++)
    {
        if (list[i].group != -1)
        {
            everyVReachable = false;
            break;
        }
    }
    ofstream output("chinese.out");
    if (!everyVReachable) output << "NO";
    else
    {
        output << "YES" << endl << findMST(list, 0);
    }
    output.close();
}
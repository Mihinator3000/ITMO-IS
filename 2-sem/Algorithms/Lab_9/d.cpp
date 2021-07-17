#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Dot
{
public:
    vector<int> l;
    vector<int> inv;
    int group;
    Dot()
    {
        group = -1;
    }
};

void dfs1(vector<Dot>& graph, int v, vector<int>& ord)
{
    graph[v].group = 0;
    for (int i = 0; i < graph[v].l.size(); i++)
    {
        int j = graph[v].l[i];
        if (graph[j].group == -1)
        {
            dfs1(graph, j, ord);
        }
    }
    ord.push_back(v);
}

void dfs2(vector<Dot>& graph, int v, int g)
{
    graph[v].group = g;
    for (int i = 0; i < graph[v].inv.size(); i++)
    {
        int j = graph[v].inv[i];
        if (graph[j].group == 0)
        {
            dfs2(graph, j, g);
        }
    }
}

int main()
{
    ifstream input("cond.in");
    int n, m;
    input >> n >> m;
    vector<Dot> graph;
    for (int i = 0; i < n; i++)
    {
        graph.push_back(Dot());
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        input >> u >> v;
        graph[u - 1].l.push_back(v - 1);
        graph[v - 1].inv.push_back(u - 1);
    }
    input.close();
    vector<int> ord;
    for (int i = 0; i < n; i++)
    {
        if (graph[i].group == -1)
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
    ofstream output("cond.out");
    output << g - 1 << endl;
    for (int i = 0; i < n; i++)
    {
        output << graph[i].group << " ";
    }
    output.close();
}
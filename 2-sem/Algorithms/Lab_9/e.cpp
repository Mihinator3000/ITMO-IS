#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Dot
{
public:
    vector<int> l;
    int path;
    Dot()
    {
        path = 0;
    }
};

int dfs(vector<Dot>& graph, int v)
{
    int c = 0;
    for (int i = 0; i < graph[v].l.size(); i++)
    {
        int j = graph[v].l[i];
        if (graph[j].path == 0)
        {
            graph[j].path = dfs(graph, j);
        }
        if (graph[j].path > c) c = graph[j].path;
    }
    return c + 1;
}

int main()
{
    ifstream input("hamiltonian.in");
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
    }
    input.close();
    for (int i = 0; i < n; i++)
    {
        if (graph[i].path == 0)
        {
            graph[i].path = dfs(graph, i);
        }
    }
    bool ham = false;
    for (int i = 0; i < n; i++)
    {
        if (graph[i].path == n)
        {
            ham = true;
            break;
        }
    }
    ofstream output("hamiltonian.out");
    output << (ham ? "YES" : "NO");
    output.close();
}
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Dot 
{
public:
    vector<int> l;
    int num;
    Dot()
    {
        num = -1;
    }
};

bool dfs(vector<Dot>& graph, int v, int n)
{
    graph[v].num = n;
    for (int i = 0; i < graph[v].l.size(); i++)
    {
        int j = graph[v].l[i];
        if (graph[j].num == -1)
        {
            bool check = dfs(graph, j, 1 - n);
            if (!check) return false;
        }
        if (graph[j].num == n)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream input("bipartite.in");
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
        graph[v - 1].l.push_back(u - 1);
    }
    input.close();
    bool check = true;
    for (int i = 0; i < n; i++)
    {
        if (check)
        {
            if (graph[i].num == -1)
                check = dfs(graph, i, 0);
        }
        else break;
    }
    ofstream output("bipartite.out");
    output << (check? "YES" : "NO");
    output.close();
}

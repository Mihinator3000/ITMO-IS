#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Dot 
{
public:
    vector<int> l;
    char color;
    Dot()
    {
        color = 'w';
    }
};

bool cycleCheck(vector<Dot>& graph, int v)
{
    graph[v].color = 'g';
    for (int i = 0; i < graph[v].l.size(); i++)
    {
        int j = graph[v].l[i];
        if (graph[j].color == 'w')
        {
            bool cycle = cycleCheck(graph, j);
            if (cycle) return true;
        }
        if (graph[j].color == 'g')
        {
            return true;
        }
    }
    graph[v].color = 'b';
    return false;
}

void dfs(vector<Dot>& graph, int v, vector<int>& sort)
{
    graph[v].color = 'g';
    for (int i = 0; i < graph[v].l.size(); i++)
    {
        int j = graph[v].l[i];
        if (graph[j].color == 'w')
        {
            dfs(graph, j, sort);
        }
    }
    sort.push_back(v + 1);
}

int main()
{
    ifstream input("topsort.in");
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
    bool cycle = false;
    for (int i = 0; i < n; i++)
    {
        if (graph[i].color == 'w')
        {
            cycle = cycleCheck(graph, i);
            if (cycle) break;
        }
    }
    ofstream output("topsort.out");
    if (!cycle)
    {
        for (int i = 0; i < n; i++)
        {
            graph[i].color = 'w';
        }
        vector<int> sort;
        for (int i = 0; i < n; i++)
        {
            if (graph[i].color == 'w')
            {
                dfs(graph, i, sort);
            }
        }
        for (int i = sort.size(); i > 0; i--)
        {
            output << sort[i - 1] << " ";
        }
    }
    else output << "-1";
    input.close();
    output.close();
}

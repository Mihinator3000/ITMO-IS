#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
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

bool dfs(vector<Dot>& graph, int v, stack<int>& s)
{
    s.push(v + 1);
    graph[v].color = 'g';
    for (int i = 0; i < graph[v].l.size(); i++)
    {
        int j = graph[v].l[i];
        if (graph[j].color == 'w')
        {
            bool cycle = dfs(graph, j, s);
            if (cycle) return true;
        }
        if (graph[j].color == 'g')
        {
            s.push(j + 1);
            return true;
        }
    }
    graph[v].color = 'b';
    s.pop();
    return false;
}

int main()
{
    ifstream input("cycle.in");
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
    stack<int> s;
    bool cycle = false;
    for (int i = 0; i < n; i++)
    {
        if (graph[i].color == 'w')
        {
            cycle = dfs(graph, i, s);
            if (cycle) break;
        }
    }
    ofstream output("cycle.out");
    if (cycle)
    {
        output << "YES" << endl;
        int last = s.top();
        int v = last;
        stack<int> out;
        while (true)
        {
            out.push(v);
            s.pop();
            v = s.top();
            if (v == last) break;
        }
        int k = 0;
        while (true)
        {
            int i = out.top();
            output << i << " ";
            out.pop();
            if (out.empty())
            {
                if (k == 0) output << i;
                break;
            }
            k++;
        }
    }
    else output << "NO";
    output.close();
}

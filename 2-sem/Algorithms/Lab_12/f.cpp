#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Vertex
{
public:
    vector<int> v;
    bool check;
    int w;
    Vertex() 
    { 
        check = false; 
        w = 0;
    };
};

void dfs(int v, vector<vector<int>>& d, vector<Vertex>& a)
{
    if (!a[v].check)
    {
        a[v].check = true;
        d[v][0] = 0;
        d[v][1] = a[v].w;
        for (int i = 0; i < a[v].v.size(); i++)
        {
            int u = a[v].v[i];
            dfs(u, d, a);
        }
        for (int i = 0; i < a[v].v.size(); i++)
        {
            int u = a[v].v[i];
            d[v][1] += d[u][0];
            d[v][0] += max(d[u][0], d[u][1]);
        }
    }
}

int main()
{
    ifstream input("selectw.in");
    int n;
    input >> n;
    vector<Vertex> a(n, Vertex());
    int top = 0;
    for (int i = 0; i < n; i++)
    {
        int p, q;
        input >> p >> q;
        if (p != 0)
        {
            a[p - 1].v.push_back(i);
        }
        else top = i;
        a[i].w = q;
    }
    vector<vector<int>> d(n, vector<int>(2, -1));
    dfs(top, d, a);
    ofstream output("selectw.out");
    output << max(d[top][0], d[top][1]);
    input.close();
    output.close();
}
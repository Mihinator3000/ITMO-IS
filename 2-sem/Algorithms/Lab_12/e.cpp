#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Vertex
{
public:
    vector<int> v;
    bool check;
    Vertex() 
    { 
        check = false; 
    };
};

void dfs(int v, vector<vector<int>>& d, vector<Vertex>& a)
{
    if (!a[v].check)
    {
        a[v].check = true;
        d[v][0] = 0;
        d[v][1] = 1;
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
    int n;
    cin >> n;
    vector<Vertex> a(n, Vertex());
    int top = 0;
    for (int i = 0; i < n; i++)
    {
        int in;
        cin >> in;
        if (in != 0)
        {
            a[in - 1].v.push_back(i);
        }
        else top = i;
    }
    vector<vector<int>> d(n, vector<int>(2, -1));
    dfs(top, d, a);
    cout << max(d[top][0], d[top][1]);
}
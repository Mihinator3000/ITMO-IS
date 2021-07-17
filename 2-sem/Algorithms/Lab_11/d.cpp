#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


constexpr auto MAXLEN = 5000000000000000000;

class Edge
{
public:
    int a;
    int b;
    long long weight;
    Edge()
    {
        a = 0;
        b = 0;
        weight = 0;
    }
    Edge(int a_, int b_, long long w)
    {
        a = a_;
        b = b_;
        weight = w;
    }
};

class Vertex
{
public:
    bool check;
    vector<int> b;
    Vertex()
    {
        check = false;
    }
};

void DFS(int s, vector<long long>& d, vector<Vertex>& v)
{
    v[s].check = true;
    d[s] = -MAXLEN;
    for (int i = 0; i < v[s].b.size(); i++)
    {
        int w = v[s].b[i];
        if (!v[w].check)
        {
            DFS(w, d, v);
        }
    }
}

void solve(int s, int n, int m, vector<Edge>& e)
{
    vector<long long> d(n, MAXLEN);
    d[s] = 0;
    vector<int> p(n, -1);
    int x = -1;
    for (int i = 0; i < n; i++)
    {
        x = -1;
        for (int j = 0; j < m; j++)
        {
            if (d[e[j].a] < MAXLEN)
            {
                if (d[e[j].b] > d[e[j].a] + e[j].weight)
                {
                    d[e[j].b] = (-MAXLEN > d[e[j].a] + e[j].weight) ? (-MAXLEN) : (d[e[j].a] + e[j].weight);
                    p[e[j].b] = e[j].a;
                    x = e[j].b;
                }
            }
        }
    }
    if (x != -1)
    {
        vector<int> negativeCycle;
        for (int i = 0; i < m; i++)
        {
            if (d[e[i].a] < MAXLEN)
            {
                if (d[e[i].b] > d[e[i].a] + e[i].weight)
                {
                    negativeCycle.push_back(e[i].b);
                }
            }
        }
        vector<Vertex> v(n, Vertex());
        for (int i = 0; i < m; i++)
        {
            v[e[i].a].b.push_back(e[i].b);
        }
        for (int i = 0; i < negativeCycle.size(); i++)
        {
            int k = negativeCycle[i];
            for (int j = 0; j < n; j++)
            {
                if (k >= 0 && k < n)
                {
                    k = p[k];
                }
            }
            DFS(k, d, v);
        }
    }
    ofstream output("path.out");
    for (int i = 0; i < n; i++)
    {
        switch (d[i])
        {
            case MAXLEN:
                output << "*\n";
                break;
            case -MAXLEN:
                output << "-\n";
                break;
            default:
                output << d[i] << endl;
        }
    }
    output.close();
}

int main()
{
    ifstream input("path.in");
    int n, m, s;
    input >> n >> m >> s;
    vector<Edge> e;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        long long w;
        input >> a >> b >> w;
        e.push_back(Edge(a - 1, b - 1, w));
        
    }
    input.close();
    solve(s - 1, n, m, e);
}
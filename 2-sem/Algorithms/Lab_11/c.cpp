#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


constexpr auto MAXLEN = 2000000000;

class Edge
{
public:
    int a;
    int b;
    int weight;
    Edge()
    {
        a = 0;
        b = 0;
        weight = 0;
    }
    Edge(int a_, int b_, int w)
    {
        a = a_;
        b = b_;
        weight = w;
    }
};


void solve(int v, int n, int m, vector<Edge>& e)
{
    vector<int> d(n, MAXLEN);
    d[v] = 0;
    while (true)
    {
        bool any = false;
        for (int i = 0; i < m; i++)
        {
            if (d[e[i].a] < MAXLEN)
            {
                if (d[e[i].b] > d[e[i].a] + e[i].weight)
                {
                    d[e[i].b] = d[e[i].a] + e[i].weight;
                    any = true;
                }
            }
        }
        if (!any) 
            break;
    }
    ofstream output("pathbgep.out");
    for (int i = 0; i < n; i++)
    {
        output << d[i] << " ";
    }
    output.close();
}

int main()
{
    ifstream input("pathbgep.in");
    int n, m;
    input >> n >> m;
    vector<Edge> e;
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        input >> a >> b >> w;
        e.push_back(Edge(a - 1, b - 1, w));
        e.push_back(Edge(b - 1, a - 1, w));
    }
    solve(0, n, m * 2, e);
    input.close();
}
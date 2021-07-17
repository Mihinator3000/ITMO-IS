#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


constexpr auto BILLION = 1000000000;

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


bool solve(int v, vector<int>& negativeCycle, int n, int m, vector<Edge>& e)
{
    vector<int> d(n, BILLION);
    d[v] = 0;
    vector<int> p(n, -1);
    int x = -1;
    for (int i = 0; i < n; i++)
    {
        x = -1;
        for (int j = 0; j < m; j++)
        {
            if (d[e[j].b] > d[e[j].a] + e[j].weight) 
            {
                d[e[j].b] = (-BILLION > d[e[j].a] + e[j].weight) ? (-BILLION) : (d[e[j].a] + e[j].weight);
                p[e[j].b] = e[j].a;
                x = e[j].b;
            }
        }
    }
    if (x == -1) 
        return false;
    for (int i = 0; i < n; i++)
    {
        x = p[x];
    }
    int i = x;
    while (true)
    {
        negativeCycle.push_back(i + 1);
        if (i == x && negativeCycle.size() > 1)
            break;
        i = p[i];
    }
    reverse(negativeCycle.begin(), negativeCycle.end());
    return true;
}

int main()
{
    ifstream input("negcycle.in");
    int n;
    input >> n;
    vector<Edge> e;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int w;
            input >> w;
            if (w != BILLION)
            {
                e.push_back(Edge(i, j, w));
            }
        }
    }
    input.close();
    vector<int> negativeCycle;
    ofstream output("negcycle.out");
    if (solve(0, negativeCycle, n, e.size(), e))
    {
        output << "YES\n" << negativeCycle.size() << endl;
        for (int i = 0; i < negativeCycle.size(); i++)
        {
            output << negativeCycle[i] << " ";
        }
    }
    else output << "NO";
    output.close();
}
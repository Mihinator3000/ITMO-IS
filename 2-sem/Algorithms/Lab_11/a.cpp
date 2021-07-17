#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


constexpr auto MAXLEN = 200000000000;

class Edge
{
public:
    int destination;
    long long weight;
    Edge()
    {
        destination = 0;
        weight = 0;
    }
    Edge(int d, long long w)
    {
        destination = d;
        weight = w;
    }
};

int main()
{
    ifstream input("pathmgep.in");
    int n, s, f;
    input >> n >> s >> f;
    vector<vector<Edge>> g(n, vector<Edge>());
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            long long w;
            input >> w;
            if (w != -1 && w != 0)
                g[i].push_back(Edge(j, w));
        }
    }
    input.close();
    vector<long long> d(n, MAXLEN);
    vector<bool> used(n, false);
    d[s - 1] = 0;
    for (int i = 0; i < n; i++)
    {
        int v = -1;
        for (int j = 0; j < n; j++)
        {
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }
        if (d[v] == MAXLEN)
            break;
        used[v] = true;
        for (unsigned int j = 0; j < g[v].size(); j++)
        {
            if (d[v] + g[v][j].weight < d[g[v][j].destination])
            {
                d[g[v][j].destination] = d[v] + g[v][j].weight;
            }
        }
    }
    ofstream output("pathmgep.out");
    if (d[f - 1] == MAXLEN)
        output << "-1";
    else
        output << d[f - 1];
    output.close();
}
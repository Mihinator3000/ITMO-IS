#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Dot
{
public:
    vector<int> l;
};

bool game(vector<Dot>& graph, int v, bool player)
{
    if (graph[v].l.size() == 0) return !player;
    for (int i = graph[v].l.size() - 1; i >= 0; i--)
    {   
        int j = graph[v].l[i];
        if (game(graph, j, !player) == player)
        {
            return player;
        }
    }
    return !player;
}

int main()
{
    ifstream input("game.in");
    int n, s, m;
    input >> n >> s >> m;
    vector<Dot> graph;
    for (int i = 0; i < n; i++)
    {
        graph.push_back(Dot());
    }
    for (int i = 0; i < s; i++)
    {
        int u, v;
        input >> u >> v;
        graph[u - 1].l.push_back(v - 1);
    }
    input.close();
    ofstream output("game.out");
    output << (game(graph, m - 1, true) ? "First" : "Second") << " player wins";
    output.close();
}
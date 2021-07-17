#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Edge
{
public:
    int b;
    int e;
    int w;
    bool check;
    Edge(int b_, int e_, int w_)
    {
        b = b_;
        e = e_;
        w = w_;
        check = false;
    }
};

class DSU
{
public:
    vector<int> parent;
    vector<int> rank;
    DSU(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    int find(int v)
    {
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    bool unite(int v, int u)
    {
        int a = find(v);
        int b = find(u);
        if (a == b) return false;
        if (rank[a] < rank[b]) parent[a] = b;
        else if (rank[b] < rank[a]) parent[b] = a;
        else
        {
            parent[a] = b;
            rank[b]++;
        }
        return true;
    }
};

bool compare(const Edge& a, const Edge& b)
{
    return a.w < b.w;
}

int main()
{
    ifstream input("spantree3.in");
    int n, m;
    input >> n >> m;
    vector<Edge> list;
    DSU d = DSU(n);
    for (int i = 0; i < m; i++)
    {
        int b, e, w;
        input >> b >> e >> w;
        list.push_back(Edge(b - 1, e - 1, w));
    }
    sort(list.begin(), list.end(), compare);
    input.close();
    long long len = 0;
    int count = 1;
    while (count != n)
    {
        for (int i = 0; i < m; i++)
        {
            if (list[i].check) continue;
            int a = list[i].b;
            int b = list[i].e;
            if (d.unite(a, b))
            {
                len += list[i].w;
                list[i].check = true;
                break;
            }
            else list[i].check = true;
        }
        count++;
    }
    ofstream output("spantree3.out");
    output << len;
    output.close();
}
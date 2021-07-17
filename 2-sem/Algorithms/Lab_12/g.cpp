#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input("knapsack.in");
    int s, n;
    input >> s >> n;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
    {
        input >> a[i];
    }
    vector<int> m(11000, 0);
    m[0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = s; j >= a[i]; j--)
        {
            if (m[j - a[i]] == 1)
                m[j] = 1;
        }
    }
    int i = s;
    while (true)
    {
        if (m[i] > 0)
            break;
        i--;
    }
    ofstream output("knapsack.out");
    output << i;
    input.close();
    output.close();
}
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

constexpr auto BILLION = 1000000000;

void func(vector<int>& a, vector<vector<long long>>& d, int i, int j)
{
    if (i < j)
    {
        if (d[i][j] == 0)
        {
            if (a[i] == a[j])
            {
                func(a, d, i, j - 1);
                func(a, d, i + 1, j);
                d[i][j] = (d[i][j - 1] + d[i + 1][j] + 1) % BILLION;
            }
            else
            {
                func(a, d, i, j - 1);
                func(a, d, i + 1, j);
                func(a, d, i + 1, j - 1);
                d[i][j] = (d[i][j - 1] + d[i + 1][j] - d[i + 1][j - 1] + BILLION) % BILLION;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<vector<long long>> d(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
    {
        d[i][i] = 1;
    }
    func(a, d, 0, n - 1);
    cout << d[0][n - 1];
}
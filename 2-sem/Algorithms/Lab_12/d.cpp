#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void func(vector<vector<int>>& arr, int n, int m, int i, int j)
{
    if (j + 2 < m)
    {
        if (i - 1 >= 0)
        {
            arr[i - 1][j + 2]++;
            func(arr, n, m, i - 1, j + 2);
        }
        if (i + 1 < n)
        {
            arr[i + 1][j + 2]++;
            func(arr, n, m, i + 1, j + 2);
        }
    }
    if (i + 2 < n)
    {
        if (j - 1 >= 0)
        {
            arr[i + 2][j - 1]++;
            func(arr, n, m, i + 2, j - 1);
        }
        if (j + 1 < m)
        {
            arr[i + 2][j + 1]++;
            func(arr, n, m, i + 2, j + 1);
        }
    }
}

int main()
{
    ifstream input("knight2.in");
    int n, m;
    input >> n >> m;
    input.close();
    vector<vector<int>> arr(n, vector<int>(m, 0));
    func(arr, n, m, 0, 0);
    ofstream output("knight2.out");
    output << arr[n - 1][m - 1];
    output.close();
}
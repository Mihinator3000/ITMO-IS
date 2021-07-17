#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<int> d(n, 1);
    vector<int> p(n, -1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
            {
                if (d[j] + 1 > d[i])
                {
                    d[i] = d[j] + 1;
                    p[i] = j;
                }
            }
        }
    }
    int k = d[0];
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if (d[i] > k)
        {
            k = d[i];
            pos = i;
        }
    }
    cout << k << endl;
    vector<int> path;
    while (pos != -1)
    {
        path.push_back(a[pos]);
        pos = p[pos];
    }
    for (int i = path.size(); i > 0; i--)
    {
        cout << path[i - 1] << " ";
    }
}
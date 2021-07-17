#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define TWOBILLION 2000000000

int main()
{
    int n;
    cin >> n;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<int> d(n + 1, TWOBILLION);
    vector<int> pos(n + 1, 0);
    d[0] = -TWOBILLION;
    pos[0] = -1;
    vector<int> p(n, -1);
    int len = 0;
    for (int i = 0; i < n; i++) 
    {
        int j = int(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        if (d[j - 1] < a[i] && a[i] < d[j])
        {
            d[j] = a[i];
            pos[j] = i;
            p[i] = pos[j - 1];
            len = max(len, j);
        }
    }
    int position = pos[len];
    vector<int> path;
    while (position != -1)
    {
        path.push_back(a[position]);
        position = p[position];
    }
    cout << path.size() << endl;
    for (int i = path.size(); i > 0; i--)
    {
        cout << path[i - 1] << " ";
    }
}
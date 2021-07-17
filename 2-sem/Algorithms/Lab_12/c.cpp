#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void LCS(int n, int m, string a, string b, vector<int>& l)
{
    vector<vector<int>> k((m + 1), vector<int>(2, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= m; j++)
            k[j][0] = k[j][1];
        for (int j = 1; j <= m; j++)
        {
            if (a[i] == b[j - 1])
                k[j][1] = k[j - 1][0] + 1;
            else
                k[j][1] = max(k[j][0], k[j - 1][1]);
        }
    }
    for (int i = 0; i <= m; i++)
        l[i] = k[i][1];
        
}

void Hirshberg(int n, int m, string a, string b)
{
    if (m <= 0)
        return;
    if (n == 1)
    {
        int i = b.find_first_of(a[0]);
        if (i != string::npos)
            cout << a[0];
        return;
    }
    int mid = n / 2;
    vector<int> f(m + 1);
    LCS(mid, m, a.substr(0, mid), b, f);
    string a_reversed = a, b_reversed = b;
    reverse(a_reversed.begin(), a_reversed.end());
    reverse(b_reversed.begin(), b_reversed.end());
    vector<int> s(m + 1);
    LCS(mid + 1, m, a_reversed.substr(0, n - mid), b_reversed, s);
    int max = s[0];
    int it_max = 0;
    for (int i = 0; i <= m; i++)
    {
        if (f[i] + s[m - i] > max)
        {
            max = f[i] + s[m - i];
            it_max = i;
        }
    }
    if (mid == 0)
        mid++;
    if (f[m] > max)
        it_max = m;
    Hirshberg(mid, it_max, a.substr(0, mid), b.substr(0, it_max));
    Hirshberg(n - mid, m - it_max, a.substr(mid, n), b.substr(it_max, m));
}

int main()
{
    string a, b;
    cin >> a >> b;
    int n = a.length(), m = b.length();
    if (n < m)
        Hirshberg(n, m, a, b);
    else
        Hirshberg(m, n, b, a);
    cout << endl;
    return 0;
}
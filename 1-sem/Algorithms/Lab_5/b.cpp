#include <iostream>
#include <fstream>
using namespace std;

bool Check(int arr_k[], int arr_l[], int arr_r[], int n, int l, int r)
{
    bool b = false;
    if ((l <arr_k[n - 1]) && (arr_k[n - 1] < r))
    {
        int left = arr_l[n - 1];
        int right = arr_r[n - 1];
        if ((left != 0) && (right != 0))
        {
            if (arr_k[n - 1] < r)
            {
                b = Check(arr_k, arr_l, arr_r, left, l, arr_k[n - 1]);
            }
            else b = Check(arr_k, arr_l, arr_r, left, l, r);
            if (b)
            {
                if (arr_k[n - 1] > l)
                {
                    b = Check(arr_k, arr_l, arr_r, right, arr_k[n - 1], r);
                }
                else return Check(arr_k, arr_l, arr_r, right, l, r);
            }
        }
        if ((left != 0) && (right == 0))
        {
            if (arr_k[n - 1] < r)
            {
                b = Check(arr_k, arr_l, arr_r, left, l, arr_k[n - 1]);
            }
            else b = Check(arr_k, arr_l, arr_r, left, l, r);
        }
        if ((right != 0) && (left == 0))
        {
            if (arr_k[n - 1] > l)
            {
                b = Check(arr_k, arr_l, arr_r, right, arr_k[n - 1], r);
            }
            else b = Check(arr_k, arr_l, arr_r, right, l, r);
        }
        if ((right == 0) && (left == 0)) b = true;
        return b;
    }
    else return b;
}

int main()
{
    ifstream input("check.in");
    int n;
    input >> n;
    bool check = 1;
    if (n != 0)
    {
        int arr_k[n];
        int arr_l[n];
        int arr_r[n];
        for(int i = 0; i < n; i++)
        {
            input >> arr_k[i] >> arr_l[i] >> arr_r[i];
        }
        check = Check(arr_k, arr_l, arr_r, 1, -1000000001, 1000000001);
    }
    ofstream output("check.out");
    if(check)output<<"YES";
    else output<<"NO";
    input.close();
    output.close();
    return 0;
}

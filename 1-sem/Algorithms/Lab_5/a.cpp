#include <iostream>
#include <fstream>
using namespace std;

int Height(int arr_l[], int arr_r[], int n)
{
    int height = 1;
    int left = arr_l[n - 1];
    int right = arr_r[n - 1];
    if ((left == 0) || (right == 0))
    {
        if ((left == 0) && (right == 0)) return height;
        if (left == 0)
        {
            height += Height(arr_l, arr_r, right);
        }
        if (right == 0)
        {
            height += Height(arr_l, arr_r, left);
        }
    }
    else
    {
        int h_l = Height(arr_l, arr_r, left);
        int h_r = Height(arr_l, arr_r, right);
        if (h_l > h_r) height += h_l;
        else height += h_r;
    }
    return height;
}

int main()
{
    ifstream input("height.in");
    int n;
    input >> n;
    int height = 0;
    if (n != 0)
    {
        int arr_k[n];
        int arr_l[n];
        int arr_r[n];
        for(int i = 0; i < n; i++)
        {
            input >> arr_k[i] >> arr_l[i] >> arr_r[i];
        }
        height = Height(arr_l, arr_r, 1);
    }
    ofstream output("height.out");
    output << height;
    input.close();
    output.close();
    return 0;
}

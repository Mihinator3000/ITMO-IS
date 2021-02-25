#include <iostream>
#include <fstream>
using namespace std;

int Height(int*& arr, int arr_l[], int arr_r[], int n)
{
    int height = 1;
    int left = arr_l[n - 1];
    int right = arr_r[n - 1];
    int h_l;
    int h_r;
    if ((left == 0) || (right == 0))
    {
        if ((left == 0) && (right == 0))
        {
            arr[n - 1] = 0;
            return height;
        }
        if (left == 0)
        {
            h_r = Height(arr, arr_l, arr_r, right);
            arr[n - 1] = h_r;
            height += h_r;
        }
        if (right == 0)
        {
            h_l = Height(arr, arr_l, arr_r, left);
            arr[n - 1] = - h_l;
            height += h_l;
        }
    }
    else
    {
        h_l = Height(arr, arr_l, arr_r, left);
        h_r = Height(arr, arr_l, arr_r, right);
        arr[n - 1] = h_r - h_l;
        if (h_l > h_r) height += h_l;
        else height += h_r;
    }
    return height;
}

int main()
{
    ifstream input("balance.in");
    int n;
    input >> n;
    int dop;
    int a[n];
    int* arr = a;
    int arr_l[n];
    int arr_r[n];
    for (int i = 0; i < n; i++)
    {
        input >> dop >> arr_l[i] >> arr_r[i];
        arr[i] = 0;
    }
    Height(arr, arr_l, arr_r, 1);
    ofstream output("balance.out");
    for (int i = 0; i < n; i++)
    {
        output << a[i] << endl;
    }
    input.close();
    output.close();
    return 0;
}

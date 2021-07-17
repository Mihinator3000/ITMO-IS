using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Heapify(int[] arr, int n, int i)
        {
            int biggest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if ((left < n) && (arr[left] > arr[biggest]))
            {
                biggest = left;
            }
            if ((right < n) && (arr[right] > arr[biggest]))
            {
                biggest = right;
            }
            if (biggest != i)
            {
                int t = arr[i];
                arr[i] = arr[biggest];
                arr[biggest] = t;
                Heapify(arr, n, biggest);
            }
        }
        static void HeapSort(int[] arr, int n)
        {
            for (int i = n / 2 - 1; i >= 0; i--)
                Heapify(arr, n, i);
            for (int i = n - 1; i >= 0; i--)
            {
                int t = arr[0];
                arr[0] = arr[i];
                arr[i] = t;
                Heapify(arr, i, 0);
            }
        }
        static void Main()
        {
            StreamReader input = new StreamReader("sort.in");
            int n = Convert.ToInt32(input.ReadLine());
            string[] str = input.ReadLine().Split(' ');
            int[] a = new int[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = Convert.ToInt32(str[i]);
            }
            HeapSort(a, n);
            StreamWriter output = new StreamWriter("sort.out");
            input.Close();
            for (int i = 0; i < n; i++)
            {
                output.Write(a[i] + " ");
            }
            output.Close();
        }
    }
}
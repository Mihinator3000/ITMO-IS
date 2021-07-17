using System;

namespace _1A
{
    class MainClass
    {
        public static void QuickSort(int[] arr, int beginning, int end, int k)
        {
            if ((k >= beginning) && (k <= end))
            {
                int m = beginning + (end - beginning) / 2;
                int mid = arr[m];
                int i = beginning;
                int j = end;
                while (i <= j)
                {
                    while ((arr[i] < mid) && (i <= end)) i++;
                    while ((arr[j] > mid) && (j >= beginning)) j--;
                    if (i <= j)
                    {
                        int t = arr[j];
                        arr[j] = arr[i];
                        arr[i] = t;
                        i++;
                        j--;
                    }
                }
                if (j > beginning) QuickSort(arr, beginning, j, k);
                if (i < end) QuickSort(arr, i, end, k);
            }
        }
        static void Main()
        {
            string[] str1 = Console.ReadLine().Split(' ');
            string[] str2 = Console.ReadLine().Split(' ');
            int n = Convert.ToInt32(str1[0]);
            int k = Convert.ToInt32(str1[1]);

            int A = Convert.ToInt32(str2[0]);
            int B = Convert.ToInt32(str2[1]);
            int C = Convert.ToInt32(str2[2]);
            int[] a = new int[n+1];
            a[1] = Convert.ToInt32(str2[3]);
            a[2] = Convert.ToInt32(str2[4]);
            for (int i = 3; i < n + 1; i++)
            {
                a[i] = A * a[i - 2] + B * a[i - 1] + C;
            }



            QuickSort(a, 1, n, k);
            Console.Write(a[k]);
        }
    }
}
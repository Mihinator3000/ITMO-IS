using System;

namespace _1A
{
    class MainClass
    {

        static int Compare(string a, string b, int k)
        {
            int len = a.Length;
            int output = 0;
            for (int i = len - 1; i >= len - k; i--)
            {
                int a1 = Convert.ToInt32(a[i]);
                int b1 = Convert.ToInt32(b[i]);
                if (a1 > b1)
                {
                    output = 1;
                }
                if (a1 < b1)
                {
                    output = -1;
                }
            }
            return output;

        }

        static void Merge(string[] arr, int first, int middle, int last, int k)
        {
            int left = first;
            int right = middle + 1;
            string[] temp = new string[last - first + 1];
            int index = 0;

            while ((left <= middle) && (right <= last))
            {
                int compare = Compare(arr[left], arr[right], k);
                if ((compare == -1) || (compare == 0))
                {
                    temp[index] = arr[left];
                    left++;
                }
                else
                {
                    temp[index] = arr[right];
                    right++;
                }
                index++;
            }

            for (int i = left; i <= middle; i++)
            {
                temp[index] = arr[i];
                index++;
            }

            for (int i = right; i <= last; i++)
            {
                temp[index] = arr[i];
                index++;
            }

            for (int i = 0; i <= last - first; i++)
            {
                arr[first + i] = temp[i];
            }
        }


        static string[] MergeSort(string[] arr, int first, int last, int k)
        {
            if (first < last)
            {
                int middle = (first + last) / 2;
                MergeSort(arr, first, middle, k);
                MergeSort(arr, middle + 1, last, k);
                Merge(arr, first, middle, last, k);
            }

            return arr;
        }

        static void Main()
        {
            string[] line = Console.ReadLine().Split(' ');
            int n = Convert.ToInt32(line[0]);
            int k = Convert.ToInt32(line[2]);
            string[] arr = new string[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = Console.ReadLine();
            }
            MergeSort(arr, 0, n - 1, k);
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine(arr[i]);
            }
        }
    }
}
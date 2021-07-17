using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Merge(int[] arr, int first, int middle, int last)
        {
            int left = first;
            int right = middle + 1;
            int []temp = new int[last - first + 1];
            int index = 0;

            while ((left <= middle) && (right <= last))
            {
                if (arr[left] < arr[right])
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


        static int[] MergeSort(int[] arr, int first, int last)
        {
            if (first < last)
            {
                int middle = (first + last) / 2;
                MergeSort(arr, first, middle);
                MergeSort(arr, middle + 1, last);
                Merge(arr, first, middle, last);
            }

            return arr;
        }

        static void Main()
        {
            int n = Convert.ToInt32(Console.ReadLine());
            string[] inp = Console.ReadLine().Split(' ');
            int[] arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = Convert.ToInt32(inp[i]);
            }
            string outp = string.Join(" ", MergeSort(arr, 0, n - 1));
            Console.WriteLine(outp);
        }
    }
}
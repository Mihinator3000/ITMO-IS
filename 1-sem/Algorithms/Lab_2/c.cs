using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static double Merge(int[] arr, int first, int middle, int last)
        {
            double count = 0;
            int left = first;
            int right = middle + 1;
            int[] temp = new int[last - first + 1];
            int index = 0;
            int counter = 0;
            while ((left <= middle) && (right <= last))
            {
                if (arr[left] <= arr[right])
                {
                    temp[index] = arr[left];
                    left++;
                    counter++;
                }
                else
                {
                    temp[index] = arr[right];
                    right++;
                    count += Convert.ToDouble(middle - first + 1 - counter);
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
            return count;
        }


        static double MergeSort(int[] arr, int first, int last)
        {
            double count = 0;
            if (first < last)
            {
                int middle = (first + last) / 2;
                count += MergeSort(arr, first, middle);
                count += MergeSort(arr, middle + 1, last);
                count += Merge(arr, first, middle, last);
            }

            return count;
        }
        static void Main()
        {
            StreamReader input = new StreamReader("inversions.in");
            int n = Convert.ToInt32(input.ReadLine());
            string[] str = input.ReadLine().Split(' ');
            int[] arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = Convert.ToInt32(str[i]);
            }

            double count = MergeSort(arr, 0, n - 1);
            StreamWriter output = new StreamWriter("inversions.out");
            input.Close();
            output.Write(count);
            output.Close();
        }
    }
}
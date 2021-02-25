using System;
using System.IO;

namespace _1A
{
    class MainClass
    {

        static int Compare(string a, string b)
        {
            int len;
            if (a.Length > b.Length) len = b.Length;
            else len = a.Length;
            for (int i = 0; i < len; i++)
            {
                int a1 = Convert.ToInt32(a[i]);
                int b1 = Convert.ToInt32(b[i]);
                if (a1 > b1)
                {
                    return 1;
                }
                if (a1 < b1)
                {
                    return -1;
                }
            }
            if (a.Length > b.Length) return 1;
            if (b.Length > a.Length) return -1;
            return 0;
            
        }
        
        static void Merge(string[ , ] arr, int first, int middle, int last)
        {
            int left = first;
            int right = middle + 1;
            string[, ] temp = new string[last - first + 1, 2];
            int index = 0;

            while ((left <= middle) && (right <= last))
            {
                int compare = Compare(arr[left, 0], arr[right, 0]);
                
                if ((compare == -1) || (compare == 0))
                {
                    temp[index, 0] = arr[left, 0];
                    temp[index, 1] = arr[left, 1];
                    left++;
                }
                else
                {
                    temp[index, 0] = arr[right, 0];
                    temp[index, 1] = arr[right, 1];
                    right++;
                }
                index++;
            }
 
            for (int i = left; i <= middle; i++)
            {
                temp[index, 0] = arr[i, 0];
                temp[index, 1] = arr[i, 1];
                index++;
            }
 
            for (int i = right; i <= last; i++)
            {
                temp[index, 0] = arr[i, 0];
                temp[index, 1] = arr[i, 1];
                index++;
            }
 
            for (int i = 0; i <= last - first; i++)
            {
                arr[first + i, 0] = temp[i, 0];
                arr[first + i, 1] = temp[i, 1];
            }
        }
 
 
        static string[ , ] MergeSort(string[ , ] arr, int first, int last)
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
            StreamReader input = new StreamReader("race.in");
             int n = Convert.ToInt32(input.ReadLine());
             string[,] arr = new string[n,2];
             for (int i = 0; i < n; i++)
             {
                string[] str = input.ReadLine().Split(' ');
                arr[i, 0] = str[0];
                arr[i, 1] = str[1];
             }
             MergeSort(arr, 0, n - 1);
             string current = "";
            StreamWriter output = new StreamWriter("race.out");
            for (int i = 0; i < n; i++)
             {
                 if(arr[i, 0] != current)
                 {
                     current = arr[i, 0];
                     output.Write("=== " + current + " ===\n");
                 }
                output.Write(arr[i, 1] + "\n");
             }
             input.Close();
             output.Close();
        }
    }
}
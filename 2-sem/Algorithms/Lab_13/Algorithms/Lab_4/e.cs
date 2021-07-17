using System;

namespace _1A
{
    class MainClass
    {
        static int Binsearch_first(int[] arr, int first, int last, int k)
        {
            if ((arr[first] <= k) && (arr[last] >= k))
            {
                int first_num;
                if (first == last)
                {
                    return first;
                }
                int mid = (first + last) / 2;
                if ((arr[first] <= k) && (arr[mid] >= k))
                {
                    first_num = Binsearch_first(arr, first, mid, k);
                }
                else first_num = Binsearch_first(arr, mid + 1, last, k);
                return first_num;
            }
            return -2;
        }
        static int Binsearch_last(int[] arr, int first, int last, int k)
        {
            if ((arr[first] <= k) && (arr[last] >= k))
            {
                int last_num;
                if (first == last)
                {
                    return first;
                }
                int mid = (first + last) / 2;
                if ((arr[mid + 1] <= k) && (arr[last] >= k))
                {
                    last_num = Binsearch_last(arr, mid + 1, last, k);
                }
                else last_num = Binsearch_last(arr, first, mid, k);
                return last_num;
            }
            return -2;
        }
        static void Main()
        {
            int n = Convert.ToInt32(Console.ReadLine());
            string[] str = Console.ReadLine().Split(' ');
            int[] arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = Convert.ToInt32(str[i]);
            }
            int m = Convert.ToInt32(Console.ReadLine());
            string[] request = Console.ReadLine().Split(' ');
            for (int i = 0; i < m; i++)
            {
                int numb = Convert.ToInt32(request[i]);
                int first = Binsearch_first(arr, 0, n - 1, numb);
                int last = Binsearch_last(arr, 0, n - 1, numb);
                first++;
                last++;
                Console.WriteLine(first + " " + last);
            }
        }
    }
}
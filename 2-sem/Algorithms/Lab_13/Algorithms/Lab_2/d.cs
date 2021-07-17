using System;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            int n = Convert.ToInt32(Console.ReadLine());
            int[] arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = i + 1;
            }
            for (int i = 2; i < n; i++)
            {
                int t = arr[i / 2];
                arr[i / 2] = arr[i];
                arr[i] = t;
            }
            for (int i = 0; i < n; i++)
            {
                Console.Write((arr[i]) + " ");
            }
        }
    }
}
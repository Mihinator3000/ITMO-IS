using System;
using System.IO;
using static System.Convert;
namespace PCMS
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader input = new StreamReader("input.txt");
            StreamWriter output = new StreamWriter("output.txt");
            string[] line = input.ReadLine().Split(' ');
            int n = ToInt32(line[0]);
            int m = ToInt32(line[1]);
            int[,] arr = new int[n, n];
            for (int i = 0; i < m; i++)
            {
                line = input.ReadLine().Split(' ');
                int u = ToInt32(line[0]);
                int v = ToInt32(line[1]);
                arr[u - 1, v - 1] = 1;
            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    output.Write($"{arr[i, j]} ");
                }
                output.WriteLine();
            }
            input.Close();
            output.Close();
        }
    }
}

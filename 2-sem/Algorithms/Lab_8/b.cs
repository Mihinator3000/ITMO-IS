using System;
using System.IO;
using static System.Convert;
namespace PCMS
{
    class Program
    {
        static bool Check(int n, int[,] arr)
        {
            for (int i = 0; i < n; i++)
            {
                if (arr[i, i] == 1) return false;
                for (int j = 0; j < i; j++)
                {
                    if (arr[i, j] != arr[j, i]) return false;
                }
            }
            return true;
            
        }
        static void Main(string[] args)
        {
            StreamReader input = new StreamReader("input.txt");
            StreamWriter output = new StreamWriter("output.txt");
            int n = ToInt32(input.ReadLine());
            int[,] arr = new int[n, n];
            for (int i = 0; i < n; i++)
            {
                string[] line = input.ReadLine().Split(' ');
                for (int j = 0; j < n; j++)
                {
                    arr[i, j] = ToInt32(line[j]);
                }
            }
            output.WriteLine(Check(n, arr) ? "YES" : "NO");
            input.Close();
            output.Close();
        }
    }
}

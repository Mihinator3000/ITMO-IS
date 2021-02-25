using System;
using System.Globalization;
using System.IO;
using System.Linq.Expressions;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("turtle.in");
            string[] hw = input.ReadLine().Split(' ');
            int h = Convert.ToInt32(hw[0]);
            int w = Convert.ToInt32(hw[1]);
            int[,] mass = new int[h, w];
            for (int i = h - 1; i >= 0; i--)
            {
                string[] inp = input.ReadLine().Split(' ');
                for (int j = 0; j < w; j++)
                {
                    mass[i, j] = Convert.ToInt32(inp[j]);
                }
            }
            for(int i = 1; i < h; i++)
            {
                mass[i, 0] += mass[i-1, 0];
            }
            for (int i = 1; i < w; i++)
            {
                mass[0, i] += mass[0, i-1];
            }
            for (int i = 1; i < h; i++)
            {
                for(int j = 1; j < w; j++)
                {
                    if (mass[i-1, j] > mass[i, j-1])
                    {
                        mass[i, j] += mass[i-1, j];
                    }
                    else mass[i, j] += mass[i, j-1];
                }
            }
            int outp = mass[h-1, w-1];
            StreamWriter output = new StreamWriter("turtle.out");
            output.Write(outp);
            input.Close();
            output.Close();
        }
    }
}
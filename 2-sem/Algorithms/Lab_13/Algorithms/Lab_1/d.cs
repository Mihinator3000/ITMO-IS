using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("smallsort.in");
            int amount = Convert.ToInt32(input.ReadLine());
            string[] inp = input.ReadLine().Split(' ');
            int[] mass = new int[amount];
            for(int i = 0; i < amount; i++)
            {
                mass[i] = Convert.ToInt32(inp[i]);
            }
            for(int i = 0; i < amount; i++)
            {
                for(int j = i; j < amount; j++)
                {
                    if(mass[j]<mass[i])
                    {
                        int t = mass[j];
                        mass[j] = mass[i];
                        mass[i] = t;
                    }
                }
            }
            StreamWriter output = new StreamWriter("smallsort.out");
            string outp = Convert.ToString(mass[0]);
            for(int i = 1; i<amount;i++)
            {
                outp += " " + mass[i];
            }
            output.Write(outp);
            input.Close();
            output.Close();
        }
    }
}
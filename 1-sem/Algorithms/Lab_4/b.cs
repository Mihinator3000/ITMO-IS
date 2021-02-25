using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("queue.in");
            int n = Convert.ToInt32(input.ReadLine());
            int[] stack = new int[1000000];
            int count = 0;
            int del_count = 0;
            StreamWriter output = new StreamWriter("queue.out");
            for (int i = 0; i < n; i++)
            {
                string[] str = input.ReadLine().Split(' ');
                if(str[0]=="+")
                {
                    stack[count] = Convert.ToInt32(str[1]);
                    count++;
                }
                else
                {
                    output.Write(stack[del_count] + "\n");
                    del_count++;
                }
            }
            input.Close();
            output.Close();
        }
    }
}
using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("aplusbb.in");
            string[] numb = input.ReadLine().Split(' ');
            long a = Convert.ToInt64(numb[0]);
            long b = Convert.ToInt64(numb[1]);
            StreamWriter output = new StreamWriter("aplusbb.out");
            output.Write(a + b * b);
            input.Close();
            output.Close();
        }
    }
}
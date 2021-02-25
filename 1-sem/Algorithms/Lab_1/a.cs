using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("aplusb.in");
            string[] numb = input.ReadLine().Split(' ');
            int sum = Convert.ToInt32(numb[0]) + Convert.ToInt32(numb[1]);
            StreamWriter output = new StreamWriter("aplusb.out");
            output.Write(sum);
            input.Close();
            output.Close();
        }
    }
}
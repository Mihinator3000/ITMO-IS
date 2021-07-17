using System;
using System.IO;
using System.Collections.Generic;
using static System.Convert;
namespace PCMS
{
    public class Info
    {
        public List<int> Links { get; set; }
        public Info()
        {
            Links = new List<int>();
        }
    }
    static class Programm
    {
        static void Main(string[] args)
        {
            var input = new StreamReader("input.txt");
            var output = new StreamWriter("output.txt");
            string[] line = input.ReadLine().Split(' ');
            int n = ToInt32(line[0]);
            int m = ToInt32(line[1]);
            var dots = new List<Info>();
            for (int i = 0; i < n; i++)
            {
                dots.Add(new Info() { });
            }
            for (int i = 0; i < m; i++)
            {
                line = input.ReadLine().Split(' ');
                int a = ToInt32(line[0]);
                int b = ToInt32(line[1]);
                dots[a - 1].Links.Add(b - 1);
                dots[b - 1].Links.Add(a - 1);
            }
            for (int i = 0; i < n; i++)
            {
                output.Write($"{dots[i].Links.Count} ");
            }
            input.Close();
            output.Close();
        }
    }
}

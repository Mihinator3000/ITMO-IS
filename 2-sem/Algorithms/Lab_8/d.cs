using System;
using System.IO;
using System.Collections.Generic;
using static System.Convert;
namespace PCMS
{
    public class Info
    {
        public List<int> Links { get; set; }
        public int Group { get; set; }
        public Info()
        {
            Links = new List<int>();
            Group = 0;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            string[] line = Console.ReadLine().Split(' ');
            int n = ToInt32(line[0]);
            int m = ToInt32(line[1]);
            var dots = new List<Info>();
            for (int i = 0; i < n; i++)
            {
                dots.Add(new Info() {});
            }
            for (int i = 0; i < m; i++)
            {
                line = Console.ReadLine().Split(' ');
                int b = ToInt32(line[0]);
                int e = ToInt32(line[1]);
                dots[b - 1].Links.Add(e - 1);
                dots[e - 1].Links.Add(b - 1);
            }
            int k = 0;
            for (int i = 0; i < n; i++)
            {
                if(dots[i].Group == 0)
                {
                    k++;
                    var queue = new Queue<int>();
                    int dot = i;
                    while (true)
                    {
                        dots[dot].Group = k;
                        for (int j = 0; j < dots[dot].Links.Count; j++)
                        {
                            int d = dots[dot].Links[j];
                            if (dots[d].Group == 0)
                            {
                                queue.Enqueue(d);
                            }
                        }
                        if (queue.Count > 0) dot = queue.Dequeue();
                        else break;
                    }
                }
            }
            Console.WriteLine(k);
            for (int i = 0; i < n; i++)
            {
                Console.Write($"{dots[i].Group} ");
            }
        }
    }
}

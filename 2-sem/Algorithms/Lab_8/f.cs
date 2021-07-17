using System;
using System.IO;
using System.Collections.Generic;
using static System.Convert;
namespace PCMS
{
    public class Links
    {
        public int Link { get; set; }
        public char Direction { get; set; }
        public Links(int i, char c)
        {
            Link = i;
            Direction = c;
        }
    }
    public class Info
    {
        public List<Links> Links { get; set; }
        public string Path { get; set; }
        public Info()
        {
            Links = new List<Links>();
            Path = null;
        }
    }
    class Program
    {
        static int Conv(int n, int m, int i, int j)
        {
            if (i < 0 || i >= n) return -1;
            if (j < 0 || j >= m) return -1;
            return m * i + j;
        }
        static char AntiD(char d)
        {
            switch (d)
            {
                case 'L':
                    return 'R';
                case 'R':
                    return 'L';
                case 'U':
                    return 'D';
                case 'D':
                    return 'U';
            }
            return ' ';
        }
        static void Sides(int centre, int n, int m, int i, int j, ref List<Info> dots, string[] field, char d)
        {
            int side = Conv(n, m, i, j);
            if (side != -1)
            {

                if (field[i][j] != '#')
                {
                    dots[centre].Links.Add(new Links(side, d));
                    dots[side].Links.Add(new Links(centre, AntiD(d)));
                }
            }
        }
        static int Func(int n, int m, int i, int j, ref List<Info> dots, string[] field)
        {
            int centre = Conv(n, m, i, j);
            if (field[i][j] != '#')
            {
                Sides(centre, n, m, i, j - 1, ref dots, field, 'L');
                Sides(centre, n, m, i, j + 1, ref dots, field, 'R');
                Sides(centre, n, m, i - 1, j, ref dots, field, 'U');
                Sides(centre, n, m, i + 1, j, ref dots, field, 'D');
                if (field[i][j] == 'S') return 1;
                if (field[i][j] == 'T') return 2;
            }
            return 0;
        }
        static void Main(string[] args)
        {
            var input = new StreamReader("input.txt");
            var output = new StreamWriter("output.txt");
            string[] line = input.ReadLine().Split(' ');
            int n = ToInt32(line[0]);
            int m = ToInt32(line[1]);
            var dots = new List<Info>();
            for (int i = 0; i < n * m; i++)
            {
                dots.Add(new Info() {});
            }
            var field = new string[n];
            for (int i = 0; i < n; i++)
            {
                field[i] = input.ReadLine();
            }
            int s = 0;
            int t = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {

                    int id = Conv(n, m, i, j);
                    int check = Func(n, m, i, j, ref dots, field);
                    if (check == 1) s = id;
                    if (check == 2) t = id;
                }
            }
            var queue = new Queue<int>();
            int dot = s;
            dots[dot].Path = string.Empty;
            while (true)
            {
                for (int j = 0; j < dots[dot].Links.Count; j++)
                {
                    int d = dots[dot].Links[j].Link;
                    if (dots[d].Path == null)
                    {

                        dots[d].Path = dots[dot].Path + dots[dot].Links[j].Direction;
                        queue.Enqueue(d);
                    }
                }
                if (queue.Count > 0)
                {
                    dot = queue.Dequeue();
                    if (dot == t)
                    {
                        output.WriteLine(dots[dot].Path.Length);
                        output.WriteLine(dots[dot].Path);
                        break;
                    }
                }
                else
                {
                    output.WriteLine("-1");
                    break;
                }
            }
            input.Close();
            output.Close();
        }
    }
}

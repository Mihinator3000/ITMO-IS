using System;
using System.IO;
using System.Collections.Generic;

namespace _1A
{
    public class Info
    {
        public static List<Info> arr = new List<Info>();
        public int K { get; set; }
        public int L { get; set; }
        public int R { get; set; }
        public int P { get; set; }
        public static int count = 0;
        public const int max = 1000000001;

    }
    class MainClass
    {
        static int Index(int x)
        {
            int i = 1;
            if (Info.count > 0)
            {
                while (true)
                {
                    if (Info.arr[i - 1].K == x)
                    {
                        return i;
                    }
                    else if (Info.arr[i - 1].K < x)
                    {
                        if (Info.arr[i - 1].R != 0) i = Info.arr[i - 1].R;
                        else return 0;
                    }
                    else if (Info.arr[i - 1].K > x)
                    {
                        if (Info.arr[i - 1].L != 0) i = Info.arr[i - 1].L;
                        else return 0;
                    }
                }
            }
            else return 0;
        }
        static string Next(int x)
        {
            int i = 1;
            int min = Info.max;
            if (Info.count > 0)
            {
                while (true)
                {
                    if (Info.arr[i - 1].K <= x)
                    {
                        if (Info.arr[i - 1].R != 0) i = Info.arr[i - 1].R;
                        else break;
                    }
                    else
                    {
                        if (Info.arr[i - 1].K < min) min = Info.arr[i - 1].K;
                        if (Info.arr[i - 1].L != 0) i = Info.arr[i - 1].L;
                        else break;
                    }
                }
                if (min == Info.max) return "none";
                else return Convert.ToString(min);
            }
            else return "none";
        }

        static string Prev(int x)
        {
            int i = 1;
            int max = -Info.max;
            if (Info.count > 0)
            {
                while (true)
                {
                    if (Info.arr[i - 1].K >= x)
                    {
                        if (Info.arr[i - 1].L != 0) i = Info.arr[i - 1].L;
                        else break;
                    }
                    else
                    {
                        if (Info.arr[i - 1].K > max) max = Info.arr[i - 1].K;
                        if (Info.arr[i - 1].R != 0) i = Info.arr[i - 1].R;
                        else break;
                    }
                }
                if (max == -Info.max) return "none";
                else return Convert.ToString(max);
            }
            else return "none";
        }
        static string Exists(int x)
        {
            int i = Index(x);
            if (i != 0) return "true";
            return "false";
        }
        static void Del_easy(int i)
        {
            int parent = Info.arr[i - 1].P;
            if ((Info.arr[i - 1].L == 0) && (Info.arr[i - 1].R == 0))
            {
                if (parent == 0)
                {
                    Info.arr.Clear();
                    return;
                }
                if (Info.arr[parent - 1].L == i) Info.arr[parent - 1].L = 0;
                else Info.arr[parent - 1].R = 0;
                Zeroing(i);
                return;
            }
            if (Info.arr[i - 1].L != 0)
            {
                if (parent == 0)
                {
                    int l = Info.arr[i - 1].L;
                    Info.arr[i - 1].K = Info.arr[l - 1].K;
                    Info.arr[i - 1].L = Info.arr[l - 1].L;
                    Info.arr[i - 1].R = Info.arr[l - 1].R;
                    if (Info.arr[l - 1].R != 0) Info.arr[Info.arr[l - 1].R - 1].P = i;
                    if (Info.arr[l - 1].L != 0) Info.arr[Info.arr[l - 1].L - 1].P = i;
                    Zeroing(l);
                    return;
                }
                if (Info.arr[parent - 1].L == i) Info.arr[parent - 1].L = Info.arr[i - 1].L;
                else Info.arr[parent - 1].R = Info.arr[i - 1].L;
                Info.arr[Info.arr[i - 1].L - 1].P = parent;
            }
            else
            {
                if (parent == 0)
                {
                    int r = Info.arr[i - 1].R;
                    Info.arr[i - 1].K = Info.arr[r - 1].K;
                    Info.arr[i - 1].L = Info.arr[r - 1].L;
                    Info.arr[i - 1].R = Info.arr[r - 1].R;
                    if (Info.arr[r - 1].R != 0) Info.arr[Info.arr[r - 1].R - 1].P = i;
                    if (Info.arr[r - 1].L != 0) Info.arr[Info.arr[r - 1].L - 1].P = i;
                    Zeroing(r);
                    return;
                }
                if (Info.arr[parent - 1].L == i) Info.arr[parent - 1].L = Info.arr[i - 1].R;
                else Info.arr[parent - 1].R = Info.arr[i - 1].R;
                Info.arr[Info.arr[i - 1].R - 1].P = parent;
            }
            Zeroing(i);
        }
        static void Del_hard(int i)
        {
            int r = Info.arr[i - 1].R;
            int index = r;
            while (true)
            {
                if (Info.arr[index - 1].L != 0)
                {
                    index = Info.arr[index - 1].L;
                }
                else break;
            }
            r = Info.arr[index - 1].R;
            if (r != 0)
            {
                Info.arr[r - 1].P = Info.arr[index - 1].P;
            }
            int check;
            if ((check = Info.arr[index - 1].P) != i)
            {
                Info.arr[check - 1].L = r;
            }
            else
            {
                Info.arr[check - 1].R = r;
            }
            Info.arr[i - 1].K = Info.arr[index - 1].K;
            Zeroing(index);
        }

        static void Zeroing(int i)
        {
            Info.arr[i - 1].P = 0;
            Info.arr[i - 1].K = Info.max;
            Info.arr[i - 1].L = 0;
            Info.arr[i - 1].R = 0;
        }
        static void Delete(int x)
        {
            if (Info.count > 0)
            {
                int i = Index(x);
                if (i != 0)
                {
                    Info.count--;
                    if (Info.count == 0)
                    {
                        Info.arr.Clear();
                        return;
                    }
                    if ((Info.arr[i - 1].L == 0) || (Info.arr[i - 1].R == 0))
                    {
                        Del_easy(i);
                    }
                    else
                    {
                        Del_hard(i);
                    }
                }
            }
        }
        static void Insert(int x)
        {
            Info.count++;
            int parent = 0;
            if (Info.count > 1)
            {
                int i = 1;
                while (true)
                {
                    if (Info.arr[i - 1].K < x)
                    {
                        if (Info.arr[i - 1].R == 0)
                        {
                            Info.arr[i - 1].R = Info.arr.Count + 1;
                            parent = i;
                            break;
                        }
                        else i = Info.arr[i - 1].R;
                    }
                    if (Info.arr[i - 1].K > x)
                    {
                        if (Info.arr[i - 1].L == 0)
                        {
                            Info.arr[i - 1].L = Info.arr.Count + 1;
                            parent = i;
                            break;
                        }
                        else i = Info.arr[i - 1].L;
                    }
                    if (Info.arr[i - 1].K == x)
                    {
                        Info.count--;
                        break;
                    }
                }
            }
            Info obj = new Info() { K = x, L = 0, R = 0, P = parent };
            Info.arr.Add(obj);
        }
        public static void Main()
        {
            StreamReader input = new StreamReader("bstsimple.in");
            StreamWriter output = new StreamWriter("bstsimple.out");
            string line;
            while ((line = input.ReadLine()) != null)
            {
                string[] command = line.Split(' ');
                int x = Convert.ToInt32(command[1]);
                switch (command[0])
                {
                    case "insert":
                        Insert(x);
                        break;
                    case "delete":
                        Delete(x);
                        break;
                    case "exists":
                        output.WriteLine(Exists(x));
                        break;
                    case "next":
                        output.WriteLine(Next(x));
                        break;
                    case "prev":
                        output.WriteLine(Prev(x));
                        break;
                }
            }
            input.Close();
            output.Close();
        }
    }
}
using System;
using System.IO;
using System.Collections.Generic;

namespace _1A
{
    public class Info
    {
        public static List<int>[] Hash = new List<int>[1000000];
    }
    class MainClass
    {
        public static int Id(int x)
        {
            int id = Math.Abs(x % 1000000);
            return id;
        }
        public static void Insert(int x)
        {
            int id = Id(x);
            if (Info.Hash[id] == null) Info.Hash[id] = new List<int>();
            if (!Info.Hash[id].Contains(x)) Info.Hash[id].Add(x);
        }
        public static void Delete(int x)
        {
            int id = Id(x);
            if (Info.Hash[id] != null)
                if (Info.Hash[id].Contains(x)) Info.Hash[id].Remove(x);
        }
        public static string Exists(int x)
        {
            int id = Id(x);
            if (Info.Hash[id] == null) return "false";
            if (Info.Hash[id].Contains(x)) return "true";
            return "false";
        }
        public static void Main()
        {
            StreamReader input = new StreamReader("set.in");
            StreamWriter output = new StreamWriter("set.out");
            string line;
            while ((line = input.ReadLine()) != null)
            {
                string[] str = line.Split(' ');
                int x = Convert.ToInt32(str[1]);
                switch (str[0])
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
                }
            }
            input.Close();
            output.Close();
        }
    }
}
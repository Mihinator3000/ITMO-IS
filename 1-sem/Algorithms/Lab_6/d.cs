using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace _1A
{
    public class Info
    {
        public static List<Info>[] Hash = new List<Info>[10000];
        public string X { get; set; }
        public List<string>[] Y { get; set; }
    }
    class MainClass
    {
        public static int Id(string x)
        {
            x = x.ToLower();
            int id = 0;
            int mult = 1;
            for (int i = 0; i < x.Length; i++)
            {
                id = (id + (x[i] - 97) * mult) % 10000;
                mult = (mult * 27) % 10000;
            }
            return id;
        }
        public static int Id2(string x)
        {
            x = x.ToLower();
            int id = 0;
            int mult = 1;
            for (int i = 0; i < x.Length; i++)
            {
                id = (id + (x[i] - 97) * mult) % 90;
                mult = (mult * 27) % 90;
            }
            return id;
        }
        public static void Put(string x, string y)
        {
            int id = Id(x);
            int id_y = Id2(y);
            if (Info.Hash[id] == null) Info.Hash[id] = new List<Info>();
            var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
            if (search == null)
            {
                List<string>[] arr_y = new List<string>[90];
                arr_y[id_y] = new List<string>();
                arr_y[id_y].Add(y);
                Info obj = new Info { X = x, Y = arr_y };
                Info.Hash[id].Add(obj);
                return;
            }
            int index = Info.Hash[id].IndexOf(search);
            if (Info.Hash[id][index].Y[id_y] != null)
            {
                if (!Info.Hash[id][index].Y[id_y].Contains(y)) Info.Hash[id][index].Y[id_y].Add(y);
            }
            else
            {
                Info.Hash[id][index].Y[id_y] = new List<string>();
                Info.Hash[id][index].Y[id_y].Add(y);
            }
        }
        public static void Delete(string x, string y)
        {
            int id = Id(x);
            int id_y = Id2(y);
            if (Info.Hash[id] != null)
            {
                var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
                if (search != null)
                {
                    int index = Info.Hash[id].IndexOf(search);
                    if (Info.Hash[id][index].Y[id_y] != null)
                    {
                        int search_y = Info.Hash[id][index].Y[id_y].IndexOf(y);
                        if (search_y != -1)
                        {
                            Info.Hash[id][index].Y[id_y].RemoveAt(search_y);
                        }
                    }
                }
            }
        }
        public static void DeleteAll(string x)
        {
            int id = Id(x);
            if (Info.Hash[id] != null)
            {
                var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
                if (search != null)
                {
                    int index = Info.Hash[id].IndexOf(search);
                    Info.Hash[id].RemoveAt(index);
                }
            }
        }
        public static void Main()
        {
            StreamReader input = new StreamReader("multimap.in");
            StreamWriter output = new StreamWriter("multimap.out");
            string line;
            while ((line = input.ReadLine()) != null)
            {
                string[] str = line.Split(' ');
                switch (str[0])
                {
                    case "put":
                        Put(str[1], str[2]);
                        break;
                    case "delete":
                        Delete(str[1], str[2]);
                        break;
                    case "deleteall":
                        DeleteAll(str[1]);
                        break;
                    case "get":
                        string x = str[1];
                        int id = Id(x);
                        if (Info.Hash[id] != null)
                        {
                            var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
                            if (search != null)
                            {
                                int index = Info.Hash[id].IndexOf(search);
                                int len = 0;
                                string s = "";
                                for (int i = 0; i < 90; i++)
                                {
                                    if (Info.Hash[id][index].Y[i] != null)
                                    {
                                        int len1 = Info.Hash[id][index].Y[i].Count();
                                        len += len1;
                                        for (int j = 0; j < len1; j++)
                                        {
                                            s += Info.Hash[id][index].Y[i][j] + " ";
                                        }
                                    }
                                }
                                output.WriteLine(len + " " + s);
                                continue;
                            }
                        }
                        output.WriteLine("0");
                        break;
                }
            }
            input.Close();
            output.Close();
        }
    }
}
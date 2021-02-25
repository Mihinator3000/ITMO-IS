using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
namespace _1A
{ 
    public class Info
    {
        public static List<Info>[] Hash = new List<Info>[1000000];
        public string X { get; set; }
        public string Y { get; set; }
        public string P { get; set; }
        public string N { get; set; }
        public static string Prev = "";
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
                id = (id + (x[i] - 97) * mult) % 1000000;
                mult = (mult * 27) % 1000000;
            }
            return id;
        }
        public static void Put(string x, string y)
        {
            int id = Id(x);
            if (Info.Hash[id] == null) Info.Hash[id] = new List<Info>();
            var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
            if (search == null)
            {
                Info obj = new Info { X = x, Y = y, P = Info.Prev, N = "" };
                Info.Hash[id].Add(obj);
                if (Info.Prev != "")
                {
                    int id_p = Id(Info.Prev);
                    int index_p = Search(Info.Prev, id_p);
                    if (index_p != -1)
                        Info.Hash[id_p][index_p].N = x;
                }
                Info.Prev = x;
                return;
            }
            int index = Info.Hash[id].IndexOf(search);
            Info.Hash[id][index].Y = y;
        }
        public static int Search(string x, int id)
        {
            if (Info.Hash[id] != null)
            {
                var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
                if (search != null)
                {
                    int index = Info.Hash[id].IndexOf(search);
                    return index;
                }
            }
            return -1;
        }
        public static void Delete(string x)
        {
            int id = Id(x);
            int index = Search(x, id);
            if (index != -1)
            {
                string prev = Info.Hash[id][index].P;
                string next = Info.Hash[id][index].N;
                int id_p;
                int id_n;
                if (prev == "" && next == "")
                {
                    Info.Prev = "";
                }
                else if (prev == "" && next != "")
                {
                    id_n = Id(next);
                    int index_n = Search(next, id_n);
                    if (index_n != -1)
                        Info.Hash[id_n][index_n].P = "";
                }
                else if (prev != "" && next == "")
                {
                    Info.Prev = prev;
                    id_p = Id(prev);
                    int index_p = Search(prev, id_p);
                    if (index_p != -1)
                        Info.Hash[id_p][index_p].N = "";
                }
                else
                {
                    id_n = Id(next);
                    int index_n = Search(next, id_n);
                    id_p = Id(prev);
                    int index_p = Search(prev, id_p);
                    if (index_n != -1 && index_p != -1)
                    {
                        Info.Hash[id_p][index_p].N = next;
                        Info.Hash[id_n][index_n].P = prev;
                    }
                }
                Info.Hash[id].RemoveAt(index);
                return;
            }    
        }
        public static string Prev(string x)
        {
            int id = Id(x);
            int index = Search(x, id);
            if (index != -1)
            {
                string prev = Info.Hash[id][index].P;
                if (prev != "")
                {
                    int id_p = Id(prev);
                    int index_p = Search(prev, id_p);
                    if (index_p != -1)
                    {
                        return Info.Hash[id_p][index_p].Y;
                    }
                }
            }
            return "none";
        }
        public static string Next(string x)
        {
            int id = Id(x);
            int index = Search(x, id);
            if (index != -1)
            {
                string next = Info.Hash[id][index].N;
                if (next != "")
                {
                    int id_n = Id(next);
                    int index_n = Search(next, id_n);
                    if (index_n != -1)
                    {
                        return Info.Hash[id_n][index_n].Y;
                    }
                }
            }
            return "none";
        }
        public static string Get(string x)
        {
            int id = Id(x);
            int index = Search(x, id);
            if (index != -1)
            {
                return Info.Hash[id][index].Y;
            }
            return "none";
        }
        public static void Main()
        {
            StreamReader input = new StreamReader("linkedmap.in");
            StreamWriter output = new StreamWriter("linkedmap.out");
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
                        Delete(str[1]);
                        break;
                    case "get":
                        output.WriteLine(Get(str[1]));
                        break;
                    case "next":
                        output.WriteLine(Next(str[1]));
                        break;
                    case "prev":
                        output.WriteLine(Prev(str[1]));
                        break;
                }
            }
            input.Close();
            output.Close();
        }
    }
}
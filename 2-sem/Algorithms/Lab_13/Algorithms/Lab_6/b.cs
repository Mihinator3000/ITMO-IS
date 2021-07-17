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
                Info obj = new Info { X = x, Y = y };
                Info.Hash[id].Add(obj);
                return;
            }
            int index = Info.Hash[id].IndexOf(search);
            Info.Hash[id][index].Y = y;
        }
        public static void Delete(string x)
        {
            int id = Id(x);
            if (Info.Hash[id] != null)
            {
                var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
                if (search != null)
                {
                    int index = Info.Hash[id].IndexOf(search);
                    Info.Hash[id].RemoveAt(index);
                    return;
                }
            }    
        }
        public static string Get(string x)
        {
            int id = Id(x);
            if (Info.Hash[id] != null)
            {
                var search = Info.Hash[id].FirstOrDefault(u => u.X == x);
                if (search != null)
                {
                    int index = Info.Hash[id].IndexOf(search);
                    return Info.Hash[id][index].Y;
                }
            }
            return "none";
        }
        public static void Main()
        {
            StreamReader input = new StreamReader("map.in");
            StreamWriter output = new StreamWriter("map.out");
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
                }
            }
            input.Close();
            output.Close();
        }
    }
}
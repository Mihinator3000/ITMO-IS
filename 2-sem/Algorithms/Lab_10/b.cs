using System;
using System.IO;
using System.Collections.Generic;
using static System.Convert;
using static System.Console;
namespace PCMS
{
    public class Vertex
    {
        public int x;
        public int y;
        public Vertex(int x_, int y_)
        {
            x = x_;
            y = y_;
        }
    }
    public class Info
    {
        public static int Commands_counter = 0;
        public static int Push_counter = 0;
        public static List<int> Line = new List<int>();
        public static int Heap_length = 0;
    }
    public class List
    {
        public static List<List> Heap = new List<List>();
        public double Key { get; set; }
        public int Original { get; set; }
        public bool Check = false;

        public static void Swap<T>(IList<T> list, int index_a, int index_b)
        {
            T temp = list[index_a];
            list[index_a] = list[index_b];
            list[index_b] = temp;
        }
        public static void Increase_key(int increase)
        {
            while ((increase != 0) && (List.Heap[increase].Key) < List.Heap[(increase - 1) / 2].Key)
            {
                Swap(List.Heap, (increase - 1) / 2, increase);
                Swap(Info.Line, List.Heap[(increase - 1) / 2].Original, List.Heap[increase].Original);
                increase = (increase - 1) / 2;
            }
        }
        public static void Push(int x)
        {
            List obj = new List() { Key = x, Original = Info.Commands_counter };
            List.Heap.Add(obj);
            Info.Line.Add(Info.Push_counter);
            Info.Push_counter++;
            Increase_key(List.Heap.Count - 1);
            Info.Heap_length++;
        }
        public static void Decrease_min(int i)
        {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if ((left < Info.Push_counter) && (List.Heap[left].Key < List.Heap[smallest].Key))
            {
                smallest = left;
            }
            if ((right < Info.Push_counter) && (List.Heap[right].Key < List.Heap[smallest].Key))
            {
                smallest = right;
            }
            if (smallest != i)
            {
                Swap(List.Heap, i, smallest);
                Swap(Info.Line, List.Heap[i].Original, List.Heap[smallest].Original);
                Decrease_min(smallest);
            }
        }
        public static int Extract_min()
        {
            Info.Line.Add(0);
            if (Info.Heap_length == 0) return -1;
            int i = List.Heap[0].Original;
            List.Heap[0].Key = Int32.MaxValue;
            Decrease_min(0);
            Info.Heap_length--;
            return i;
        }
        public static void Decrease_key(int x, double y)
        {
            Info.Line.Add(0);
            List.Heap[Info.Line[x]].Key = y;
            Increase_key(Info.Line[x]);
        }
    }

    class MainClass
    {
        public static double Distance(Vertex a, Vertex b)
        {
            return Math.Sqrt(Math.Pow(a.x - b.x, 2) + Math.Pow(a.y - b.y, 2));
        }
        public static void Main()
        {
            int n = ToInt32(ReadLine());
            var v = new List<Vertex>();
            for (int i = 0; i < n; i++)
            {
                List.Push(Int32.MaxValue);
                Info.Commands_counter++;
                string[] line = ReadLine().Split(' ');
                v.Add(new Vertex(ToInt32(line[0]), ToInt32(line[1])));
            }
            List.Heap[0].Key = 0;
            double len = 0;
            while(Info.Heap_length != 0)
            {
                len += List.Heap[0].Key;
                List.Heap[0].Check = true;
                int u = List.Extract_min();
                for (int i = 0; i < n; i++)
                {
                    if(!List.Heap[Info.Line[i]].Check)
                    {
                        double d = Distance(v[u], v[i]);
                        if (d < List.Heap[Info.Line[i]].Key)
                        {
                            List.Decrease_key(i, d);
                        }
                    }
                }
            }
            WriteLine(len);
        }
    }
}
using System;
using System.Collections.Generic;

namespace _1A
{
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
        public int Number { get; set; }
        public int Original { get; set; }

    }
    class MainClass
    {
        public static void Swap<T>(IList<T> list, int index_a, int index_b)
        {
            T temp = list[index_a];
            list[index_a] = list[index_b];
            list[index_b] = temp;
        }
        static void Increase_key(int increase)
        {
            while ((increase != 0) && (List.Heap[increase].Number) < List.Heap[(increase - 1) / 2].Number)
            {
                Swap(List.Heap, (increase - 1) / 2, increase);
                Swap(Info.Line, List.Heap[(increase - 1) / 2].Original, List.Heap[increase].Original);
                increase = (increase - 1) / 2;
            }
        }
        static void Push(int x)
        {
            List obj = new List() { Number = x, Original = Info.Commands_counter };
            List.Heap.Add(obj);
            Info.Line.Add(Info.Push_counter);
            Info.Push_counter++;
            Increase_key(List.Heap.Count - 1);
            Info.Heap_length++;
        }
        static void Decrease_min(int i)
        {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if ((left < Info.Push_counter) && (List.Heap[left].Number < List.Heap[smallest].Number))
            {
                smallest = left;
            }
            if ((right < Info.Push_counter) && (List.Heap[right].Number < List.Heap[smallest].Number))
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
        static void Extract_min()
        {
            Info.Line.Add(0);
            if (Info.Heap_length == 0)
            {
                Console.WriteLine("*");
            }
            else
            {
                Console.WriteLine(List.Heap[0].Number);
                List.Heap[0].Number = Int32.MaxValue;
                Decrease_min(0);
                Info.Heap_length--;
            }
        }
        static void Decrease_key(int x, int y)
        {
            Info.Line.Add(0);
            List.Heap[Info.Line[x]].Number = y;
            Increase_key(Info.Line[x]);
        }
        public static void Main()
        {
            string line;
            while ((line = Console.ReadLine()) != null)
            {
                string[] info = line.Split(' ');
                switch (info[0])
                {
                    case "push":
                        Push(Convert.ToInt32(info[1]));
                        break;
                    case "decrease-key":
                        Decrease_key(Convert.ToInt32(info[1]) - 1, Convert.ToInt32(info[2]));
                        break;
                    case "extract-min":
                        Extract_min();
                        break;
                }
                Info.Commands_counter++;
            }
        }
    }
}
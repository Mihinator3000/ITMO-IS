using System;
using System.Collections.Generic;

namespace _1A
{
    public class Info
    {
        public static List<string> commands = new List<string>();
        public static List<UInt16> queue = new List<UInt16>();
        public static int head = 0;
        public static int tail = 0;
        public static UInt16[] registers = new UInt16[26];
        public static Dictionary<string, int> label = new Dictionary<string, int>();

    }
    class MainClass
    {
        public static UInt16 Get()
        {
            if (Info.head < Info.tail)
            {
                UInt16 x = Info.queue[Info.head];
                Info.head++;
                return x;
            }
            return 0;
        }
        public static void Put(UInt16 x)
        {
            Info.tail++;
            Info.queue.Add(x);
        }
        public static void Main()
        {
            string line;
            while ((line = Console.ReadLine()) != null && line != "") 
            {
                Info.commands.Add(line);
                if (line[0] == ':')
                {
                    Info.label.Add(line.Substring(1), Info.commands.Count - 1);
                }
            }
            int counter = 0;
            while (counter < Info.commands.Count)
            {
                line = Info.commands[counter];
                counter++;
                UInt16 x;
                UInt16 y;
                int id;
                int id2;
                switch (line[0])
                {
                    case '+':
                        x = Get();
                        y = Get();
                        Put((ushort)((x + y) % 65536));
                        break;
                    case '-':
                        x = Get();
                        y = Get();
                        Put((ushort)((x - y) % 65536));
                        break;
                    case '*':
                        x = Get();
                        y = Get();
                        Put((ushort)((x * y) % 65536));
                        break;
                    case '/':
                        x = Get();
                        y = Get();
                        if (y == 0) Put(0);
                        else Put(Convert.ToUInt16(x / y));
                        break;
                    case '%':
                        x = Get();
                        y = Get();
                        if (y == 0) Put(0);
                        else Put(Convert.ToUInt16(x % y));
                        break;
                    case '>':
                        id = Convert.ToInt32(line[1]) - 97;
                        Info.registers[id] = Get();
                        break;
                    case '<':
                        id = Convert.ToInt32(line[1]) - 97;
                        x = Info.registers[id];
                        Put(x);
                        break;
                    case 'P':
                        if (line.Length == 1)
                        {
                            Console.WriteLine(Get());
                        }
                        else
                        {
                            id = Convert.ToInt32(line[1]) - 97;
                            Console.WriteLine(Info.registers[id]);
                        }
                        break;
                    case 'C':
                        if (line.Length == 1)
                        {
                            Console.Write(Convert.ToChar(Get() % 256));
                        }
                        else
                        {
                            id = Convert.ToInt32(line[1]) - 97;
                            Console.Write(Convert.ToChar(Info.registers[id] % 256));
                        }
                        break;
                    case ':':
                        break;
                    case 'J':
                        counter = Info.label[line.Substring(1)];
                        break;
                    case 'Z':
                        id = Convert.ToInt32(line[1]) - 97;
                        if (Info.registers[id] == 0)
                        {
                            counter = Info.label[line.Substring(2)];
                        }
                        break;
                    case 'E':
                        id = Convert.ToInt32(line[1]) - 97;
                        id2 = Convert.ToInt32(line[2]) - 97;
                        if (Info.registers[id] == Info.registers[id2])
                        {
                            counter = Info.label[line.Substring(3)];
                        }
                        break;
                    case 'G':
                        id = Convert.ToInt32(line[1]) - 97;
                        id2 = Convert.ToInt32(line[2]) - 97;
                        if (Info.registers[id] > Info.registers[id2])
                        {
                            counter = Info.label[line.Substring(3)];
                        }
                        break;
                    case 'Q':
                        return;
                    default:
                        Put(Convert.ToUInt16(line));
                        break;
                }
            }
        }
    }
}
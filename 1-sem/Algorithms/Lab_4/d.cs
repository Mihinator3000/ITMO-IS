using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("postfix.in");
            string[] str = input.ReadLine().Split(' ');
            input.Close();
            int count = str.Length;
            int counter = 0;
            while ((count != 1) && (counter <= count))
            {
                if (str[counter] == "+")
                {
                    str[counter - 2] = Convert.ToString(Convert.ToInt32(str[counter - 2]) + Convert.ToInt32(str[counter - 1]));
                    for (int i = counter - 1; i < count - 2; i++)
                    {
                        str[i] = str[i + 2];
                    }
                    count -= 2;
                    counter -= 2;
                    continue;
                }
                if (str[counter] == "-")
                {
                    str[counter - 2] = Convert.ToString(Convert.ToInt32(str[counter - 2]) - Convert.ToInt32(str[counter - 1]));
                    for (int i = counter - 1; i < count - 2; i++)
                    {
                        str[i] = str[i + 2];
                    }
                    count -= 2;
                    counter -= 2;
                    continue;
                }
                if (str[counter] == "*")
                {
                    str[counter - 2] = Convert.ToString(Convert.ToInt32(str[counter - 2]) * Convert.ToInt32(str[counter - 1]));
                    for (int i = counter - 1; i < count - 2; i++)
                    {
                        str[i] = str[i + 2];
                    }
                    count -= 2;
                    counter -= 2;
                    continue;
                }
                counter++;
            }
            StreamWriter output = new StreamWriter("postfix.out");
            output.Write(str[0]);
            output.Close();
        }
    }
}
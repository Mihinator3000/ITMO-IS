using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("brackets.in");
            StreamWriter output = new StreamWriter("brackets.out");
            string line;
            while((line = input.ReadLine()) != null)
            {
                char[] stack = new char[10000];
                int count = 0;
                bool brackets = true;
                for (int i = 0; i < line.Length; i++)
                {
                    if((line[i] == '(')||(line[i] == '['))
                    {
                        stack[count] = line[i];
                        count++;
                    }
                    if (line[i] == ')')
                    {
                        if (count != 0)
                        {
                            if (stack[count - 1] == '[')
                            {
                                brackets = false;
                                break;
                            }
                            else count--;
                        }
                        else
                        {
                            brackets = false;
                            break;
                        }
                    }
                    if (line[i] == ']')
                    {
                        if (count != 0)
                        {
                            if (stack[count - 1] == '(')
                            {
                                brackets = false;
                                break;
                            }
                            else count--;
                        }
                        else
                        {
                            brackets = false;
                            break;
                        }
                    }
                }
                if (count != 0) brackets = false;
                if (brackets) output.Write("YES\n");
                else output.Write("NO\n");
            }
            input.Close();
            output.Close();
        }
    }
}
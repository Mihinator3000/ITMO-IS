using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("isheap.in");
            int n = Convert.ToInt32(input.ReadLine());
            string[] str = input.ReadLine().Split(' ');
            int[] a = new int[n + 1];
            for (int i = 1; i <= n; i++)
            {
                a[i] = Convert.ToInt32(str[i - 1]);
            }

            bool pyramid = true;
            for (int i = 1; i <= n; i++)
            {
                if ((2 * i <= n) && (a[i] > a[2 * i]))
                {
                    pyramid = false;
                    break;
                }
                if ((2 * i + 1 <= n) && (a[i] > a[2 * i + 1]))
                {
                    pyramid = false;
                    break;
                }
            }
            string outp;
            if (pyramid)
            {
                outp = "YES";
            }
            else
            {
                outp = "NO";
            }
            StreamWriter output = new StreamWriter("isheap.out");
            input.Close();
            output.Write(outp);
            output.Close();
        }
    }
}
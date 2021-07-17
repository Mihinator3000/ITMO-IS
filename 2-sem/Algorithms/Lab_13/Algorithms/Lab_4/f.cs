using System;

namespace _1A
{
    class Programm
    {
        public static double BinSearch(double[] h, int n)
        {
            double left = 0;
            double right = h[0];
            while (right - left > 0.000001)
            {
                double mid = (left + right) / 2;
                bool all_positive = true;
                h[1] = mid;
                for (int i = 2; i < n; i++)
                {
                    h[i] = h[i - 1] * 2 - h[i - 2] + 2;
                    if (h[i] < 0)
                    {
                        all_positive = false;
                        break;
                    }
                }
                if (all_positive) right = mid;
                else left = mid;
            }
            return h[n - 1];
        }
        public static void Main()
        {
            string[] str = Console.ReadLine().Split();
            int n = Convert.ToInt32(str[0]);
            double[] h = new double[n];
            h[0] = Convert.ToDouble(str[1]);
            double last = BinSearch(h, n);
            double round = Math.Floor(last * 100) / 100;
            Console.WriteLine(Convert.ToString(round));
        }
    }
}
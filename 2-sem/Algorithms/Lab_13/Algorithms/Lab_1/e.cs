using System;
using System.IO;

namespace _1A
{
    class MainClass
    {
        static void Main()
        {
            StreamReader input = new StreamReader("sortland.in");
            int amount = Convert.ToInt32(input.ReadLine());
            string[] inp = input.ReadLine().Split(' ');
            double[] mass = new double[amount];
            double[] original = new double[amount];
            for (int i = 0; i < amount; i++)
            {
                inp[i]=inp[i].Replace('.', ',');
                mass[i] = Convert.ToDouble(inp[i]);
                original[i] = mass[i];
            }
            for (int i = 0; i < amount; i++)
            {
                for(int j = i; j < amount; j++)
                {
                    if(mass[j]<mass[i])
                    {
                        double t = mass[j];
                        mass[j] = mass[i];
                        mass[i] = t;
                    }
                }
            }
            double min=mass[0], mid=mass[(amount-1)/2], max=mass[amount-1];
            int n_min=-1, n_mid=-1, n_max=-1;
            for(int i = 0; i < amount; i++)
            {
                if (original[i] == min) n_min = i;
                if (original[i] == mid) n_mid = i;
                if (original[i] == max) n_max = i;
            }
            StreamWriter output = new StreamWriter("sortland.out");
            string outp = Convert.ToString(n_min+1)+ " " + Convert.ToString(n_mid+1) + " " +Convert.ToString(n_max+1);
            output.Write(outp);
            input.Close();
            output.Close();
        }
    }
}
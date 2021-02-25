using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace Digital_culture
{
    class Program
    {
        static void Forth_function()
        {
            StreamReader input = new StreamReader("brain.txt");
            List<string> words = new List<string>();
            string line;
            while ((line = input.ReadLine()) != null)
            {
                string[] split = line.Split(' ', '!', '?', ',', ';', '.', ':', '—', '«', '(', ')', '»');
                for (int i = 0; i < split.Length; i++)
                {
                    if (split[i] != "") words.Add(split[i].ToLower());
                }
            }
            input.Close();
            Console.WriteLine("Количество словоформ: " + words.Count);
            List<string> new_words = new List<string>();
            for (int i = 0; i < words.Count; i++)
            {
                if (!new_words.Contains(words[i])) new_words.Add(words[i]);
            }
            Console.WriteLine("Количество разных словоформ: " + new_words.Count);
            List<string> dictionary = new List<string>();
            List<int> frequency = new List<int>();
            StreamReader dict = new StreamReader("dict1.txt", Encoding.GetEncoding(1251));
            while ((line = dict.ReadLine()) != null)
            {
                string[] str = line.Split(' ');
                dictionary.Add(str[0]);
                frequency.Add(Convert.ToInt32(str[1]));
            }
            dict.Close();
            int count = 0;
            for (int i = 0; i < new_words.Count; i++)
            {
                if (dictionary.Contains(new_words[i])) count++;
            }
            Console.WriteLine("Присутствуют в словаре: " + count);
        }
        static int Equal(string a, string b)
        {
            bool check = false;
            if (Math.Abs(a.Length - b.Length) > 1) return 0;
            if (a.Length == b.Length + 1) check = true;
            for (int i = 0; i < b.Length; i++)
            {
                if (a[i] != b[i]) return 0;
            }
            if (check) return 2;
            return 1;

        }
        static int Editorial_distance(string a, string b)
        {
            if (Math.Abs(a.Length - b.Length) > 2) return 3;
            if (a.Length - b.Length == 2)
            {
                int difference = 0;
                int i = 0, j = 0;
                while ((i < a.Length) && (j < b.Length))
                {
                    if (a[i] == b[j])
                    {
                        i++;
                        j++;
                    }
                    else
                    {
                        difference++;
                        j++;
                    }
                }
                if (difference == 2 && i == a.Length - 1) return 2;
                else return 3;
            }
            if (a.Length - b.Length == -2)
            {
                int difference = 0;
                int i = 0, j = 0;
                while ((i < a.Length) && (j < b.Length))
                {
                    if (a[i] == b[j])
                    {
                        i++;
                        j++;
                    }
                    else
                    {
                        difference++;
                        i++;
                    }
                }
                if (difference == 2 && j == b.Length - 1) return 2;
                else return 3;
            }
            if (a.Length - b.Length == 1)
            {
                int difference = 0;
                int dif = 0;
                int i = 0, j = 0;
                while ((i < a.Length) && (j < b.Length))
                {
                    if (a[i] == b[j])
                    {
                        i++;
                        j++;
                    }
                    else
                    {
                        if (difference == 1)
                        {
                            dif++;
                            i++;
                            j++;
                        }
                        else
                        {
                            difference++;
                            i++;
                        }
                    }
                }
                if (difference + dif <= 2) return difference + dif;
                else return 3;
            }
            if (a.Length - b.Length == -1)
            {
                int difference = 0;
                int dif = 0;
                int i = 0, j = 0;
                while ((i < a.Length) && (j < b.Length))
                {
                    if (a[i] == b[j])
                    {
                        i++;
                        j++;
                    }
                    else
                    {
                        if (difference == 1)
                        {
                            dif++;
                            i++;
                            j++;
                        }
                        else
                        {
                            difference++;
                            j++;
                        }
                    }
                }
                if (difference + dif <= 2) return difference;
                else return 3;
            }
            if (a.Length == b.Length)
            {
                int difference = 0;
                for (int i = 0; i < a.Length; i++)
                {
                    if (a[i] != b[i]) difference++; 
                }
                return difference;
            }
            return 0;
        }
        static void Main()
        {
            StreamReader input = new StreamReader("brain068.txt", Encoding.GetEncoding(1251));
            List<string> words = new List<string>();
            string line;
            while ((line = input.ReadLine()) != null)
            {
                string[] split = line.Split(' ', '!', '?', ',', ';', '.', ':', '—', '«', '(', ')', '»');
                for (int i = 0; i < split.Length; i++)
                {
                    if (split[i] != "") words.Add(split[i].ToLower());
                }
            }
            input.Close();
            Console.WriteLine("Количество словоформ: " + words.Count);
            List<string> new_words = new List<string>();
            for (int i = 0; i < words.Count; i++)
            {
                if (!new_words.Contains(words[i])) new_words.Add(words[i]);
            }
            Console.WriteLine("Количество разных словоформ: " + new_words.Count);
            List<string> dictionary = new List<string>();
            List<int> frequency = new List<int>();
            List<string> probable_mistakes = new List<string>();
            StreamReader dict = new StreamReader("dict1.txt", Encoding.GetEncoding(1251));
            while ((line = dict.ReadLine()) != null)
            {
                string[] str = line.Split(' ');
                dictionary.Add(str[0]);
                frequency.Add(Convert.ToInt32(str[1]));
            }
            dict.Close();
            int count = 0;
            for (int i = 0; i < new_words.Count; i++)
            {
                if (!dictionary.Contains(new_words[i]))
                {
                    probable_mistakes.Add(new_words[i]);
                }
                else count++;
            }
            Console.WriteLine("Присутствуют в словаре: " + count);
            Console.WriteLine("Возможные ошибки: " + probable_mistakes.Count);
            string[] corrected_mistakes = new string[probable_mistakes.Count];
            probable_mistakes.CopyTo(corrected_mistakes);
            for (int i = 0; i < probable_mistakes.Count; i++)
            {
                List<string> possible_versions_1 = new List<string>();
                List<int> freq_1 = new List<int>();
                List<string> possible_versions_2 = new List<string>();
                List<int> freq_2 = new List<int>();
                for (int j = 0; j < dictionary.Count; j++)
                {
                    int distance = Editorial_distance(probable_mistakes[i], dictionary[j]);
                    if (distance == 1)
                    {
                        possible_versions_1.Add(dictionary[j]);
                        freq_1.Add(frequency[j]);
                    }
                    else if (distance == 2)
                    {
                        possible_versions_2.Add(dictionary[j]);
                        freq_2.Add(frequency[j]);
                    }
                }
                int f = 0;
                if (possible_versions_1.Count > 0)
                {
                    for (int j = 0; j < possible_versions_1.Count; j++)
                    {
                        if (freq_1[j] > f)
                        {
                            corrected_mistakes[i] = possible_versions_1[j];
                            f = freq_1[j];
                        }
                    }
                }
                else if (possible_versions_2.Count > 0)
                {
                    for (int j = 0; j < possible_versions_2.Count; j++)
                    {
                        if (freq_2[j] > f)
                        {
                            corrected_mistakes[i] = possible_versions_2[j];
                            f = freq_2[j];
                        }
                    }
                }
                else corrected_mistakes[i] = "не найдено";
            }
            input = new StreamReader("brain068.txt", Encoding.GetEncoding(1251));
            StreamWriter output = new StreamWriter("brain.txt");
            while ((line = input.ReadLine()) != null)
            {
                string outp = "";
                string[] split = line.Split(' ');
                for (int i = 0; i < split.Length; i++)
                {
                    bool check = false;
                    for (int j = 0; j < probable_mistakes.Count; j++)
                    {
                        int equality = Equal(split[i], probable_mistakes[j]);
                        if (equality == 1)
                        {
                            check = true;
                            outp += (corrected_mistakes[j] + " ");
                            break;
                        }
                        if (equality == 2)
                        {
                            check = true;
                            outp += (corrected_mistakes[j] + split[i][split[i].Length - 1] + " ");
                        }
                    }
                    if (!check) outp += (split[i] + " ");
                }
                output.WriteLine(outp.Substring(0, outp.Length - 1));
            }
            input.Close();
            output.Close();
            Forth_function();
            for (int i = 0; i < probable_mistakes.Count; i++)
            {
                Console.Write(probable_mistakes[i] + " - " + corrected_mistakes[i]);
                if (corrected_mistakes[i] == "не найдено") Console.WriteLine(" > 2");
                else Console.WriteLine(" - " + Editorial_distance(probable_mistakes[i], corrected_mistakes[i]));
            }
            Console.ReadKey();
        }
    }
}

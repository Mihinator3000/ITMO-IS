import math as m
import numpy as n
from skimage.io import imread


def message(arr):
    mess = []
    for i in range(128):
        mess.append(arr[64][i][1])
        mess[i] = round(mess[i] // 20) * 20
    print(mess)
    return mess


def frequent(mess):
    f = [0] * 256
    for i in range(128):
        f[mess[i]] += 0.0078125
        # Нахождение частоты для каждого элемента
    return f


def bin(n):
    s = ""
    for i in range(8):
        s += str(n % 2)
        n //= 2
    return ''.join(reversed(s))


def ent(frequency):
    entropy = 0
    for i in range(256):
        if frequency[i] != 0:
            entropy += (frequency[i] * m.log2(frequency[i]))
            # Подсчет энтропии
    return -entropy


image = imread("cat.png")
# Чтение изображение
arr = n.array(image)
# Запись изображения в массив
mess = message(arr)
# Квантование строки по заданной формуле

frequency = frequent(mess)
# Нахождение частоты встречаемости
frequency_output = [0] * 256
frequency_number = [0] * 256
counter = 0
for i in range(256):
    if frequency[i] != 0:
        frequency_output[counter] += frequency[i]
        frequency_number[counter] = i
        counter += 1
# Подсчет количества символов
for i in range(counter):
    for j in range(i, counter):
        if frequency_output[i] < frequency_output[j]:
            t = frequency_output[i]
            frequency_output[i] = frequency_output[j]
            frequency_output[j] = t
            t = frequency_number[i]
            frequency_number[i] = frequency_number[j]
            frequency_number[j] = t
# Сортировка элементов по встречаемости
for i in range(counter):
    print(frequency_number[i], " ", frequency_output[i])
# Вывод символов по встремости
numb = m.ceil(m.log2(counter))
# Подсчет количества символов в алфавите
entropy = ent(frequency)
# Подсчет энтропии
leng = 128 * numb
# Подсчет длины двоичного кода
print(counter)
print(numb)
print(entropy)
print(leng)
# Вывод данных

for i in range(128):
    if mess[i] == 140:
        mess[i] = 0
    if mess[i] == 240:
        mess[i] = 1
    if mess[i] == 80:
        mess[i] = 2
    if mess[i] == 100:
        mess[i] = 3
    if mess[i] == 120:
        mess[i] = 4
    if mess[i] == 60:
        mess[i] = 5
    if mess[i] == 180:
        mess[i] = 6
    if mess[i] == 160:
        mess[i] = 7

print(mess)
code_equal = [
    "000",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110",
    "111"
]
# Присваивание значений для равномерного кода
line_equal = ""

code_shannon_fano = [
    "1",
    "01",
    "001",
    "0001",
    "00001",
    "000001",
    "0000001",
    "0000000"
]
# Присваивание значений для кода Шеннона-Фано
line_shannon_fano = ""

code_huffman = [
    "0",
    "10",
    "110",
    "1110",
    "11110",
    "111110",
    "1111110",
    "1111111"
]
# Присваивание значений для кода Хаффмана
line_huffman = ""

for i in range(128):
    line_equal += code_equal[mess[i - 1]]
    line_shannon_fano += code_shannon_fano[mess[i - 1]]
    line_huffman += code_huffman[mess[i - 1]]

print(line_equal, "\n 3", len(line_equal))
# Вывод полученной строки и значений
print(line_shannon_fano, "\n", len(line_shannon_fano) / 128, len(line_shannon_fano))
# Вывод полученной строки и значений для задания 9
print(line_huffman, "\n", len(line_huffman) / 128, len(line_huffman))
# Вывод полученной строки и значений для задания 10

print(len(line_shannon_fano) / len(line_equal), 1 - entropy / (len(line_shannon_fano) / 128))
# Вывод степени сжатия сообщения и относительной избыточности для кода Шеннона-Фано
print(len(line_huffman) / len(line_equal), 1 - entropy / (len(line_huffman) / 128))
# Вывод степени сжатия сообщения и относительной избыточности для кода Хаффмана

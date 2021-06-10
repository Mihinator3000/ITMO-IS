#include "components.h"

Cube::Cube()
{
    sides = {'y', 'w', 'b', 'g', 'o', 'r'};
}

char& Cube::operator [] (const int i)
{
    if (i >= 0 && i < SIDES_COUNT)
        return sides[i];
    throw std::out_of_range("Indexation of cube out of range");
}

int Cube::sideToInt(const std::string s) const
{
    if (s == "top")
        return 0;
    if (s == "down")
        return 1;
    if (s == "front")
        return 2;
    if (s == "back")
        return 3;
    if (s == "left")
        return 4;
    if (s == "right")
        return 5;
    throw std::out_of_range("Indexation of cube out of range");
}

char& Cube::operator [] (const std::string s)
{
    return sides[sideToInt(s)];
}


std::string Cube::inversion(std::string s) const
{
    if (s == "up")
        return "down";
    else if (s == "down")
        return "up";
    else if (s == "left")
        return "right";
    else if (s == "right")
        return "left";
    else if (s == "up_dop")
        return "down_dop";
    else if (s == "down_dop")
        return "up_dop";
    throw std::runtime_error("No such rotation");
}

void Cube::rotation(std::string s, bool inv)
{
    if (inv)
        s = inversion(s);
    std::vector<int> rotation_order;
    if (s == "up")
    {
        rotation_order = {0, 2, 1, 3};
    }
    else if (s == "down")
    {
        rotation_order = {0, 3, 1, 2};
    }
    else if (s == "left")
    {
        rotation_order = {2, 5, 3, 4};
    }
    else if (s == "right")
    {
        rotation_order = {2, 4, 3, 5};
    }
    else if (s == "up_dop")
    {
        rotation_order = {0, 5, 1, 4};
    }
    else if (s == "down_dop")
    {
        rotation_order = {0, 4, 1, 5};
    }
    else
        throw std::runtime_error("No such rotation");

    char c = sides[rotation_order[0]];
    for (int i = 1; i < ROTATIONS_COUNT; i++)
    {
        sides[rotation_order[i - 1]] = sides[rotation_order[i]];
    }
    sides[rotation_order[ROTATIONS_COUNT - 1]] = c;
}

std::vector<char> Cube::getColors()
{
    std::vector<char> a;
    for (int i = 0; i < SIDES_COUNT; i++)
    {
        if(sides[i] != 'd')
            a.push_back(sides[i]);
    }
    return a;
}

void Info::vector_init()
{
    for (int i = 0; i < SIDE_LENGHT; i++)
    {
        std::vector<std::vector<Cube>> layer1;
        for (int j = 0; j < SIDE_LENGHT; j++)
        {
            std::vector<Cube> layer2;
            for (int k = 0; k < SIDE_LENGHT; k++)
            {
                layer2.push_back(Cube());
            }
            layer1.push_back(layer2);
        }
        cubes.push_back(layer1);
    }
}

Info::Info()
{
    vector_init();
    for (int i = 0; i < SIDE_LENGHT; i++)
    {
        for (int j = 0; j < SIDE_LENGHT; j++)
        {
            for (int k = 0; k < SIDE_LENGHT; k++)
            {
                bool checks[6]
                {
                    j < 2, j > 0, k < 2, k > 0, i > 0, i < 2
                };

                for (int t = 0; t < SIDES_COUNT; t++)
                {
                    if (checks[t])
                        cubes[i][j][k][t] = 'd';
                }
            }
        }
    }
}

Cube& Info::operator () (int i, int j, int k)
{
    if ((i >= -1 && i <= 1) &&
        (j >= -1 && j <= 1) &&
        (k >= -1 && k <= 1))
    {
        return cubes[i + 1][j + 1][k + 1];
    }
    throw std::out_of_range("Indexation out of range");
}

Cube& Info::operator() (int constant, int j, int k, char axis)
{
    if ((constant >= -1 && constant <= 1) &&
        (j >= -1 && j <= 1) &&
        (k >= -1 && k <= 1))
    {
        switch (axis)
        {
        case 'x':
            return cubes[constant + 1][j + 1][k + 1];
        case 'y':
            return cubes[j + 1][constant + 1][k + 1];
        case 'z':
            return cubes[j + 1][k + 1][constant + 1];
        }
    }
    throw std::out_of_range("Indexation out of range");
}

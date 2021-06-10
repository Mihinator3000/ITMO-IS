#ifndef COMPONENTS_H
#define COMPONENTS_H

#define SIDE_LENGHT 3
#define SIDES_COUNT 6
#define ROTATIONS_COUNT 4

#include <iostream>
#include <vector>

class Cube
{
private:
    std::vector<char> sides;
    std::string inversion(std::string) const;
public:
    Cube();
    char& operator [] (const int);
    int sideToInt(const std::string) const;

    char& operator [] (const std::string);
    void rotation(std::string, bool);

    std::vector<char> getColors();
};

class Info
{
private:
    std::vector<std::vector<std::vector<Cube>>> cubes;
    void vector_init();
public:
    Info();
    Cube& operator () (int, int, int);
    Cube& operator () (int, int, int, char);
};

#endif // COMPONENTS_H

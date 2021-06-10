#ifndef CUBE_H
#define CUBE_H

#include "components.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>

class RotationAnimation
{
public:
    char axis;
    int value_axis;
    bool inv;
    std::string command;
    RotationAnimation() {axis = '0';};
    RotationAnimation(char a, int v, bool i, std::string c)
    {
        axis = a;
        value_axis = v;
        inv = i;
        command = c;
    }
};

extern std::vector<RotationAnimation> steps;

class RubiksCube
{
private:
    Info c;

    std::string colors_to_string(std::vector<char>&);
    bool color_opposite(char, char);

    void double_function(std::string, std::string);

    void cross_yellow_up();
    void cross_rotate_top(int, int);
    void cross_rotate_top();
    void cross_whites_up(int&);
    void cross();

    void pif_paf();
    std::vector<char> color_corner(int, int, int, char);
    bool colors_existence(std::vector<char>&, char, char);

    void first_layer_rotate_top();
    void first_later_rotate_top(char, char);
    void first_layer();

    void pif_paf_left();
    bool colors_existence(std::vector<char>&, char);

    void second_layer_rotate_top();
    void second_layer_rotate_top(char, char);
    void second_layer_edge_right();
    void second_layer_edge_left();
    void second_layer();

    void pif_paf_f();

    bool top_cross();

    void correct_edges();
    void correct_top_cross();

    void correct_cubes_create();
    int top_layer_correct_cubes_count();
    void top_layer_rotate();
    bool top_layer_correct_cubes();
    bool top_layer();

public:
    RubiksCube() {c = Info();}
    Cube& operator () (int, int, int);
    void load(std::string);
    void save(std::string);
    void print();

    void rotation_helper(char, int, bool);

    void rotation(std::string, bool);
    void rotation(std::string);
    void motion(std::string, bool);
    void motion(std::string);
    bool check_invariation();
    void generate_valid_cube();
    bool solve();
};

#endif // CUBE_H

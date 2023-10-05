#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Defines.hpp"
#include "src/rsdl.hpp"
#include "SpaceFighter.hpp"
#include <fstream>
#include <string>
#include <vector>

typedef struct Position
{
    int i;
    int j;
}Position;

class Map
{
public:
    void read_map(std::string map_address);
    void setup_map_items();
    void draw(Window* window, std::vector<Spacefighter> static_spacefighters,
                std::vector<Spacefighter> moving_spacefighters, Rectangle hostage);
    std::vector<Position> get_static_enemies(int round);
    std::vector<Position> get_moving_enemies(int round);
    Position get_hostage(int round);
    Position size();
    int get_rounds();
private:
    std::vector<std::vector<Position>> static_enemies;
    std::vector<std::vector<Position>> moving_enemies;
    std::vector<std::vector<Position>> hostage_spaceship;
    int row, column, rounds = 0;
};

#endif
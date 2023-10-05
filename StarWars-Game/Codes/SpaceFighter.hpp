#ifndef SPACEFIGHTER_H
#define SPACEFIGHTER_H

#include "src/rsdl.hpp"
#include "Defines.hpp"
#include <iostream>
#include <time.h>
#include "LaserBullet.hpp"
#include <vector>

bool is_two_rect_overlap(Rectangle rect1, Rectangle rect2);

class Spacefighter 
{
public:
    void handle_spacefighter_keypress(char pressed_key, Window* window);
    void handle_spacefighter_keyrelease(char released_key);
    void draw(Window* window, int mode);
    void update();
    void limit_in_max_speed();
    bool is_key_directional(char key);
    void init_enemy(int i, int j, int type, int rows, int columns);
    bool is_inside_screen(int direction);
    void update_spacefighters(int type);
    void shoot(int type);
    void draw_lasers(Window* window);
    void starting_loc(int column);
    void UI_shot(int not_to_shot);
    bool is_bullet_hit(Spacefighter opponent);
    bool is_bullet_hit(Rectangle rect);
    bool is_spacefighter_hit(Spacefighter opponent);
    Rectangle get_hitbox();
    void update_lasers();
private:
    int row;
    int column; 
    Rectangle body = Rectangle(100, 100, SPACESHIP_WIDTH, SPACESHIP_HEIGHT);
    double vx = 0;
    double vy = 0;
    char active_key = EMPTY;
    char previous_key = EMPTY;
    double increase_velocity_rate = 0;
    int direction;
    std::vector<Laser> lasers;
};

#endif
#ifndef LASER_H
#define LASER_H

#include "src/rsdl.hpp"
#include "Defines.hpp"

class Laser
{
public:
    Laser(Point shoot_point, int type);
    void draw(Window* window);
    void update();
    Rectangle hitbox();
    bool is_outside_map();
private:
    Rectangle bullet = Rectangle(0 ,0, 3, 50);
    int direction;
};



#endif
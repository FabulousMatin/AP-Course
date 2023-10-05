#include "LaserBullet.hpp"
using namespace std;

Laser::Laser(Point shoot_point, int type)
{
    if(type == PLAYER)
    {
        direction = UP;
        bullet.x = shoot_point.x + 45;
        bullet.y = shoot_point.y - 20;
    }
 
    else if(type == UI)
    {
        direction = DOWN;
        bullet.x = shoot_point.x + 35;
        bullet.y = shoot_point.y + 100;
    }
        
  
}

void Laser::draw(Window* window)
{
    if (direction == UP)
        window->fill_rect(bullet, RED);
    else if(direction == DOWN)
         window->draw_rect(bullet, GREEN);
}

void Laser::update()
{
    if (direction == UP)
        bullet.y -= ENEMY_SHOT_SPEED;
    else if(direction == DOWN)
         bullet.y += ENEMY_SHOT_SPEED;
    
}

Rectangle Laser::hitbox()
{
    return bullet;
}

bool Laser::is_outside_map()
{
    return (bullet.y < 0 || bullet.y > 1080);
}
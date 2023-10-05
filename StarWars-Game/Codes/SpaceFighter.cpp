#include "SpaceFighter.hpp"

using namespace std;

bool is_two_rect_overlap(Rectangle r1, Rectangle r2)
{
    return !(r1.x + r1.w < r2.x || r1.y + r1.h < r2.y 
            || r1.x > r2.x + r2.w || r1.y > r2.y + r2.h);
}

void Spacefighter::handle_spacefighter_keypress(char pressed_key, Window* window)
{
    if(is_key_directional(pressed_key))
    {
        active_key = pressed_key;
    }
    if(pressed_key == ' ')
    {
        shoot(PLAYER);
        window->play_sound_effect(LASER_BLASTER);
    }
       
}

void Spacefighter::handle_spacefighter_keyrelease(char released_key)
{
    if((released_key == 'w' && active_key != 's') 
        || (released_key == 's' && active_key != 'w'))
    {
        increase_velocity_rate = 0;
        active_key = EMPTY;
        vy = 0;
    }

    else if((released_key == 'a' && active_key != 'd')
           || (released_key == 'd' && active_key != 'a'))
    {
        increase_velocity_rate = 0;
        active_key = EMPTY;
        vx = 0;
    }
}

void Spacefighter::update()
{
    if(increase_velocity_rate < 5)
        increase_velocity_rate += 0.35;

    if(active_key == 'w')
	    vy -= increase_velocity_rate;
    else if(active_key == 'd')
	    vx += increase_velocity_rate;
    else if(active_key == 's')
	    vy += increase_velocity_rate;
    else if(active_key == 'a')
	    vx -= increase_velocity_rate;

    limit_in_max_speed();
    if(is_inside_screen(1))
    {
        body.x += vx;
    }
    if(is_inside_screen(2))
    {
        body.y += vy;
    }

   update_lasers();
        
}

void Spacefighter::update_lasers()
{
    for(int i = 0; i < lasers.size() ; i++)
    {
        lasers[i].update();
        if(lasers[i].is_outside_map())
            lasers.erase(lasers.begin() + i);
    }
}

void Spacefighter::update_spacefighters(int type)
{
    update_lasers();

    if(type == STATIC_SPACEFIGHTER)
    {
        
    }
    else if(type == DYNAMIC_SPACEFIGHTER)
    {
        if(direction == LEFT && body.x <= SPACEFIGHTER_SPEED)
            direction = RIGHT;
        if(direction == RIGHT && body.x >= 1820)
            direction = LEFT;
        if(direction == LEFT)
            body.x -= SPACEFIGHTER_SPEED;
        else if(direction == RIGHT)
            body.x += SPACEFIGHTER_SPEED;
    }
}

bool Spacefighter::is_inside_screen(int direction)
{
    if(direction == 1) 
        if(body.x + vx > 0 && body.x + vx < 1820)
            return true;
    if(direction == 2)
        if(body.y + vy > 0 && body.y + vy < 900)
            return true;
    return false;
}

void Spacefighter::draw(Window* window, int mode)
{
    if(mode == PLAYER_SPACEFIGHTER)
        window->draw_img(PLAYER_SPACEFIGHTER_IMG, body);
    else if(mode == DYNAMIC_SPACEFIGHTER)
        window->draw_img(DYNAMIC_SPACEFIGHTER_IMG, body);
    else if(mode == STATIC_SPACEFIGHTER)
        window->draw_img(STATIC_SPACEFIGHTER_IMG, body);
}

void Spacefighter::draw_lasers(Window* window)
{
    for(int i = 0; i < lasers.size() ; i++)
        lasers[i].draw(window);
}

void Spacefighter::limit_in_max_speed()
{
    if(vx > SPEED_LIMIT)
        vx = SPEED_LIMIT;
    else if(vx < -SPEED_LIMIT)
        vx = -SPEED_LIMIT;
    if(vy > SPEED_LIMIT)
        vy = SPEED_LIMIT;
    else if(vy < -SPEED_LIMIT)
        vy = -SPEED_LIMIT;
}

bool Spacefighter::is_key_directional(char key)
{
    return key == 'w' || key == 'd' || key == 's' || key == 'a';
}

void Spacefighter::init_enemy(int i, int j, int type, int rows, int columns)
{
    srand(time(0));
    direction = rand() % 2;
    if(type == STATIC_SPACEFIGHTER)
    {
        body.h = 130;
        body.w = 80;
    }
    else if(type == DYNAMIC_SPACEFIGHTER)
    {
        body.h = 90;
        body.w = 100;
    }
    row = i;
    column = j;
    body.y = i * (int)(600 / rows) + body.w / 2;
    body.x = j * (int)(1920 / columns) + body.h / 2;

}

void Spacefighter::UI_shot(int not_to_shot)
{

    if(column != not_to_shot)
    {
        shoot(UI);
    }
    
}

void Spacefighter::shoot(int type)
{
    if(type == PLAYER)
        lasers.push_back(Laser(Point(body.x, body.y), PLAYER));
    else if(type == UI)
        lasers.push_back(Laser(Point(body.x, body.y), UI));
}

void Spacefighter::starting_loc(int column)
{
    body.x = column;
    body.y = 900;
}

bool Spacefighter::is_bullet_hit(Spacefighter opponent)
{
    for(int i = 0 ; i < lasers.size() ; i++)
    {
        if(is_two_rect_overlap(lasers[i].hitbox(), opponent.body))
        {
            lasers.erase(lasers.begin() + i);
            return true;
        } 
            
    }
    return false;
}

bool Spacefighter::is_bullet_hit(Rectangle rect)
{
   for(int i = 0 ; i < lasers.size() ; i++)
    {
        if(is_two_rect_overlap(lasers[i].hitbox(), rect)) 
            return true;
    }
    return false;
}

bool Spacefighter::is_spacefighter_hit(Spacefighter opponent)
{
    return is_two_rect_overlap(body, opponent.body);
}

Rectangle Spacefighter::get_hitbox()
{
    return body;
}


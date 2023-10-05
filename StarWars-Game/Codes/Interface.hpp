#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "src/rsdl.hpp"
#include "Defines.hpp"

bool is_inside_rectangle(Point point ,Rectangle rectangle);

class Menu
{
public:
	void update();
	void draw(Window* window);
	void handle_menu_event(Window* window, Point mouse_position, int& game_status);
    void start_game(Window* window, int& game_status);
	void setup(Window* window, int& game_status);
private:
	Rectangle start_icon = Rectangle(Point(100, 100), Point(300,200));
};	


#endif
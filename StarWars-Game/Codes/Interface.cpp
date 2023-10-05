#include "Interface.hpp"

bool is_inside_rectangle(Point point ,Rectangle rectangle)
{
	return (point.x >= rectangle.x && point.x <= rectangle.x + rectangle.w ) &&
	 (point.y >= rectangle.y && point.y <= rectangle.y + rectangle.h); 
}

void Menu::draw(Window* window)
{
	window->draw_img(MENU_BACKGROUND);
	window->play_music(MAIN_THEME);
	window->draw_rect(start_icon);
	window->show_text("start", Point(180,130), WHITE, FONT, 24);
	window->update_screen();
}

void Menu::handle_menu_event(Window* window, Point mouse_position, int& game_status)
{
	if(is_inside_rectangle(mouse_position, start_icon))
	{
		start_game(window, game_status);
	}
}


void Menu::start_game(Window* window, int& game_status)
{
	game_status = BETWEEN_ROUNDS;
}

void Menu::setup(Window* window, int& game_status)
{
	draw(window);
	while(game_status == IN_MENU)
	{
		if(window->has_pending_event())
		{
			Event event = window->poll_for_event();
			switch(event.get_type())
			{
				case Event::EventType::QUIT:
					exit(0);
				break;
				case Event::EventType::LCLICK:
					handle_menu_event(window, event.get_mouse_position(), game_status);
				break;
			}	
		}
	}
	
}
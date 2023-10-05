#include "Game.hpp"

using namespace std;

void Game::run(string map_adress)
{
	map.read_map(map_adress);
    menu.setup(window, game_status);
	setup();
	while(game_status != LOSE && game_status != WIN)
	{
		handle_round();
		process_events();
		update_objects();
        draw_screen();
		delay(delay_time);
		check_next_round(window);
	}
	if(game_status == WIN)
		win(window);
	else if(game_status == LOSE)
		lose(window);
}


void Game::process_events() 
{
	while(window->has_pending_event()) 
	{
		Event event = window->poll_for_event();
		switch(event.get_type()) 
		{
			case Event::EventType::QUIT:
				exit(0);
			break;
			case Event::EventType::LCLICK:
				
			break; 
            case Event::EventType::KEY_PRESS:
                if(game_status == IN_GAME)
                {
                    spaceship.handle_spacefighter_keypress(event.get_pressed_key(), window);
                }
            break;
			case Event::EventType::KEY_RELEASE:
				if(game_status == IN_GAME)
				{
					spaceship.handle_spacefighter_keyrelease(event.get_pressed_key());
				}
			break;
		}
	}
}

void Game::setup()
{
	srand(time(0));
	not_to_shot = rand() % map.size().j;
	spaceship.starting_loc(not_to_shot * (int)(1920 / map.size().j));
}

void Game::update_objects()
{
	spaceship.update();
	update_enemies();
	shoot_logic();
	check_all_objects();
}

void Game::draw_screen()
{
	window->clear();
	map.draw(window, static_spacefighters, moving_spacefighters, hostage);
	spaceship.draw(window, PLAYER_SPACEFIGHTER);
	spaceship.draw_lasers(window);
	enemies_drawlasers();
	window->update_screen();

}

void Game::arrange_enemies(std::vector<Position> static_enemies,std::vector<Position> moving_enemies,
																		Position hostage_spaceship)
{
	static_spacefighters.clear();
	moving_spacefighters.clear();

	for(int i = 0; i < static_enemies.size(); i++)
	{
		Spacefighter enemy;
		enemy.init_enemy(static_enemies[i].i, static_enemies[i].j, STATIC_SPACEFIGHTER, map.size().i, map.size().j);
		static_spacefighters.push_back(enemy);
	}
	for(int i = 0; i < moving_enemies.size(); i++)
	{
		Spacefighter enemy;
		enemy.init_enemy(moving_enemies[i].i, moving_enemies[i].j, DYNAMIC_SPACEFIGHTER, map.size().i, map.size().j);
		moving_spacefighters.push_back(enemy);
	}

	hostage.x = hostage_spaceship.i;
	hostage.y = hostage_spaceship.j;
	hostage.h = 120;
	hostage.w = 120;

}

void Game::update_enemies()
{
	for(int i = 0 ; i < static_spacefighters.size() ; i++)
	{
		static_spacefighters[i].update_spacefighters(STATIC_SPACEFIGHTER);
	}
	for(int i = 0 ; i < moving_spacefighters.size() ; i++)
	{
		moving_spacefighters[i].update_spacefighters(DYNAMIC_SPACEFIGHTER);
	}
}

void Game::shoot_logic()
{
	srand(time(0));
	shot_turn++;
	if(shot_turn == 100)
	{
		shot_turn = 0;
		
		for(int i = 0 ; i < static_spacefighters.size() ; i++)
		{
			static_spacefighters[i].UI_shot(not_to_shot);
		}
		for(int i = 0 ; i < moving_spacefighters.size() ; i++)
		{
			moving_spacefighters[i].UI_shot(not_to_shot);
		}

		int next_col_prob = rand() % 2;
		if(next_col_prob == 0)
    	{
        	not_to_shot++;
        	if(not_to_shot == map.size().j + 1)
           	 not_to_shot -= 2 ;
    	}
    	else
    	{
        	not_to_shot--;
        	if(not_to_shot == -1)
           		not_to_shot += 2 ;
    	}
	}
}

void Game::enemies_drawlasers()
{
	for(int i = 0 ; i < static_spacefighters.size() ; i++)
	{
		static_spacefighters[i].draw_lasers(window);
	}
	for(int i = 0 ; i < moving_spacefighters.size() ; i++)
	{
		moving_spacefighters[i].draw_lasers(window);
	}
}

void Game::check_all_objects()
{
	check_player_shots();
	check_enemy_shots();
	check_two_spaceship_meet();
	check_hostage();
}
void Game::check_enemy_shots()
{
	for(int i = 0 ; i < static_spacefighters.size() ; i++)
	{
		if(static_spacefighters[i].is_bullet_hit(spaceship))
		{
			game_status = LOSE;
			window->play_sound_effect(EXPLOSION);
		}
	}
	for(int i = 0 ; i < moving_spacefighters.size() ; i++)
	{
		if(moving_spacefighters[i].is_bullet_hit(spaceship))
		{
			game_status = LOSE;
			window->play_sound_effect(EXPLOSION);
		}
	}
}

void Game::check_player_shots()
{
	for(int i = 0 ; i < static_spacefighters.size() ; i++)
	{
		if(spaceship.is_bullet_hit(static_spacefighters[i]))
		{
			static_spacefighters.erase(static_spacefighters.begin() + i);
			window->play_sound_effect(EXPLOSION);
		}
	}

	for(int i = 0 ; i < moving_spacefighters.size() ; i++)
	{
		if(spaceship.is_bullet_hit(moving_spacefighters[i]))
		{
			moving_spacefighters.erase(moving_spacefighters.begin() + i);
			window->play_sound_effect(EXPLOSION);
		}
	}
}

void Game::check_two_spaceship_meet()
{
	for(int i = 0 ; i < static_spacefighters.size() ; i++)
	{
		if(spaceship.is_spacefighter_hit(static_spacefighters[i]))
		{
			static_spacefighters.erase(static_spacefighters.begin() + i);
			window->play_sound_effect(EXPLOSION);
			game_status = LOSE;
		}
	}
	for(int i = 0 ; i < moving_spacefighters.size() ; i++)
	{
		if(spaceship.is_spacefighter_hit(moving_spacefighters[i]))
		{
			moving_spacefighters.erase(moving_spacefighters.begin() + i);
			window->play_sound_effect(EXPLOSION);
			game_status = LOSE;
		}
	}
}

bool Game::is_round_finished()
{
	return(static_spacefighters.empty() && moving_spacefighters.empty());
}

void Game::check_next_round(Window* window)
{
	if(is_round_finished() && round != map.get_rounds())
	{
		window->draw_img(NEXTROUND, Rectangle(Point(690,360), Point(1250, 720)));
		window->update_screen();
		delay(2000);
		game_status = BETWEEN_ROUNDS;
		round++;
		setup();
		reset_hostage();
	}
	else if(is_round_finished() && round == map.get_rounds())
		game_status = WIN;
	
}

void Game::handle_round()
{
	if(game_status == BETWEEN_ROUNDS)
	{
		if(round > map.get_rounds())
		{
			game_status = WIN;
		}
		else
		{
			arrange_enemies(map.get_static_enemies(round),
						 map.get_moving_enemies(round), map.get_hostage(round));

			game_status = IN_GAME;
		}
	
	}
}

void Game::lose(Window* window)
{
	window->draw_img(GAMEOVER, Rectangle(Point(690,360), Point(1250, 720)));
	window->update_screen();
	delay(2000);
}

void Game::win(Window* window)
{
	window->draw_img(VICTORY, Rectangle(Point(690,360), Point(1250, 720)));
	window->update_screen();
	delay(2000);
}

void Game::check_hostage()
{
	if(is_two_rect_overlap(spaceship.get_hitbox(), hostage))
	{
		game_status = LOSE;
		window->play_sound_effect(EXPLOSION);
	}
		
	if(spaceship.is_bullet_hit(hostage))
	{
		game_status = LOSE;
		window->play_sound_effect(EXPLOSION);
	}
}

void Game::reset_hostage()
{
	hostage.x = -1;
	hostage.y = -1;
	hostage.w = 0;
	hostage.h = 0;
}
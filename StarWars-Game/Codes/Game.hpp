#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "src/rsdl.hpp"
#include "Defines.hpp"
#include "Interface.hpp"
#include "SpaceFighter.hpp"
#include "Map.hpp"

class Game
{
public:
	void setup();
	void update_objects();
    void draw_screen();
    void run(std::string map_adress);
    void process_events();
    void arrange_enemies(std::vector<Position> static_enemies,std::vector<Position> moving_enemies,
                        Position hostage_spaceship);

    void update_enemies();
    void shoot_logic();
    void enemies_drawlasers();

    void check_all_objects();
    void check_player_shots();
    void check_enemy_shots();
    void check_two_spaceship_meet();
    bool is_round_finished();
    void check_next_round(Window* window);
    void check_hostage();
    void handle_round();
    void lose(Window* window);
    void win(Window* window);
    void reset_hostage();
private:
	Menu menu;
	int game_status = IN_MENU;
    Window* window = new Window(1920, 1080, "Star Wars");
    Spacefighter spaceship;
    std::vector<Spacefighter> static_spacefighters;
    std::vector<Spacefighter> moving_spacefighters;
    Rectangle hostage = Rectangle(-1, -1, 0, 0);
    Map map;
    int round = 1;
    int shot_turn = 41;
    int delay_time = 20;
    int not_to_shot = 0;
};

#endif
#include "Map.hpp"

using namespace std;

void Map::read_map(string map_address)
{
	ifstream map_file;
	map_file.open(map_address);
	string line;
	map_file >> row >> column >> rounds ;
    setup_map_items();

	for(int n = 0 ; n < rounds ; n++)
	{
		for(int i = 0 ; i < row ; i++)
		{
			map_file >> line;
			for(int j = 0 ; j < column ; j++)
            {
                if(line[j] == 'S')
			    {
                    static_enemies[n].push_back(Position({i, j}));
			    }
			    else if(line[j] == 'M')
			    {
                    moving_enemies[n].push_back(Position({i, j}));
			    }
			    else if(line[j] == 'H')
			    {   
				    hostage_spaceship[n].push_back(Position({j * (int)(1920 / column), i * (int)(600 / row)}));
			    }
            }
		}
        map_file >> line;
	}
}
void Map::setup_map_items()
{
    static_enemies.resize(rounds);
    moving_enemies.resize(rounds);
    hostage_spaceship.resize(rounds);
}

void Map::draw(Window* window, vector<Spacefighter> static_spacefighters,
                vector<Spacefighter> moving_spacefighters, Rectangle hostage)
{   
	window->draw_img(GAME_BACKGROUND);
	for(int i = 0 ; i < static_spacefighters.size() ; i++)
	{
		static_spacefighters[i].draw(window, STATIC_SPACEFIGHTER);
	}
	for(int i = 0 ; i < moving_spacefighters.size() ; i++)
	{
		moving_spacefighters[i].draw(window, DYNAMIC_SPACEFIGHTER);
	}

	if(hostage.x != -1)
		window->draw_img(HOSTAGE_IMG, hostage);

}

vector<Position> Map::get_static_enemies(int round)
{
    return static_enemies[round - 1];
}
vector<Position> Map::get_moving_enemies(int round)
{
    return moving_enemies[round - 1];
}
Position Map::get_hostage(int round)
{
	if (hostage_spaceship[round - 1].size() == 1)
    	return hostage_spaceship[round - 1][0];
	else
		return Position({-1,-1});
}

Position Map::size()
{
	return Position({row, column});
}

int Map::get_rounds()
{
	return rounds;
}
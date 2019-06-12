#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"



int main()
{
	Game game;
	game.SetUp();

	while(game.UpdateGame())
	{ }
	
	std::cout << "Thanks for playing" << std::endl;

	return 0;
}
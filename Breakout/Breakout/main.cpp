#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

#include <stdlib.h>
#include <time.h>



int main()
{

	srand(time(NULL));

	Game* game = new Game();

	sf::Font font;
	std:string font_name = "pixelmix.ttf";

	try
	{
		font.loadFromFile("Fonts/" + font_name);
	}
	catch (...)
	{
		std::cout << "ERROR 1: FONT (" << font_name << ") NOT FOUND" << std::endl;
	}

	sf::Text breakout;
	breakout.setFont(font);
	breakout.setString("BREAKOUT (ish)");
	breakout.setCharacterSize(30);
	float x_pos = (WIDTH - breakout.getLocalBounds().width) * 0.5f;
	float y_pos = (HEIGHT - breakout.getLocalBounds().height) * 0.33f;
	breakout.setPosition(sf::Vector2f(x_pos, y_pos));

	sf::Text enter;
	enter.setFont(font);
	enter.setString("PRESS ENTER TO PLAY");
	enter.setCharacterSize(30);
	x_pos = (WIDTH - enter.getLocalBounds().width) * 0.5f;
	y_pos = (HEIGHT - enter.getLocalBounds().height) * 0.66f;
	enter.setPosition(sf::Vector2f(x_pos, y_pos));

	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Ninja Kiwi Code Test - Breakout(ish)");

	bool playing = false;


	while(window->isOpen())
	{ 
		sf::Event event;
		while (window->pollEvent(event))
		{
			// Checks if the game window has been closed
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}
		
		if (playing)
		{
			if (!game->UpdateGame(window))
			{
				playing = false;
			}
		}
		else
		{
			
			window->clear();
			window->draw(breakout); 
			window->draw(enter);
			window->display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				delete game;
				game = new Game();
				game->SetUp();
				playing = true;
			}
		}
	}
	
	std::cout << "Thanks for playing" << std::endl;

	return 0;
}
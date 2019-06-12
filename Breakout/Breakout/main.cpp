#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"



int main()
{
	Game game;
	game.SetUp();

	sf::Texture main_menu_tex;
	main_menu_tex.loadFromFile("Textures/main_menu.png");

	sf::Sprite sprite;
	sprite.setTexture(main_menu_tex);

	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Ninja Kiwi Code Test - Breakout(ish)");

	window->draw(sprite); window->display();

	int num = 0;
	cin >> num;

	/*while(game.UpdateGame())
	{ }*/
	
	std::cout << "Thanks for playing" << std::endl;

	return 0;
}
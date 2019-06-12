#include "UI.h"

UI::UI()
{

}

void UI::Init(float width, float height, int starting_score, int starting_lives)
{
	
	border_width = 10.0f;
	text_region = 100.0f;

	walls[0] = new GameObject();
	walls[0]->Init
	(
		sf::Vector2f(border_width * 0.5f, height * 0.5f),
		sf::Vector2f(border_width, height),
		sf::Color(255, 255, 255)
	);

	walls[1] = new GameObject();
	walls[1]->Init
	(
		sf::Vector2f(width - (border_width * 0.5f), height * 0.5f),
		sf::Vector2f(border_width, height),
		sf::Color(255, 255, 255)
	);

	walls[2] = new GameObject();
	walls[2]->Init
	(
		sf::Vector2f(width * 0.5f, text_region),
		sf::Vector2f(width, border_width),
		sf::Color(255, 255, 255)
	);

	walls[3] = new GameObject();
	walls[3]->Init
	(
		sf::Vector2f(width * 0.5f, border_width * 0.5f),
		sf::Vector2f(width, border_width),
		sf::Color(255, 255, 255)
	);

;
	std:string font_name = "pixelmix.ttf";

	try
	{
		font.loadFromFile(font_name);
	}
	catch (...)
	{
		std::cout << "ERROR 1: FONT (" << font_name << ") NOT FOUND" << std::endl;
	}

	font_size = 30.0f;

	score.setFont(font);
	score.setString("Score: " + std::to_string(starting_score));
	score.setPosition(sf::Vector2f(border_width + 20.0f, (text_region * 0.5f) - 0.5f * font_size));
	score.setCharacterSize(30);

	lives.setFont(font);
	lives.setString("Lives: " + std::to_string(starting_lives));
	lives.setPosition(sf::Vector2f(width * 0.5f + 20.0f, (text_region * 0.5f) - 0.5f * font_size));
	lives.setCharacterSize(30);
}

UI::~UI()
{
	for (int i = 0; i < 4; i++)
	{
		delete walls[i];
		walls[i] = NULL;
	}

}

void UI::UpdateScore(int score)
{
	
	this->score.setString("Score: " + std::to_string(score));
}

void UI::UpdateLives(int lives)
{
	this->lives.setString("Lives: " + std::to_string(lives));
}

void UI::Render(sf::RenderWindow* window)
{	
	for (int i = 0; i < 4; i++)
	{
		window->draw(*walls[i]->body);
	}

	window->draw(score);
	window->draw(lives);
}

void UI::ActivateScoreMult()
{
	score.setFillColor(sf::Color(255, 255, 0));
}
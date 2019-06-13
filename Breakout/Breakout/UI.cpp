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
		font.loadFromFile("Fonts/" + font_name);
	}
	catch (...)
	{
		std::cout << "ERROR 1: FONT (" << font_name << ") NOT FOUND" << std::endl;
		std::cin >> font_name;
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

	this->width = width;
	this->height = height;

	end = false;
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

	if (end)
	{
		window->draw(score_calculation);
		window->draw(score_final);
		window->display();

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

void UI::ActivateScoreMult(sf::Color colour)
{
	score.setFillColor(colour);
}

void UI::End(int score, int lives)
{
	if (lives < 0)
	{
		lives = 0;
	}

	score_calculation.setFont(font);
	score_calculation.setString("Final Score = \n" + std::to_string(score) + " + 50 x " + std::to_string(lives));
	score_calculation.setCharacterSize(30);

	
	float x_pos = (width - score_calculation.getLocalBounds().width) * 0.5f;
	float y_pos = (height - score_calculation.getLocalBounds().height) * 0.5f;
	score_calculation.setPosition(sf::Vector2f(x_pos, y_pos - score_calculation.getCharacterSize() * 0.75f));
	
	score_calculation.setOutlineColor(sf::Color(0, 0, 0));
	score_calculation.setOutlineThickness(2.0f);

	score_final.setFont(font);
	score_final.setString(std::to_string(score + 50 * lives));
	score_final.setCharacterSize(30);

	x_pos = (width - score_final.getLocalBounds().width) * 0.5f;
	y_pos = (height - score_final.getLocalBounds().height) * 0.5f;
	score_final.setPosition(sf::Vector2f(x_pos, y_pos + score_calculation.getCharacterSize()));

	score_final.setFillColor(sf::Color(255, 255, 0));
	score_final.setOutlineColor(sf::Color(0, 0, 0));
	score_final.setOutlineThickness(2.0f);

	end = true;
}
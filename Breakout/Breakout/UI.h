#include "GameObject.h"
#include <chrono>
#include <thread>

#pragma once
class UI
{
public:
	UI();
	~UI();

	void Init(float width, float height, int starting_score, int starting_lives);
	void Render(sf::RenderWindow* window);

	void UpdateScore(int score);
	void UpdateLives(int lives);
	
	void ActivateScoreMult(sf::Color colour);

	void End(int score, int lives);

	GameObject* walls[4];
	float border_width;
	float text_region;

private:
	sf::Font font;
	sf::Text score;
	sf::Text lives;

	sf::Text score_calculation;
	sf::Text score_final;

	float font_size;

	int width;
	int height;

	bool end;
};


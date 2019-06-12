#include "GameObject.h"

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
	
	void ActivateScoreMult();

	GameObject* walls[4];
	float border_width;
	float text_region;

private:
	sf::Font font;
	sf::Text score;
	sf::Text lives;

	float font_size;
};


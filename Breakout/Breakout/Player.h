#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Color colour, float speed, int screen_width, int starting_lives);
	~Player();

	void Update(sf::RenderWindow* window, float delta_time);
	void Move(int direction, float delta_time);

	void ActivateScoreMult(int mult);
	void ActivateLengthChange(float length);

	int GetScore();
	int GetLives();

	void SetScore(int score);
	void Setlives(int lives);

	void UpdateScore(int points);
	void Dead();

private:

	float starting_length;
	float max_length;
	float speed;
	int screen_width;
	int score;
	int score_mult;
	int lives;
};


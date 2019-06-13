#pragma once
#include <stdlib.h>

#include "GameObject.h"
class Ball : public GameObject
{
public:
	Ball();
	Ball(sf::Vector2f pos, sf::Vector2f size, sf::Color colour, float speed, int width, int height, float speed_increase_rate);
	~Ball();

	void Reset();
	void Update(sf::RenderWindow* window, float delta_time);
	void Move(float delta_time);
	void X_Bounce();
	void Y_Bounce();

	void CalculateNewAngle();

	void ChangeSpeed(float speed_increase);

	GameObject* last_collision;
	sf::Vector2f previous_position;

private:
	int screen_width;
	int screen_height;

	float x_speed;
	float y_speed;
	float angle;
	float speed_increase;
	float starting_speed;
	sf::Vector2i direction;

	sf::Vector2f starting_pos;


	float speed_increase_rate;
	float speed_boost;


};


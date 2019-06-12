#include "Ball.h"



Ball::Ball()
{
	speed = 1.0f;
	screen_width = 0;
	screen_height = 0;

	direction.x = 1;
	direction.y = 1;

	previous_position = sf::Vector2f(0.0f, 0.0f);

	starting_speed = speed;
}
 
Ball::Ball(sf::Vector2f pos, sf::Vector2f size, sf::Color colour, float speed, int width, int height, float speed_increase_rate)
{
	GameObject::Init(pos, size, colour);
	this->speed = speed;
	this->speed_increase_rate = speed_increase_rate;
	starting_speed = speed;
	speed_increase = 0.0f;

	screen_width = width;
	screen_height = height;

	previous_position = pos;
	starting_pos = pos;

	direction.x = 1;
	direction.y = -1;

	last_collision = NULL;
}

Ball::~Ball()
{
}

void Ball::Reset()
{
	body->setPosition(starting_pos);
	//body->setFillColor(sf::Color());
	direction.x = 1;
	direction.y = -1;
	speed = start_speed;

	active = true;

	last_collision = NULL;

	std::cout << "RESET" << std::endl;
}

void Ball::Update(sf::RenderWindow* window, float delta_time)
{
	if (active)
	{
		Move(delta_time);

		speed_increase += speed_increase_rate * delta_time;

		if (speed > starting_speed)
		{
			speed -= 50.0f * delta_time;
		}

		GameObject::Update(window);
	}
}

void Ball::Move(float delta_time)
{
	sf::Vector2f pos = body->getPosition();

	previous_position = pos;

	pos.x += (speed + speed_increase) * direction.x * delta_time;
	pos.y += (speed + speed_increase) * direction.y * delta_time;

	body->setPosition(pos);
}

void Ball::ChangeSpeed(float speed_increase)
{
	speed += speed_increase;
}

void Ball::X_Bounce()
{
	direction.x *= -1;	
}

void Ball::Y_Bounce()
{
	direction.y *= -1;
}
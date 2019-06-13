#include "Ball.h"



Ball::Ball()
{
	x_speed = 0;
	y_speed = 0; 
	screen_width = 0;
	screen_height = 0;

	direction.x = 1;
	direction.y = 1;

	previous_position = sf::Vector2f(0.0f, 0.0f);

	starting_speed = x_speed;
}
 
Ball::Ball(sf::Vector2f pos, sf::Vector2f size, sf::Color colour, float speed, int width, int height, float speed_increase_rate)
{
	GameObject::Init(pos, size, colour);
	this->x_speed = speed;
	this->y_speed = speed;
	angle = 45.0f;
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

	speed_boost = 0.0f;
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
	x_speed = starting_speed;
	y_speed = starting_speed;

	speed_boost = 0.0f;
	speed_increase = 0.0f;

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

		if (speed_boost > 0.0f)
		{
			speed_boost -= 50.0f * delta_time;
		}

		GameObject::Update(window);
	}
}

void Ball::Move(float delta_time)
{
	sf::Vector2f pos = body->getPosition();

	previous_position = pos;

	pos.x += (x_speed + speed_increase + speed_boost) * direction.x * delta_time;
	pos.y += (y_speed + speed_increase + speed_boost) * direction.y * delta_time;

	body->setPosition(pos);
}

void Ball::ChangeSpeed(float speed_increase)
{
	speed_boost += speed_increase;
}

void Ball::X_Bounce()
{
	direction.x *= -1;	
}

void Ball::Y_Bounce()
{
	direction.y *= -1;
}

void Ball::CalculateNewAngle()
{
	float current_speed = sqrtf(x_speed * x_speed + y_speed * y_speed);
	
	angle = rand() % 70 + 10.0f;

	cout << angle << endl;

	x_speed = current_speed * cosf(angle * (3.14159265/180.0f));

	y_speed = current_speed * sinf(angle * (3.14159265 / 180.0f));
}

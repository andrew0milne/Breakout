#include "Player.h"



Player::Player()
{
	speed = 1.0f;
	screen_width = 1;
	score_mult = 1;
}

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Color colour, float speed, int width, int starting_lives)
{
	GameObject::Init(pos, size, colour);
	this->speed = speed;
	screen_width = width;
	lives = starting_lives;
	score = 0;
	score_mult = 1;
}

Player::~Player()
{
}

void Player::Update(sf::RenderWindow* window, float delta_time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		Move(-1, delta_time);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		Move(1, delta_time);
	}

	GameObject::Update(window);
}

void Player::Move(int direction, float delta_time)
{
	sf::Vector2f pos = body->getPosition();

	float new_x_pos = pos.x + (speed * direction * delta_time);
	
	if ((new_x_pos < (screen_width - body->getSize().x/2.0f) && direction > 0) || (new_x_pos > body->getSize().x / 2.0f && direction < 0))
	{
		pos.x = new_x_pos;
	}

	body->setPosition(pos);
}

void Player::ActivateScoreMult(int mult)
{
	score_mult = mult;
}

int Player::GetScore()
{
	return score;
}

int Player::GetLives()
{
	return lives;
}

void Player::SetScore(int score)
{
	this->score = score;
}

void Player::Setlives(int lives)
{
	this->lives = lives;
}

void Player::UpdateScore(int points)
{
	score += points * score_mult;
}

void Player::Dead()
{
	lives--;
}
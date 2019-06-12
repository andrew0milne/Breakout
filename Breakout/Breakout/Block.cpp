#include "Block.h"



Block::Block()
{
	health = 0;
}

Block::~Block()
{
}

void Block::Init(sf::Vector2f pos, sf::Vector2f size, int health)
{	
	this->health = health;

	size.x -= 2.0f;
	size.y -= 2.0f;

	

	GameObject::Init(pos, size, GetColour());
}

sf::Color Block::GetColour()
{
	switch (health)
	{
	case 1:
	{
		return sf::Color(255, 255, 0);
	}
	case 2:
	{
		return sf::Color(255, 160, 0);
	}
	case 3:
	{
		return sf::Color(255, 0, 0);
	}
	case 4:
	{
		return sf::Color(255, 0, 160);
	}
	case 5:
	{
		return sf::Color(255, 0, 255);
	}
	case 6:
	{
		return sf::Color(160, 0, 255);
	}
	case 7:
	{
		return sf::Color(0, 0, 255);
	}
	case 8:
	{
		return sf::Color(0, 160, 255);
	}
	case 9:
	{
		return sf::Color(0, 255, 255);
	}
	default:
		return sf::Color(255, 255, 0);
		break;
	}
}

void Block::Disable()
{
	active = false;
	visible = false;
}


#pragma once
#include "GameObject.h"


class Block : public GameObject
{
public:
	Block();
	~Block();
	void Init(sf::Vector2f pos, sf::Vector2f size, int health);
	void Disable();

	
	sf::Color GetColour();

	int health;


};


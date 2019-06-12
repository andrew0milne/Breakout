#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init(sf::Vector2f pos, sf::Vector2f size, sf::Color colour);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	virtual void Hit() {}
	

	sf::RectangleShape* body;

	
	sf::Color colour;

	bool active;
	bool visible;

};


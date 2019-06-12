#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	sf::Vector2f default_size(10.0f, 10.0f);
	sf::Vector2f default_position(0.0f, 0.0f);
	sf::Color default_colour(255, 255, 255);

	Init(default_position, default_size, default_colour);

	active = true;
	visible = true;
}

GameObject::~GameObject()
{
	delete body;
	body = NULL;
}

void GameObject::Update(sf::RenderWindow* window)
{
	
}

void GameObject::Init(sf::Vector2f pos, sf::Vector2f size, sf::Color colour)
{
	body = new sf::RectangleShape;
	
	body->setOrigin(size / 2.0f);
	body->setSize(size);
	body->setPosition(pos);
	body->setFillColor(colour);
	
}


void GameObject::Render(sf::RenderWindow* window)
{
	if (visible)
	{
		window->draw(*body);
	}

}


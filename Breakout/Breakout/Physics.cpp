#include "Physics.h"


Physics::Physics()
{
}


Physics::~Physics()
{
}

bool Physics::BoxToBoxCollision(GameObject* go_a, GameObject* go_b)
{
	sf::RectangleShape* a = go_a->body;
	sf::RectangleShape* b = go_b->body;

	return (abs(a->getPosition().x - b->getPosition().x) * 2 < (a->getSize().x + b->getSize().x)) &&
		(abs(a->getPosition().y - b->getPosition().y) * 2 < (a->getSize().y + b->getSize().y));
}

bool Physics::IsAbove(GameObject* go_a, Ball* ball)
{
	sf::RectangleShape* a_body = go_a->body;
	sf::RectangleShape* ball_body = ball->body;

	
	if (a_body->getPosition().x + (a_body->getSize().x / 2.0f) <=  ball->previous_position.x - (ball_body->getSize().x /2.0f) ||
		ball->previous_position.x + (ball_body->getSize().x/2.0f)  <= a_body->getPosition().x - (a_body->getSize().x / 2.0f))
	{
		return false;
	}

	return true;
}

bool Physics::BallCollision(GameObject* go_a, Ball* ball)
{
	if (BoxToBoxCollision(go_a, ball) && ball->last_collision != go_a)
	{
		ball->last_collision = go_a;
		if (IsAbove(go_a, ball))
		{
			ball->Y_Bounce();
		}
		else
		{
			ball->X_Bounce();
		}

		go_a->Hit();

		return true;
	}

	return false;
}
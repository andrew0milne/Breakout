#pragma once
#include "GameObject.h"
#include "Ball.h"

class Physics
{
public:
	Physics();
	~Physics();

	bool BoxToBoxCollision(GameObject* go_a, GameObject* go_b);
	bool IsAbove(GameObject* go_a, Ball* ball);
	bool BallCollision(GameObject* go_a, Ball* ball);

};


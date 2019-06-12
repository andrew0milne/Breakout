#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <chrono>

#include "GameObject.h"
#include "Player.h"
#include "Ball.h"
#include "MapReader.h"
#include "Block.h"
#include "UI.h"

#include "Physics.h"

#pragma once

#define WIDTH 500
#define HEIGHT 600
#define BLOCK_REGION 300

class Game
{
public:
	Game();
	~Game();
	void SetUp();
	bool UpdateGame();
	void Update();
	void CheckCollisions(Ball* current_ball);
	void Render();
	void CalculateDeltaTime();

	void CheckBlocks(Block* block, Ball* b);

	void ScoreMult(int mult);
	void BallSpeedIncrease(float speed_increase);
	void Explosion(int new_ball_amount, Ball* b);

	sf::RenderWindow* window;

	Player* player;
	Ball* ball;
	std::list<Ball*> other_balls;
	MapReader map_reader;

	std::vector<Block*> blocks;

	Physics* physics;
	UI ui;

private:

	int block_width = 50;
	int block_height = 10;

	float delta_time;
	std::chrono::steady_clock::time_point current_time;
	std::chrono::steady_clock::time_point previous_time;
};


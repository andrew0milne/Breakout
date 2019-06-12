#include "Game.h"



Game::Game()
{
	
}

Game::~Game()
{
	delete player;
	player = NULL;

	delete ball;
	ball = NULL;

	/*for (int i = 0; i < balls.size(); i++)
	{
		delete balls[i];
		balls[i] = NULL;
	}*/

	
	for (int i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
		blocks[i] = NULL;
	}

	delete window;
	window = NULL;

	delete physics;
	physics = NULL;
}

// Sets up the various objects in the game
void Game::SetUp()
{
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Ninja Kiwi Code Test - Breakout(ish)");
	
	physics = new Physics();

	//Creates the Player
	player = new Player
	(
		sf::Vector2f(WIDTH/2.0f, HEIGHT - 50.0f),	// Position
		sf::Vector2f(100.0f, 10.0f),				// Size
		sf::Color(0.0f, 0.0f, 255.0f),				// Colour
		500.0f,										// Speed
		WIDTH,										// Screen bounds
		3											// Starting lives
	);

	ui.Init(WIDTH, HEIGHT, 0, player->GetLives());

	// Creates the Ball
	ball = new Ball
	(
		sf::Vector2f(WIDTH/2.0f, BLOCK_REGION + 50.0f),	// Position
		sf::Vector2f(10.0f, 10.0f),						// Size
		sf::Color(255, 255, 255),					// Colour 
		100.0f,											// Speed
		WIDTH, HEIGHT,									// Screen bounds
		5.0f											// Speed increase rate
	);									

	// Reads in the block data
	std::vector<BlockInfo> block_info;
	block_info = map_reader.ReadInMap("Map");

	block_width = (WIDTH - (2.0f * ui.border_width) - 3.0f) / map_reader.GetMaxColumns();
	block_height = (BLOCK_REGION - ui.text_region) / map_reader.GetMaxRows();

	// Creates the blocks
	for (int i = 0; i < block_info.size(); i++)
	{
		Block* temp_block = new Block;

		// Calculates the current block's position
		sf::Vector2f temp_pos;
		temp_pos = sf::Vector2f
		(
			block_info[i].pos.x * block_width + (block_width * 0.5f) + ui.border_width + 3.0f,						// X position
			block_info[i].pos.y * block_height + (block_height * 0.5f) + ui.text_region + ui.border_width	// Y Position
		);

		// Creates the current block
		temp_block->Init
		(
			temp_pos,									// Position
			sf::Vector2f(block_width, block_height),	// Size
			block_info[i].block_num						// Block Health
		);

		// Adds block the vector
		blocks.push_back(temp_block);
	}

	
	delta_time = 0.0f;
	current_time = std::chrono::high_resolution_clock::now();
	previous_time = std::chrono::high_resolution_clock::now();
}

// Updates the game
bool Game::UpdateGame()
{
	if (window->isOpen())
	{
		CalculateDeltaTime();
		Update();
		Render();

		return true;
	}
	else
	{
		return false;
	}
}

void Game::CalculateDeltaTime()
{
	previous_time = current_time;
	current_time = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> time;	

	time = current_time - previous_time;

	delta_time = time.count();
}

// Updates the various game objects
void Game::Update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		// Checks if the game window has been closed
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
	
	player->Update(window, delta_time);

	ball->Update(window, delta_time);
	if (ball->previous_position.y >= HEIGHT)
	{		
		player->Dead();
		ui.UpdateLives(player->GetLives());
		ball->Reset();		
	}

	for (Ball* const& i : other_balls)
	{
		i->Update(window, delta_time);
		if (i->previous_position.y >= HEIGHT)
		{
			i->active = false;
			i->visible = false;
		}
	}

	//for (int i = 0; i < balls.size(); i++)
	//{
	//	balls[i]->Update(window, delta_time);

	//	if (balls[i]->previous_position.y >= HEIGHT)
	//	{
	//		
	//		//kill ball
	//	}
	//}

	CheckCollisions(ball);
	for (Ball* const& b : other_balls)
	{
		CheckCollisions(b);
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Update(window);		
	}


}

void Game::CheckCollisions(Ball* current_ball)
{
	physics->BallCollision(player, current_ball);

	for (int i = 0; i < 3; i++)
	{
		physics->BallCollision(ui.walls[i], current_ball);
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->active && current_ball->active)
		{
			if (physics->BallCollision(blocks[i], current_ball))
			{
				player->UpdateScore(1);
				ui.UpdateScore(player->GetScore());

				if (current_ball == ball)
				{
					ball->body->setFillColor(blocks[i]->body->getFillColor());
				}

				CheckBlocks(blocks[i], current_ball);
			}
		}
	}
}

// Renders the game objects
void Game::Render()
{
	window->clear();
	
	player->Render(window);

	for (Ball* const& i : other_balls)
	{
		i->Render(window);
	}

	ball->Render(window);

	ui.Render(window);

	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Render(window);
	}

	window->display();
}

void Game::CheckBlocks(Block* block, Ball* b)
{
	
	switch (block->health)
	{
		// Normal Blocks
	case 1:
	case 2:
	case 3:
	{
		block->health--;
		if (block->health <= 0)
		{
			block->Disable();
		}
		else
		{
			block->body->setFillColor(block->GetColour());
		}
		break;
	}
	// Ball Explosion
	case 4:
	{
		block->Disable();
		Explosion(2, b);
		break;
	}
	// Ball Speed Increase
	case 5:
	{
		block->Disable();
		BallSpeedIncrease(50.0f);
		break;
	}
	// Score Multiplier
	case 6:
	{
		block->Disable();
		ScoreMult(2);
		break;
	}
	// Change Player Length
	case 7:
	{
		block->Disable();
		ResizePlayer(player->body->getSize().x * 2.0f);
		break;
	}
	default:

		break;
	}


	
}

void Game::ScoreMult(int mult)
{
	player->ActivateScoreMult(mult);
	ui.ActivateScoreMult();
}

void Game::ResizePlayer(float length)
{
	player->ActivateLengthChange(length);
}

void Game::BallSpeedIncrease(float speed_increase)
{
	ball->ChangeSpeed(speed_increase);
}

void Game::Explosion(int new_ball_amount, Ball* b)
{
	// Creates the Ball
	Ball* new_ball = new Ball
	(
		sf::Vector2f(b->body->getPosition()),	// Position
		sf::Vector2f(9.0f, 9.0f),							// Size
		sf::Color(0.0f, 255.0f, 0.0f),						// Colour 
		100.0f,												// Speed
		WIDTH, HEIGHT,										// Screen bounds
		5.0f												// Speed increase rate
	);

	new_ball->Y_Bounce();
	new_ball->X_Bounce();

	new_ball->body->setOutlineThickness(1.0f);
	new_ball->body->setOutlineColor(sf::Color(255, 255, 255));
	
	other_balls.push_back(new_ball);

}


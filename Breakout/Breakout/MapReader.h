#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>

struct BlockInfo
{
	sf::Vector2i pos;
	int block_num;
	

	void Init(int x, int y, int num)
	{
		pos.x = x;
		pos.y = y;
		block_num = num;
	}
};

#pragma once
class MapReader
{
public:
	MapReader();
	~MapReader();

	wchar_t* GetFileName(std::string filename, std::string file_type);
	std::vector<BlockInfo> ReadInMap(std::string filename);
	int GetMaxColumns();
	int GetMaxRows();
	int GetNumberOfBlocks();

private:
	int max_x;
	int max_y;
	int number_of_blocks;
};


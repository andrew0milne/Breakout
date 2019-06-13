#include "MapReader.h"



MapReader::MapReader()
{
	
}


MapReader::~MapReader()
{
}

std::vector<BlockInfo> MapReader::ReadInMap(std::string filename)
{
	std::vector<BlockInfo> block_info;

	std::ifstream file("Maps/" + filename + ".csv");
	std::string line = "";


	int x = 0;
	
	max_x = 0;
	max_y = 0;
	number_of_blocks = 0;

	while (std::getline(file, line))
	{
		std::stringstream line_stream(line);
		std::string data;

		max_y++;

		if (x > max_x)
		{
			max_x = x;
		}
		x = 0;

		while (std::getline(line_stream, data, ',') && max_y > 1)
		{
			BlockInfo temp;
			int data_to_int = 0;

			try
			{
				data_to_int = stoi(data);

			}
			catch (...)
			{
				if (data != "")
				{
					std::cout << "Data value (" << data << ") at " << x + 1 << ", " << max_y + 1 << " is invalid" << std::endl;
				}

				data_to_int = 0;
			}

			if (data_to_int != 0)
			{
				temp.Init(x, max_y - 2, data_to_int);
				block_info.push_back(temp);
				number_of_blocks++;
			}

			x++;
		}
		
	}

	std::cout << max_x << ", " << max_y << std::endl;

	return block_info;
}

int MapReader::GetMaxColumns()
{
	return max_x;
}

int MapReader::GetMaxRows()
{
	return max_y;
}

int MapReader::GetNumberOfBlocks()
{
	return number_of_blocks;
}

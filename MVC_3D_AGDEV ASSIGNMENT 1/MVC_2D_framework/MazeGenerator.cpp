#include "MazeGenerator.h"


MazeGenerator::MazeGenerator()
{
	srand(time(NULL));
	//Initialize the maze. Set it all to 1
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			theMaze[i][j] = 1;
		}
	}


	//Set the random direction bias to 1 to 4.
	//These numbers correspond to direction to check first.
	for (int i = 0; i < 4; i++)
	{
		RandomDirectionBias.push_back(i + 1);
	}

	RandomStart();

	Carve(x, z);

	FindPossibleExits();
}


MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::ShuffleRandom()
{
	std::random_shuffle(RandomDirectionBias.begin(), RandomDirectionBias.end());
}

void MazeGenerator::RandomStart()
{
	// r for row、c for column
	// Generate random r
	int r;
	int c;
	do
	{
		r = rand() % WIDTH;
	} while (r % 2 == 0);
	// Generate random c
	do
	{
		c = rand() % HEIGHT;
	} while (c % 2 == 0);

	//Set the starting path to 0
	theMaze[r][c] = 0;
	x = r;
	z = c;

}

void MazeGenerator::Carve(int x, int y)
{
	ShuffleRandom();
	// 4 random directions
	// Examine each direction
	for (int i = 0; i < RandomDirectionBias.size(); i++)
	{

		switch (RandomDirectionBias[i]){
		case 1: // Up
			//　Whether 2 cells up is out or not
			if (x - 2 <= 0)
			{
				//Save the location of the deadend to PossibleExits
				Location theLocation;
				theLocation.theArray = &theMaze[x][y];
				theLocation.x = x;
				theLocation.y = y;
				theLocation.Delete = false;
				PossibleExits.push_back(theLocation);
				continue;
			}
			if (theMaze[x - 2][y] != 0) {
				theMaze[x - 2][y] = 0;
				theMaze[x - 1][y] = 0;
				Carve(x - 2, y);
			}
			break;
		case 2: // Right
			// Whether 2 cells to the right is out or not
			if (y + 2 >= WIDTH - 1)
			{
				Location theLocation;
				theLocation.theArray = &theMaze[x][y];
				theLocation.x = x;
				theLocation.y = y;
				theLocation.Delete = false;
				PossibleExits.push_back(theLocation);
				continue;
			}
			if (theMaze[x][y + 2] != 0) {
				theMaze[x][y + 2] = 0;
				theMaze[x][y + 1] = 0;
				Carve(x, y + 2);
			}
			break;
		case 3: // Down
			// Whether 2 cells down is out or not
			if (x + 2 >= HEIGHT - 1)
			{
				Location theLocation;
				theLocation.theArray = &theMaze[x][y];
				theLocation.x = x;
				theLocation.y = y;
				theLocation.Delete = false;
				PossibleExits.push_back(theLocation);
				continue;
			}
			if (theMaze[x + 2][y] != 0) {
				theMaze[x + 2][y] = 0;
				theMaze[x + 1][y] = 0;
				Carve(x + 2, y);
			}
			break;
		case 4: // Left
			// Whether 2 cells to the left is out or not
			if (y - 2 <= 0)
			{
				Location theLocation;
				theLocation.theArray = &theMaze[x][y];
				theLocation.x = x;
				theLocation.y = y;
				theLocation.Delete = false;
				PossibleExits.push_back(theLocation);
				continue;
			}
			if (theMaze[x][y - 2] != 0) {
				theMaze[x][y - 2] = 0;
				theMaze[x][y - 1] = 0;
				Carve(x, y - 2);
			}
			break;
		}
	}
}

void MazeGenerator::Draw()
{

	//Drawing. You don't need to understand my pain.

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{

			if (i == x && j == z)
			{
				std::cout << "X ";
			}
			else
			{
				bool Printed = false;
				for (int counter = 0; counter < PossibleExits.size() && Printed == false; counter++)
				{
					if (i == PossibleExits[counter].x && j == PossibleExits[counter].y)
					{
						std::cout << "Y ";
						Printed = true;
					}
				}
				if (Printed == false)
				{
					std::cout << theMaze[i][j] << " ";
				}
			}
		}
		std::cout << std::endl;
	}
}

void MazeGenerator::FindPossibleExits()
{

	//Here, we check if how many roads are leading to the cell. A cell has
	//a maximum of 4 roads (N,S,E,W). If there is only one road leading to it,
	//than it is a candidate for exit.
	for (int i = 0; i < PossibleExits.size(); i++)
	{
		int Counter = 0;
		for (int k = -1; k < 2; k++)
		{
			if (k == 0)
				continue;
			if (theMaze[PossibleExits[i].x + k][(PossibleExits[i].y)] == 0)
			{
				Counter++;
			}
			if (theMaze[PossibleExits[i].x][(PossibleExits[i].y + k)] == 0)
			{
				Counter++;
			}
		}
		if (Counter != 1)
		{
			//Mark for deletion here.
			PossibleExits[i].Delete = true;
		}
	}

	//After marked for deletion, delete it now.
	//We want to seperate out deletion since in a vector
	//deletion could create messy codes when done all in the same time.
	for (auto i = PossibleExits.begin(); i != PossibleExits.end();)
	{
		if (i->Delete == true)
		{
			i = PossibleExits.erase(i);
			continue;
		}
		i++;
	}
}
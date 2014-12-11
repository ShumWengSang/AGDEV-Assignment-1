#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <iostream>
#define HEIGHT 3
#define WIDTH 3

//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
							MAZE GENERATOR
//							By Shum Weng Sang
//						1 is wall. 0 is path.  
/////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

struct Location
{
	int * theArray;
	int x;
	int y;
	bool Delete;

	~Location(){};
};

class MazeGenerator
{
public:
	//The map. 1 is wall. 0 is path.
	int theMaze[WIDTH][HEIGHT];

	//Two variables used to keep track of the starting position. Its Z and not Y since this is 3D.
	int x, z;

	std::vector<Location> PossibleExits;
	MazeGenerator();
	~MazeGenerator();
	void Draw();
private:
	//A vector used to control the direction of the search.
	std::vector<int> RandomDirectionBias;
	//Function that would shuffle the bias, so that the bias would also be randomed.
	void ShuffleRandom();
	//Function that would randomize your starting position. Position must be odd.
	void RandomStart();

	//Function that would carve the maze with a depth first algo.
	//X and Y are the starting position.
	void Carve(int x, int y);



	//Funcion that finds all the possible exits and puts them into PossibleExits vector
	void FindPossibleExits();

};


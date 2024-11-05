#include "Grid.h"
#include <iostream>

float Grid::gridWidth;
float Grid::gridHeight;
int Grid::gridAmount;

Grid::Grid()
{
	initialize();
}

void Grid::setShape(sf::RectangleShape t_shape, float t_width, float t_height, int t_ID)
{
	shape = t_shape;
	width = t_width;
	height = t_height;

	sf::Vector2f linePosition = shape.getPosition();
	linePosition.x += width / 2;
	linePosition.y += height / 2;

	lines[0].position = linePosition;
	lines[0].color = sf::Color::White;

	lines[1].position = linePosition;
	lines[1].color = sf::Color::White;

	cellID = t_ID;
}

void Grid::setDirection(sf::Vector2f t_direction)
{
	if (passable == false) 
	{
		direction = sf::Vector2f{ 0,0 };
		lines[0].position = shape.getPosition();
		lines[1].position = shape.getPosition();
		return;
	}

	direction = t_direction;

	sf::Vector2f linePosition = shape.getPosition();
	linePosition.x += width / 2;
	linePosition.y += height / 2;
	lines[0].position = linePosition;

	linePosition.x += (width / 2) * (direction.x);
	linePosition.y += (height / 2) * (direction.y);;
	lines[1].position = linePosition;
}

void Grid::calculateGoal(Grid* t_grid)
{
	sf::Vector2f start = shape.getPosition();
	sf::Vector2f end = t_grid->shape.getPosition();

	distanceFromGoal = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

void Grid::render(sf::RenderWindow& t_window)
{
	t_window.draw(lines, 2, sf::Lines);
}

void Grid::findNeighbours(std::vector<Grid>& t_grid)
{
	std::vector<int> neighbors;

	int gridWidth = 50;
	int gridHeight = 50;

	int row = cellID / gridWidth;
	int col = cellID % gridWidth;

	// North-West
	if (row > 0 && col > 0)
		neighbors.push_back(cellID - gridWidth - 1);
	// North
	if (row > 0)
		neighbors.push_back(cellID - gridWidth);
	// North-East
	if (row > 0 && col < gridWidth - 1)
		neighbors.push_back(cellID - gridWidth + 1);
	// West
	if (col > 0)
		neighbors.push_back(cellID - 1);
	// East
	if (col < gridWidth - 1)
		neighbors.push_back(cellID + 1);
	// South-West
	if (row < gridHeight - 1 && col > 0)
		neighbors.push_back(cellID + gridWidth - 1);
	// South
	if (row < gridHeight - 1)
		neighbors.push_back(cellID + gridWidth);
	// South-East
	if (row < gridHeight - 1 && col < gridWidth - 1)
		neighbors.push_back(cellID + gridWidth + 1);
	
	neighbouringCells = neighbors;
}


void Grid::initialize()
{
	shape.setSize(sf::Vector2f{ 50,50 });
	shape.setFillColor(sf::Color::Blue);
}
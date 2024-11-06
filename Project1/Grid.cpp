#include "Grid.h"
#include <iostream>

float Grid::gridWidth;
float Grid::gridHeight;
int Grid::gridAmount;

Grid::Grid()
{

}

void Grid::setShape(sf::RectangleShape& t_shape, float t_width, float t_height, int t_ID)
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

	// Font
	text.setPosition(shape.getPosition());
	text.setCharacterSize(10U);
	text.setFillColor(sf::Color::White);
	text.setString("");
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

void Grid::setFont(sf::Font& t_font)
{
	text.setFont(t_font);
}

void Grid::setCost(int t_cost)
{
	cost = t_cost;
	if (cost != 99999) {
		int temp = cost;
		text.setString(std::to_string(temp));
	}
}

void Grid::calculateGoal(Grid* t_grid)
{
	sf::Vector2f start = shape.getPosition();
	sf::Vector2f end = t_grid->shape.getPosition();

	distanceFromGoal = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
}

void Grid::render(sf::RenderWindow& t_window, bool t_text)
{
	t_window.draw(lines, 2, sf::Lines);
	if (t_text == true)
		t_window.draw(text);
}

void Grid::findNeighbours(std::vector<Grid>& t_grid)
{
	std::vector<Grid*> neighbors;

	int gridWidth = 50;
	int gridHeight = 50;

	int row = cellID / gridWidth;
	int col = cellID % gridWidth;

	int ID = 0;

	// North-West
	if (row > 0 && col > 0)
		ID = cellID - gridWidth - 1;
		//neighbors.push_back(&t_grid[ID]);

	// North
	if (row > 0)
		ID = cellID - gridWidth;
		neighbors.push_back(&t_grid[ID]);

	// North-East
	if (row > 0 && col < gridWidth - 1)
		ID = cellID - gridWidth + 1;
		//neighbors.push_back(&t_grid[ID]);

	// West
	if (col > 0)
		ID = cellID - 1;
		neighbors.push_back(&t_grid[ID]);

	// East
	if (col < gridWidth - 1)
		ID = cellID + 1;
		neighbors.push_back(&t_grid[ID]);

	// South-West
	if (row < gridHeight - 1 && col > 0)
		ID = cellID + gridWidth - 1;
		//neighbors.push_back(&t_grid[ID]);

	// South
	if (row < gridHeight - 1)
		ID = cellID + gridWidth;
		neighbors.push_back(&t_grid[ID]);

	// South-East
	if (row < gridHeight - 1 && col < gridWidth - 1)
		ID = cellID + gridWidth + 1;
		//neighbors.push_back(&t_grid[ID]);
	
	neighbouringCells = neighbors;
}

void Grid::changeColor()
{ 
	if (cost == 99999)
	{
		return;
	}
	else
	{
		float intensity = 1.0f - (std::min(cost, 25.f) / 25);
		sf::Uint8 blueValue = static_cast<sf::Uint8>(intensity * 255);

		// more intense blue for lower costs
		if (!goal)
			shape.setFillColor(sf::Color(0, 0, blueValue));
	}
}

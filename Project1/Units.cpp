#include "Units.h"

Units::Units() 
{
	initialize();
}
Units::~Units() {}



void Units::initialize()
{
	body.setSize(sf::Vector2f{ 10, 10 });
	body.setFillColor(sf::Color::Green);
	body.setPosition(pos);
	body.setOrigin(10 / 2, 10 / 2);
}

void Units::update()
{
	body.move(direction * speed);
	pos = body.getPosition();
	if (currentCell != nullptr)
	{
		sf::Vector2f cellLocation = currentCell->shape.getPosition();
		cellLocation.x += Grid::gridWidth / 2;
		cellLocation.y += Grid::gridHeight / 2;
		sf::Vector2f direction(cellLocation.x - pos.x, cellLocation.y - pos.y);
		float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (magnitude != 0)
		{
			direction.x /= magnitude;
			direction.y /= magnitude;
		}
		body.move(direction * 0.1f);
	}
}

void Units::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Units::setCurrentCell(sf::Vector2f t_direction, Grid* t_cell)
{
	direction = t_direction;
	currentCell = t_cell;
}



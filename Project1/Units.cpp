#include "Units.h"

Units::Units() 
{
	initialize();
}
Units::~Units() {}



void Units::initialize()
{
	body.setSize(sf::Vector2f{ 25, 25 });
	body.setFillColor(sf::Color::Green);
	body.setPosition(pos);
	body.setOrigin(25 / 2, 25 / 2);
}

void Units::update()
{
	body.move(direction * speed);
	pos = body.getPosition();
}

void Units::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Units::setDirection(sf::Vector2f t_direction)
{
	direction = t_direction;
}



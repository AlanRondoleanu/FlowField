#ifndef UNITS_H
#define UNITS_H
#include <SFML/Graphics.hpp>
#include "Trigonometry.hpp"
#include "VectorAlgebra2D.h"
#include "VectorAlgebra2D.inl"
#include "Grid.h"

class Units
{
public:
	Units();
	~Units();

	void update();
	void draw(sf::RenderWindow& t_window);;
	void setCurrentCell(sf::Vector2f t_direction, Grid* t_cell);

	sf::RectangleShape body;

	//Stat variables
	float speed{ 0.5 };
	sf::Vector2f direction{ 0,0 };
	
	//Getters-Setters
	sf::Vector2f getPos() { return pos; }

	void setPos(sf::Vector2f t_position) { pos = t_position, body.setPosition(pos); }

private:
	void initialize();

	sf::Vector2f pos{ 50, 50 };
	Grid* currentCell;
};
#endif

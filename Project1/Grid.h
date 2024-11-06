#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <algorithm>

class Grid
{
public:
	Grid();

	// Functions
	void calculateGoal(Grid* t_grid);
	void render(sf::RenderWindow& t_window, bool t_text);
	void findNeighbours(std::vector<Grid>& t_grid);
	void changeColor();

	// Vars
	bool passable{ true };
	bool goal{ false };
	float cost{ 99999 };
	sf::Vector2f direction{ 0,0 };
	std::vector<Grid*> neighbouringCells;

	static float gridWidth;
	static float gridHeight;
	static int gridAmount;

	// Getters and Setters
	void setShape(sf::RectangleShape& t_shape, float t_width, float t_height, int t_ID);
	void setDirection(sf::Vector2f t_direction);
	float getWidth() { return width; }
	float getHeight() { return height; }
	int getID() { return cellID; }
	void setFont(sf::Font& t_font);
	void setCost(int t_cost);
	sf::Vector2f getDirection(){ return direction; }

	sf::RectangleShape shape;
	sf::Vertex lines[2];

private:

	float distanceFromGoal{ 0 };
	float width{ 0 };
	float height{ 0 };
	int cellID{ 0 }; 
	sf::Text text;
};

#endif
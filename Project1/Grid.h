#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>

class Grid
{
public:
	Grid();

	// Functions
	void calculateGoal(Grid* t_grid);
	void render(sf::RenderWindow& t_window);
	void findNeighbours(std::vector<Grid>& t_grid);

	// Vars
	bool passable{ true };
	bool goal{ false };
	sf::Vector2f direction{ 0,0 };
	std::vector<int> neighbouringCells;

	static float gridWidth;
	static float gridHeight;
	static int gridAmount;

	// Getters and Setters
	void setShape(sf::RectangleShape t_shape, float t_width, float t_height, int t_ID);
	void setDirection(sf::Vector2f t_direction);
	float getWidth() { return width; }
	float getHeight() { return height; }
	sf::Vector2f getDirection(){ return direction; }

	sf::RectangleShape shape;
	sf::Vertex lines[2];

private:

	float distanceFromGoal{ 0 };
	float width{ 0 };
	float height{ 0 };
	int cellID{ 0 };

	void initialize();  
};

#endif
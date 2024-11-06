/// <summary>
/// Author: Alan Rondoleanu
/// Date: 15/11/2021
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Units.h"
#include  "Grid.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processKeyReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void initialize();
	void setGoal(Grid &t_grid);
	void setWall(Grid &t_grid);
	void generateFlowField(Grid& t_goal, std::vector<Grid>& t_flowField);
	void generateFlowFieldBFS(Grid* t_goal);
	void loadFont();

	sf::Vector2f getMousePosition();
	sf::Vector2f mousePosition;

	//Solider
	Units player;

	// Fonts
	sf::Font font;
	bool drawFont{ false };

	// Grid
	std::vector<Grid> gridVector;
	Grid* goal;

	sf::RenderWindow m_window; // main SFML window
	sf::Sprite backgroundSprite; // the sprite for the background
	sf::Texture gameBackground; // The background for the game

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP


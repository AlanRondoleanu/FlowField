/// <summary>
/// Author: Alan Rondoleanu
/// Date: 24/10/2024
/// </summary>

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 2400U, 1800U, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	initialize();
}

Game::~Game()
{
}

/// <summary>
/// main game loop
/// updates 60 times per second
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render();
	}
}
/// <summary>
/// handles events and inputs fron the user
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyReleases(newEvent);
		}
	}
}


/// <summary>
/// handles the key presses by the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		for (size_t i = 0; i < gridVector.size(); i++)
		{
			if (gridVector[i].shape.getGlobalBounds().contains(getMousePosition()))
			{
				setWall(gridVector[i]);

				return;
			}
		}
	}
	if (sf::Keyboard::E == t_event.key.code)
	{
		for (size_t i = 0; i < gridVector.size(); i++)
		{
			if (gridVector[i].shape.getGlobalBounds().contains(getMousePosition()))
			{
				setGoal(gridVector[i]);
				return;
			}
		}
	}
	if (sf::Keyboard::Q == t_event.key.code)
	{
		player.setPos(getMousePosition());
	}

	// Calculates the goal to the target
	if (sf::Keyboard::R == t_event.key.code)
	{
		for (size_t i = 0; i < gridVector.size(); i++)
		{
			gridVector[i].calculateGoal(goal);
		}

		generateFlowField(*goal, gridVector);
	}

	// Tweaking
	if (sf::Keyboard::T == t_event.key.code)
	{
		for (size_t i = 0; i < gridVector.size(); i++)
		{
			if (gridVector[i].shape.getGlobalBounds().contains(getMousePosition()))
			{
				gridVector[i].findNeighbours(gridVector);
				return;
			}
		}
	}
}

/// <summary>
/// Processes the keys released on the keyboard
/// </summary>
/// <param name="t_event">the key released</param>
void Game::processKeyReleases(sf::Event t_event)
{
	
}

/// <summary>
/// Update the game
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	mousePosition = getMousePosition();

	int gridX = static_cast<int>(player.getPos().x / Grid::gridWidth);
	int gridY = static_cast<int>(player.getPos().y / Grid::gridHeight);
	int gridNumber = gridY * 10 + gridX;
	sf::Vector2f direction = gridVector[gridNumber].getDirection();

	for (size_t i = 0; i < gridVector.size(); i++)
	{
		if (player.body.getGlobalBounds().intersects(gridVector[i].shape.getGlobalBounds()))
		{
			direction = gridVector[i].direction;
		}
	}

	

	player.setDirection(direction);
	player.update();
}

/// <summary>
/// draws the sprites and displays the window
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	
	//Render Grid
	for (int i = 0; i < gridVector.size(); i++)
	{
		m_window.draw(gridVector[i].shape);
	}
	for (int i = 0; i < gridVector.size(); i++)
	{
 		gridVector[i].render(m_window);
	}

	m_window.draw(player.body);

	//Draws the selected building on mouse location
	//playerBuildings[Buildings::PLAYER_BUILDING_AMOUNT]->draw(m_window);

	m_window.display();
}

void Game::initialize()
{
	// Grid creation
	sf::RectangleShape square;
	square.setFillColor(sf::Color::Black);
	square.setOutlineColor(sf::Color::Blue);
	square.setOutlineThickness(1);

	Grid::gridAmount = 50;
	float const width = 2400 / Grid::gridAmount;
	float const height = 1800 / Grid::gridAmount;
	Grid::gridWidth = width;
	Grid::gridHeight = height;


	square.setSize(sf::Vector2f(width, height));

	float x = 0;
	float y = 0;
	int cellNumber = 0;

	for (size_t o = 0; o < Grid::gridAmount; o++)
	{
		for (size_t i = 0; i < Grid::gridAmount; i++)
		{
			square.setPosition(x, y);

			Grid newGrid;
			newGrid.setShape(square, width, height, cellNumber);
			gridVector.push_back(newGrid);

			x += width;
			cellNumber++;
		}
		x = 0;
		y += height;
	}
}


sf::Vector2f Game::getMousePosition()
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(m_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(m_window).y;

	return m_mousePosition;
}

void Game::setGoal(Grid &t_grid)
{
	if (t_grid.passable == false)
	{
		return;
	}
	else {

		for (size_t i = 0; i < gridVector.size(); i++)
		{
			if (gridVector[i].goal == true &&
				gridVector[i].passable == true)
			{
				gridVector[i].goal = false;
				gridVector[i].shape.setFillColor(sf::Color::Black);
			}
		}

		if (t_grid.passable == true)
		{
			goal = &t_grid;
			t_grid.goal = true;
			t_grid.shape.setFillColor(sf::Color::Green);
		}
	}
}

void Game::setWall(Grid& t_grid)
{
	if (t_grid.passable == false)
	{
		t_grid.shape.setFillColor(sf::Color::Black);
		t_grid.passable = true;
	}
	else if (t_grid.goal == false)
	{
		t_grid.shape.setFillColor(sf::Color::Cyan);
		t_grid.passable = false;
	}
	else {
		return;
	}
}

void Game::generateFlowField(Grid& t_goal, std::vector<Grid>& t_flowField)
{
	sf::Vector2f goalPos = t_goal.shape.getPosition();

	for (Grid& grid : t_flowField) 
	{
		sf::Vector2f gridPos = grid.shape.getPosition();

		if (grid.goal != true &&
			grid.passable != false) 
		{
			sf::Vector2f direction(goalPos.x - gridPos.x, goalPos.y - gridPos.y);
			float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

			if (magnitude != 0) 
			{
				direction.x /= magnitude;
				direction.y /= magnitude;
			}
			grid.setDirection(direction);
		}
	}
}

void Game::generateFlowFieldBFS(Grid& t_goal, std::vector<Grid>& t_flowField)
{
	// Get neighbors of the cells
	for (Grid n : gridVector)
	{
		n.findNeighbours(gridVector);
	}

	sf::Vector2f goalPos = t_goal.shape.getPosition();

	for (Grid& grid : t_flowField)
	{
		sf::Vector2f gridPos = grid.shape.getPosition();

		
	}
}
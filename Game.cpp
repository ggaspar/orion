#include "Game.h"
#include "UserInterface.h"
#include "splashScreen.h"
#include "mainMenu.h"
#include "visibleGameObject.h"




sf::RenderWindow Game::_mainWindow;
GameBoard* Game::_gameBoard = 0;
Game::GameState2 Game::_gameState = Uninitialized;
map<PlayerId,string> _players;

sf::Clock Game::_clock;
GameObjectManager Game::_gameObjectManager;
sf::Event Game::_currentEvent;

/*void Game::createPlayers()
{

}
void Game::createGameBoard()
{
	//_gameBoard = new GameBoard;
}*/

void Game::startGame()
{

	//sf::RenderWindow window(sf::VideoMode(800,800,320), "Hello world!");
	//sf::CircleShape shape(400.f);
	//shape.setFillColor(sf::Color::Green);

	if(_gameState != Uninitialized)
	{
		return;
	}

	_gameState= Game::ShowingMenu;

	//res 800x600 with 32 bpp resolution
	_mainWindow.create(sf::VideoMode(800,600,32), "Orion");


	/*Card* c1 = new Card('A', 'D', 1);
	Card* c2 = new Card('K', 'D', 1);
	Card* c3 = new Card('Q', 'D', 1);

	//c1->load("assets/images/cards/diamonds-a-75.png");
	//c2->load("assets/images/cards/diamonds-k-75.png");
	//c3->load("assets/images/cards/diamonds-q-75.png");

	c3->setPosition((800/2)-90,480);
	c2->setPosition((800/2),480);
	c1->setPosition((800/2)+90,480);

	_gameObjectManager.add("c1",c1);
	_gameObjectManager.add("c2",c2);
	_gameObjectManager.add("c3",c3);
	*/

	while (!isExiting())
    {
		gameLoop();
    }
	_mainWindow.close();
	//_gameBoard->startGame();			
}

bool Game::isExiting()
{
  return (_gameState == Game::Exiting);    
}

void Game::gameLoop()
{
	
			
	_mainWindow.pollEvent(_currentEvent);
	_clock.restart();	

	switch(_gameState)
	{
		case Game::ShowingMenu:
		{
			showMenu();
			break;
		}
		case Game::ShowingSplash:
		{
			showSplashScreen();

			break;
		}
		case Game::Playing:
		{

			plays();			
			break;
		}
		
	}
	/*window.clear();
	window.draw(shape);
	window.display();*/
}

void Game::showDebug()
{
	sf::Text text;
	sf::Vector2i pos = sf::Mouse::getPosition(_mainWindow);

	std::stringstream ss;
	ss << "DEBUG INFO! posX: " << pos.x << " posY:" << pos.y;
	string debugInfo = ss.str();			
	text.setString(debugInfo);
	text.setCharacterSize(16); // in pixels, not points!
	text.setColor(sf::Color::Red);
	/*Text. setColor(sf::Color(128, 128, 0));
	Text.setRotation(90.f);
	Text.setScale(2.f, 2.f);
	Text.move(100.f, 200.f);*/
	sf::Font font;

	// Load it from a file
	if (!font.loadFromFile("assets/sansation.ttf"))
    //find this file in the "pong" example in the SFML examples folder
	{
	    std::cout << "Error loading font\n" ;
	}
	text.setFont(font);
	//text.setPosition(50,500);
	_mainWindow.draw(text);
}

void Game::plays()
{
	
	_mainWindow.clear(sf::Color(107,142,35));
	_gameObjectManager.updateAll(_clock);
	_gameObjectManager.drawAll(_mainWindow);
	showDebug();
	_mainWindow.display();



	if(_currentEvent.type == sf::Event::Closed)
	{
		_gameState = Game::Exiting;
	}
	if(_currentEvent.type == sf::Event::KeyPressed)
	{
		if(_currentEvent.key.code == sf::Keyboard::Escape)
		{
			showMenu();
		}
	}
	else
	{
		_gameBoard->go();
	}
	if(_currentEvent.type == sf::Event::MouseButtonPressed)
	{
		/*cout << "X: " << _currentEvent.mouseButton.x <<endl;
		cout << "Y: " << _currentEvent.mouseButton.y << endl;
		if(_currentEvent.mouseButton.x > 255 &&
			_currentEvent.mouseButton.x < 290 && 
			_currentEvent.mouseButton.y < 600 &&
			_currentEvent.mouseButton.y > 480)
		{
			((Card*)_gameObjectManager.get("c1"))->playCard();
		}	
		if(_currentEvent.mouseButton.x > 310 &&
			_currentEvent.mouseButton.x < 355 && 
			_currentEvent.mouseButton.y < 600 &&
			_currentEvent.mouseButton.y > 480)
		{
			((Card*)_gameObjectManager.get("c2"))->playCard();
		}	
		if(_currentEvent.mouseButton.x > 400 &&
			_currentEvent.mouseButton.x < 435 && 
			_currentEvent.mouseButton.y < 600 &&
			_currentEvent.mouseButton.y > 480)
		{
			((Card*)_gameObjectManager.get("c3"))->playCard();
		}	*/
	}

}
void Game::showSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::showMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
	       break;
		case MainMenu::Play:
			Game::_gameBoard = new GameBoard;
			_gameState = Game::Playing;
			break;
	}
}

sf::RenderWindow& Game::getWindow()
{
	return _mainWindow;
}

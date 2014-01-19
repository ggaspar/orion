#include "Game.h"
#include "UserInterface.h"
#include "splashScreen.h"
#include "mainMenu.h"
#include "visibleGameObject.h"




sf::RenderWindow Game::_mainWindow;
GameBoard* Game::_gameBoard = 0;
Game::GameState Game::_gameState = Uninitialized;
map<PlayerId,string> _players;
GameBoard::GamePhase Game::_matchPhase = GameBoard::GamePhase::NotPlaying;
float Game::_waitingTime;



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
	Game::_waitingTime = 0.0;
	if(_gameState != Uninitialized)
	{
		return;
	}

	_gameState= Game::ShowingMenu;

	//res 800x600 with 32 bpp resolution
	_mainWindow.create(sf::VideoMode(800,600,32), "Orion", sf::Style::Titlebar | sf::Style::Close);	
	_mainWindow.setVerticalSyncEnabled(true);
	


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
}

void Game::showDebug()
{
	sf::Text text;
	sf::Vector2i pos = sf::Mouse::getPosition(_mainWindow);

	std::stringstream ss;
	ss << "DEBUG INFO!" << endl << "Pos: " << pos.x << ", " << pos.y << endl;
	VisibleGameObject* object = _gameObjectManager.getObjectByPos(pos);
	if(object)
	{
		ss << "Object: " << _gameObjectManager.getObjectNameByPos(pos);
		ss << " pos: " << object->getPosition().x << ", " << object->getPosition().y <<endl;
	}
	ss << "Wating time: " << _waitingTime <<endl;
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


	_gameBoard->ShowStats();
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
	if(_matchPhase == GameBoard::GamePhase::EndingRound || _matchPhase == GameBoard::GamePhase::FinishingMatch)
		//&& )
	{	
		_waitingTime = _waitingTime + _clock.getElapsedTime().asSeconds();
		if (_matchPhase == GameBoard::GamePhase::FinishingMatch)
		{
			_gameBoard->processMatchWinner();
		}
		if(_waitingTime > TIME_BETWEEN_ROUNDS && _currentEvent.type == sf::Event::MouseButtonPressed)
		{
			_matchPhase = _gameBoard->go();
		}

	}
	else
	{
		_matchPhase = _gameBoard->go();
		_waitingTime = 0.0;
	}

	_mainWindow.display();

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

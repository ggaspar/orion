#include "stdsfml.h"
#include "GameObjectManager.h"
#include "tools.h"
#include "resources.h"
 
 
 
GameObjectManager::GameObjectManager()
{  
}
 
GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
}
 
void GameObjectManager::add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string,VisibleGameObject*>(name,gameObject));
}
 
void GameObjectManager::remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if(results != _gameObjects.end() )
	{
	    delete results->second;
	    _gameObjects.erase(results);
	}
}
 
VisibleGameObject* GameObjectManager::get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if(results == _gameObjects.end() )
	{
		return NULL;
	}
	return results->second;   
 }
 
int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}
 
 
void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while(itr != _gameObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::updateAll(sf::Clock clock)
{
  std::map<std::string,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
  //float timeDelta = renderWindow.GetFrameTime();
  //clock.getElapsedTime
  //float timeDelta = clock.restart().asMicroseconds();   

  float ElapsedTime = clock.getElapsedTime().asMicroseconds();  
  //cout << "time passed: " << ElapsedTime << endl;

  //cout << "fps: " << 1000000 / ElapsedTime << endl;

  while(itr != _gameObjects.end())
  {
    itr->second->update(ElapsedTime / 100);
    itr++;
  }
  
}


VisibleGameObject* GameObjectManager::getClickedObject(sf::Vector2i clickPosition)
{
	pair<string,VisibleGameObject*> object = getObjectPair(clickPosition, true);
	return object.second;
}

VisibleGameObject* GameObjectManager::getObjectByPos(sf::Vector2i clickPosition)
{
	pair<string,VisibleGameObject*> object = getObjectPair(clickPosition, false);
	return object.second;
}



string GameObjectManager::getObjectNameByPos(sf::Vector2i clickPosition)
{
	pair<string,VisibleGameObject*> object = getObjectPair(clickPosition, false);
	return object.first;
}

pair<string,VisibleGameObject*> GameObjectManager::getObjectPair(sf::Vector2i clickPosition, bool onlyClickable)
{
	map<string, VisibleGameObject*>::iterator itObjects = _gameObjects.begin();
	pair<string, VisibleGameObject*> result = make_pair("",new VisibleGameObject());
	for ( itObjects = _gameObjects.begin(); itObjects != _gameObjects.end(); ++itObjects)
	{
		VisibleGameObject *object = itObjects->second;
		sf::Vector2f objectPosition = object->getPosition();
		//int height = object._height;
		int topLimit = objectPosition.y + CARD_HEIGHT;
		int bottomLimit = objectPosition.y ;
		int leftLimit = objectPosition.x;
		int rightLimit = objectPosition.x + CARD_WIDTH;

		//bug: not catching the mouse position at exact moment of click
		if ((object->isClicable() || !onlyClickable) && 
			clickPosition.x < rightLimit && clickPosition.x > leftLimit && 
			clickPosition.y < topLimit && clickPosition.y > bottomLimit)
		{
			result = (*itObjects);
			break;
		}
	}
	return result;
}

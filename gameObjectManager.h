 #include "VisibleGameObject.h"
 

#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

class Card;
using namespace std;
 class GameObjectManager
 {
 public:  
   GameObjectManager();
   ~GameObjectManager();
 
   void add(std::string name, VisibleGameObject* gameObject);
   void remove(std::string name);
   int getObjectCount() const;
   VisibleGameObject* get(std::string name) const;
 
   void drawAll(sf::RenderWindow& renderWindow);
   void GameObjectManager::updateAll(sf::Clock clock);
   VisibleGameObject* getClickedObject(sf::Vector2i clickPosition);
   std::string getObjectNameByPos(sf::Vector2i clickPosition);
   VisibleGameObject* getObjectByPos(sf::Vector2i clickPosition);

 
 private:
	std::map<string, VisibleGameObject*> _gameObjects;
	pair<string,VisibleGameObject*>  getObjectPair(sf::Vector2i clickPosition, bool onlyClickable=true);
   
   struct GameObjectDeallocator
   {
     void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
     {
       delete p.second;
     }
   };
 };

 #endif
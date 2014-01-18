 #include "VisibleGameObject.h"
 

#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

class Card;

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

 
 private:
	std::map<std::string, VisibleGameObject*> _gameObjects;

   
   struct GameObjectDeallocator
   {
     void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
     {
       delete p.second;
     }
   };
 };

 #endif
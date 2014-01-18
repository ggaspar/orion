#include "stdsfml.h"

#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__


class MainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play };  
 
	struct MenuItem
	{
		public:
		 sf::Rect<int> rect;
		 MenuResult action;
    };
  
	MenuResult Show(sf::RenderWindow& window);
 
 private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};
#endif
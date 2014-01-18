#include "splashScreen.h"

#ifndef __SPLASH_SCREEN_H__
#define __SPLASH_SCREEN_H__


void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Texture image;
	if(image.loadFromFile("assets/images/splash-temp2.png") != true)
	{
	    return;
	}

	sf::Sprite sprite(image);
  
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while(true)
	{
		while(renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::EventType::KeyPressed 
			|| event.type == sf::Event::EventType::MouseButtonPressed
			|| event.type == sf::Event::EventType::Closed )
			{
		        return;
			}
		}
	}
}
#endif

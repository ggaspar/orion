#include "stdsfml.h" 


#ifndef __VISIBLE_GAME_OBJECT_H__
#define __VISIBLE_GAME_OBJECT_H__


class VisibleGameObject
 {
  public:
	VisibleGameObject();
    virtual ~VisibleGameObject();
    
    virtual void load(std::string filename);
    virtual void draw(sf::RenderWindow & window);
	virtual void update(float elapsedTime);
 
	virtual void setPosition(float x, float y);
	virtual sf::Vector2f getPosition() const;
	virtual bool isLoaded() const;
	void activate();
	void deactivate();
	bool isClicable() { return _isClickable; };
	void setIsClickable(bool iIsClicable) { _isClickable = iIsClicable; }
	int  _width, _height;


 protected:
	sf::Sprite& getSprite();

 private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
	bool _isActivated;
	bool _isClickable;
 
};

#endif
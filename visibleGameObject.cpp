#include "visibleGameObject.h"


VisibleGameObject::VisibleGameObject() : _isActivated(false)
{
  _isLoaded = false;
}


VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::load(std::string filename)
{
  if(_image.loadFromFile(filename) == false)
  {
    _filename = "";
    _isLoaded = false;
  }
  else
  {
    _filename = filename;
	_sprite.setTexture(_image);
    _isLoaded = true;
  }
}

void VisibleGameObject::draw(sf::RenderWindow & renderWindow)
{
  if(_isLoaded && _isActivated)
  {
    renderWindow.draw(_sprite);
  }
}

void VisibleGameObject::setPosition(float x, float y)
{
  if(_isLoaded)
  {
    _sprite.setPosition(x,y);
  }
}

void VisibleGameObject::update(float elapsedTime)
{
}


sf::Vector2f VisibleGameObject::getPosition() const
{
  if(_isLoaded)
  {
    return _sprite.getPosition();
  }
  return sf::Vector2f();
}


sf::Sprite& VisibleGameObject::getSprite()
{
  return _sprite;
}

bool VisibleGameObject::isLoaded() const
{
  return _isLoaded;
}

void VisibleGameObject::activate()
{
  _isActivated = true;
}

void VisibleGameObject::deactivate()
{
  _isActivated = false;
}
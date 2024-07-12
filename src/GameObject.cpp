//
// Created by copig on 23/02/2024.
//

#include "GameObject.h"
//#include "Player.h"
#include <iostream>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}
sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

bool GameObject::initSprite(sf::Texture& texture, std::string file_name)
{
  if(!texture.loadFromFile(file_name)) {
    std::cout << "GameObject texture did not load\n";
  }
  sprite = new sf::Sprite;
  if(sprite != nullptr) { this->sprite->setTexture(texture); }
  if(sprite != nullptr) { this->sprite->setScale(0.75, 0.75); }
  //SET SWITCH CASE HERE FOR COLOUR
  return true;
}

const sf::Vector2f& GameObject::getMoveDirection() const
{
  return move_direction;
}
void GameObject::setMoveDirection(const sf::Vector2f& moveDirection)
{
  move_direction = moveDirection;
}

bool GameObject::checkRectCollision(GameObject& player, sf::RectangleShape rect)
{
  if((player.getSprite()->getPosition().x < rect.getPosition().x+rect.getGlobalBounds().width) && (player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width > rect.getPosition().x))
  {
    return true;
  }
  return false;
}

bool GameObject::checkPlatformCollision(GameObject& player, sf::RectangleShape rect)
{
  if((player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height > rect.getPosition().y) &&
      (player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height < rect.getPosition().y+4))
  {
    if((player.getSprite()->getPosition().x+player.getSprite()->getGlobalBounds().width > rect.getPosition().x)
        && (player.getSprite()->getPosition().x < rect.getPosition().x+rect.getGlobalBounds().width)
        )
      {
        //std::cout << "Collision procced" << std::endl;
        return true;
      }
      return false;
  }
  return false;
}

bool GameObject::checkDecayingPlatformCollision(GameObject& player, sf::Sprite& platform_chunk)
{
  if((player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height > platform_chunk.getPosition().y) &&
      (player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height < platform_chunk.getPosition().y+4) &&
      (player.getSprite()->getPosition().x+player.getSprite()->getGlobalBounds().width > platform_chunk.getPosition().x)
          && (player.getSprite()->getPosition().x < platform_chunk.getPosition().x+platform_chunk.getGlobalBounds().width))
  {
        //std::cout << "Collision procced" << std::endl;
        return true;
  }
  return false;
}

bool GameObject::checkPlatformCollisionWall(GameObject& player, sf::RectangleShape rect)
{
  if((player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height > rect.getPosition().y) &&
      (player.getSprite()->getPosition().y < rect.getPosition().y+rect.getGlobalBounds().height) &&
      (player.getSprite()->getPosition().x+player.getSprite()->getGlobalBounds().width > rect.getPosition().x) &&
      (player.getSprite()->getPosition().x < rect.getPosition().x+rect.getGlobalBounds().width))
      {
        //std::cout << "Collision procced" << std::endl;
        return true;
      }
  return false;
}

bool GameObject::isActive() const
{
  return is_active;
}
void GameObject::setIsActive(bool isActive)
{
  is_active = isActive;
}
void GameObject::animateEnemy(int direction, GameObject& enemy) {
  if (enemy.animation_clock.getElapsedTime().asSeconds() > 0.08)
  {
        if(direction == -1) { direction = 0; }
        sprite_texture_rect = sf::IntRect(
          sprite_rect_pos[direction][frame].x, enemy.getSprite()->getTextureRect().top, sprite_rect_pos[direction][frame].y, 16);
        getSprite()->setTextureRect(sprite_texture_rect);
        if (frame < 3)
        {
        frame++;
        }
        else
        {
        frame = 0;
        }
        enemy.animation_clock.restart();
  }
}
void GameObject::moveEnemy(GameObject& enemy, float dt, int direction) {
  enemy.getSprite()->move(direction * speed * dt, 0);
  enemy.animateEnemy(direction, enemy);
}
int GameObject::getSpeed() const
{
  return speed;
}
void GameObject::setSpeed(int speed)
{
  GameObject::speed = speed;
}
const sf::Vector2f& GameObject::getMovementLimits() const
{
  return movement_limits;
}
void GameObject::setMovementLimits(const sf::Vector2f& movementLimits)
{
  movement_limits = movementLimits;
}
bool GameObject::isOnPlatform(GameObject& player)
{

}
int GameObject::getDecayTimer() const
{
  return decay_timer;
}
void GameObject::setDecayTimer(int decayTimer)
{
  decay_timer = decayTimer;
}
const sf::Texture& GameObject::getTexture() const
{
  return texture;
}
void GameObject::setTexture(const sf::Texture& texture)
{
  GameObject::texture = texture;
}
const sf::Vector2f& GameObject::getSize() const
{
  return size;
}
void GameObject::setSize(const sf::Vector2f& size)
{
  GameObject::size = size;
}
const std::string& GameObject::getType() const
{
  return type;
}
void GameObject::setType(const std::string& type)
{
  GameObject::type = type;
}
const sf::Color& GameObject::getFill() const
{
  return fill;
}
void GameObject::setFill(const sf::Color& fill)
{
  GameObject::fill = fill;
}

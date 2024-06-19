//
// Created by copig on 23/02/2024.
//

#include "Player.h"
#include "GameObject.h"
#include "Platform.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

Player::Player() : GameObject()
{

}

Player::~Player()
{

}

void Player::playerMove(float dt, Player &player, sf::Clock& animation_clock)
{
  if((!is_jumping) && (is_falling))
  {
    getSprite()->move(0, 1 * speed * dt);
    y_velocity += gravity;
  }
  else if((!is_jumping) && (!is_falling))
  {
    if(moving_platform)
    {
      getSprite()->move(-1 * speed * dt, 0);
    }
    else
    {
      if (move_left)
      {
        getSprite()->move(-1 * speed * dt, 0);

        // ANIMATION
        animatePlayer(player, animation_clock, 1);
      }
      if (move_right)
      {
        player.getSprite()->move(1 * speed * dt, 0);

        // ANIMATION
        animatePlayer(player, animation_clock, 0);
      }
    }
  }

  if(is_jumping)
  {

    if(jump_right)
    {
      getSprite()->move(x_velocity * dt, y_velocity * dt);
      y_velocity += gravity;

      //ANIMATION
      animatePlayer(player, animation_clock, 0);
    }
    else if (jump_left)
    {
      getSprite()->move(-x_velocity * dt, y_velocity * dt);
      y_velocity += gravity;
      //std::cout << y_velocity << std::endl;

      //ANIMATION
      animatePlayer(player, animation_clock, 1);
    }
    else
    {
      getSprite()->move(0, y_velocity * dt);
      y_velocity += gravity;
      if (getSprite()->getPosition().y <= max_y_jump)
      {
        is_jumping = false;
        is_falling = true;
      }
    }
  }
}



int Player::getLives() const
{
  return lives;
}
void Player::setLives(int lives)
{
  Player::lives = lives;
}
int Player::getScore() const
{
  return score;
}
void Player::setScore(int score)
{
  Player::score = score;
}
int Player::getSpeed() const
{
  return speed;
}
void Player::setSpeed(int speed)
{
  Player::speed = speed;
}
bool Player::checkPlatformCollision(GameObject& player, sf::RectangleShape rect)
{
  return GameObject::checkPlatformCollision(player, rect);
}

bool Player::checkDecayingPlatformCollision(GameObject& player, sf::Sprite& platform_chunk)
{
  return GameObject::checkDecayingPlatformCollision(player, platform_chunk);
}

void Player::animatePlayer(GameObject& player, sf::Clock& animation_clock, int direction)
{
  if (animation_clock.getElapsedTime().asSeconds() > 0.08)
  {
    sprite_texture_rect = sf::IntRect(
      sprite_rect_pos[direction][frame].x, 0, sprite_rect_pos[direction][frame].y, 16);
    getSprite()->setTextureRect(sprite_texture_rect);
    if (frame < 3)
    {
      frame++;
    }
    else
    {
      frame = 0;
    }
    animation_clock.restart();
  }
}
int Player::getKeys() const
{
  return keys;
}
void Player::setKeys(int keys)
{
  Player::keys = keys;
}

bool Player::checkEnemyCollison(GameObject& player, GameObject& enemy)
{
  if((player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width > enemy.getSprite()->getPosition().x &&
      player.getSprite()->getPosition().x < enemy.getSprite()->getPosition().x + enemy.getSprite()->getGlobalBounds().width) &&
      (player.getSprite()->getPosition().y + player.getSprite()->getGlobalBounds().height > enemy.getSprite()->getPosition().y &&
       player.getSprite()->getPosition().y < enemy.getSprite()->getPosition().y + enemy.getSprite()->getGlobalBounds().height))
  {
    return true;
  }
  else {
    return false;
  }
}
bool Player::checkDecayPlatformCollison(GameObject& player, GameObject& platform, Platform& platform1)
{
  if((player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height > platform.getSprite()->getPosition().y) &&
      (player.getSprite()->getPosition().y+player.getSprite()->getGlobalBounds().height < platform.getSprite()->getPosition().y+4) &&
    (player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width > platform.getSprite()->getPosition().x &&
      player.getSprite()->getPosition().x < platform.getSprite()->getPosition().x + platform.getSprite()->getGlobalBounds().width))
    {
      return true;
    }
  return false;
}
const sf::Vector2f& Player::getCurrentPlatformConstraints() const
{
  return current_platform_constraints;
}
void Player::setCurrentPlatformConstraints(
  const sf::Vector2f& currentPlatformConstraints)
{
  current_platform_constraints = currentPlatformConstraints;
}
bool Player::isMovingPlatform() const
{
  return moving_platform;
}
void Player::setMovingPlatform(bool movingPlatform)
{
  moving_platform = movingPlatform;
}


//
// Created by copig on 23/02/2024.
//

#ifndef PLATFORMERSFML_GAMEOBJECT_H
#define PLATFORMERSFML_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
//#include "Player.h"

class GameObject {

 public:
  GameObject();
  ~GameObject();
  bool initSprite(sf::Texture &texture, std::string file_name);
  sf::Sprite* getSprite();
  bool checkRectCollision(GameObject& player, sf::RectangleShape rect);
  virtual bool checkPlatformCollision(GameObject& player, sf::RectangleShape rect);
  virtual bool checkDecayingPlatformCollision(GameObject& player, sf::Sprite& platform_chunk);
  bool checkPlatformCollisionWall(GameObject& player, sf::RectangleShape rect);
  bool isOnPlatform(GameObject& player);
  const sf::Vector2f& getMoveDirection() const;
  void setMoveDirection(const sf::Vector2f& moveDirection);
  sf::Texture texture;
  sf::IntRect sprite_texture_rect;
  sf::Vector2f sprite_rect_pos[2][4];
  const sf::Vector2f& getMovementLimits() const;
  void setMovementLimits(const sf::Vector2f& movementLimits);
  int getSpeed() const;
  void setSpeed(int speed);
  bool isActive() const;
  void setIsActive(bool isActive);
  void animateEnemy(int direction, GameObject& enemy);
  void moveEnemy(GameObject& enemy, float dt, int direction);

 private:
  sf::Sprite *sprite = nullptr;
  sf::Vector2f move_direction;
  bool is_active = true;
  int frame = 0;
  int speed = 0;
  sf::Vector2f movement_limits = {0,0};
  sf::Clock animation_clock;

};


#endif // PLATFORMERSFML_GAMEOBJECT_H

//
// Created by copig on 23/02/2024.
//

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "GameObject.h"
#include "Platform.h"

class Player: public GameObject {

 private:
  int lives = 3;
  int score = 0;
  int speed = 100;
  int keys = 0;

 public:
  int getKeys() const;
  void setKeys(int keys);
  int getSpeed() const;
  void setSpeed(int speed);
  Player();
  ~Player();

  void playerMove(float dt, Player &player, sf::Clock& animation_clock);
  int getLives() const;
  void setLives(int lives);
  int getScore() const;
  void setScore(int score);
  virtual bool checkPlatformCollision(GameObject& player, sf::RectangleShape rect);
  virtual bool checkDecayingPlatformCollision(GameObject& player, sf::Sprite& platform_chunk);
  void animatePlayer(GameObject& player, sf::Clock& animation_clock, int direction);
  bool checkEnemyCollison(GameObject& player, GameObject& enemy);
  bool checkDecayPlatformCollison(GameObject& player, GameObject& platform, Platform& platform1);


  bool move_left = false;
  bool move_right = false;
  bool is_falling = true;
  bool is_jumping = false;
  bool jump_left = false;
  bool jump_right = false;
  bool on_platform = false;
  bool moving_platform = false;
  bool isMovingPlatform() const;
  void setMovingPlatform(bool movingPlatform);
  sf::Vector2f current_platform_constraints = {0,0};
  const sf::Vector2f& getCurrentPlatformConstraints() const;
  void setCurrentPlatformConstraints(const sf::Vector2f& currentPlatformConstraints);
  float y_velocity = 0;
  float y_velocity_modifier = -160;
  float x_velocity = 100;
  float gravity = 3;
  int frame = 0;


  float max_y_jump = 0;
  //float offsetX = 0;
  //float offsetX1 = 0;
  //float offsetY = 0;

};

#endif // PLATFORMERSFML_PLAYER_H

//
// Created by copig on 23/02/2024.
//

#ifndef PLATFORMERSFML_ENEMY_H
#define PLATFORMERSFML_ENEMY_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Enemy: public GameObject {

 public:
  Enemy();
  ~Enemy();

 private:
  int speed = 100;

};

#endif // PLATFORMERSFML_ENEMY_H

//
// Created by copig on 01/04/2024.
//

#ifndef PLATFORMERSFML_PLATFORM_H
#define PLATFORMERSFML_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Platform: public GameObject {
 private:
  int decay_timer = 4;

 public:
  int getDecayTimer() const;
  void setDecayTimer(int decayTimer);

 public:

};

#endif // PLATFORMERSFML_PLATFORM_H

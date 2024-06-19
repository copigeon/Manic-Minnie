//
// Created by copig on 01/04/2024.
//

#include "Platform.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"

int Platform::getDecayTimer() const
{
  return decay_timer;
}
void Platform::setDecayTimer(int decayTimer)
{
  decay_timer = decayTimer;
}

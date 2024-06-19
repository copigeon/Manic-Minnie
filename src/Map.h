//
// Created by copig on 23/02/2024.
//

#ifndef PLATFORMERSFML_MAP_H
#define PLATFORMERSFML_MAP_H

#include <SFML/Graphics.hpp>

class Map {

 public:
  Map();
  ~Map();
  int getHazards() const;
  void setHazards(int hazards);
  int getEnemies() const;
  void setEnemies(int enemies);
  int getKeys() const;
  void setKeys(int keys);
  int getPlatforms() const;
  void setPlatforms(int platforms);
  int getColourRed() const;
  void setColourRed(int colourRed);
  int getColourBlue() const;
  void setColourBlue(int colourBlue);
  int getColourGreen() const;
  void setColourGreen(int colourGreen);
  int getDecayPlatforms() const;
  void setDecayPlatforms(int decayPlatforms);

 private:
  int enemies = 0;
  int hazards = 0;
  int keys = 0;
  int platforms = 0;
  int decay_platforms = 0;
  int colour_red = 0;
  int colour_green = 0;
  int colour_blue = 0;

};

#endif // PLATFORMERSFML_MAP_H

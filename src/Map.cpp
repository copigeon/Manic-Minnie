//
// Created by copig on 23/02/2024.
//

#include "Map.h"


Map::Map()
{

}

Map::~Map()
{

}
int Map::getHazards() const
{
  return hazards;
}
void Map::setHazards(int hazards)
{
  Map::hazards = hazards;
}
int Map::getEnemies() const
{
  return enemies;
}
void Map::setEnemies(int enemies)
{
  Map::enemies = enemies;
}
int Map::getKeys() const
{
  return keys;
}
void Map::setKeys(int keys)
{
  Map::keys = keys;
}
int Map::getPlatforms() const
{
  return platforms;
}
void Map::setPlatforms(int platforms)
{
  Map::platforms = platforms;
}
int Map::getDecayPlatforms() const
{
  return decay_platforms;
}
void Map::setDecayPlatforms(int decayPlatforms)
{
  decay_platforms = decayPlatforms;
}
int Map::getColourRed() const
{
  return colour_red;
}
void Map::setColourRed(int colourRed)
{
  colour_red = colourRed;
}
int Map::getColourBlue() const
{
  return colour_blue;
}
void Map::setColourBlue(int colourBlue)
{
  colour_blue = colourBlue;
}
int Map::getColourGreen() const
{
  return colour_green;
}
void Map::setColourGreen(int colourGreen)
{
  colour_green = colourGreen;
}

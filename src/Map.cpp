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
const std::string& Map::getName() const
{
  return name;
}
void Map::setName(const std::string& name)
{
  Map::name = name;
}
const std::string& Map::getColour() const
{
  return colour;
}
void Map::setColour(const std::string& colour)
{
  Map::colour = colour;
}
const std::string& Map::getEnemiesContainer() const
{
  return enemies_container;
}
void Map::setEnemiesContainer(const std::string& enemiesContainer)
{
  enemies_container = enemiesContainer;
}
const std::string& Map::getHazardsContainer() const
{
  return hazards_container;
}
void Map::setHazardsContainer(const std::string& hazardsContainer)
{
  hazards_container = hazardsContainer;
}
const std::string& Map::getKeysContainer() const
{
  return keys_container;
}
void Map::setKeysContainer(const std::string& keysContainer)
{
  keys_container = keysContainer;
}
const std::string& Map::getPlatformsContainer() const
{
  return platforms_container;
}
void Map::setPlatformsContainer(const std::string& platformsContainer)
{
  platforms_container = platformsContainer;
}
const std::string& Map::getGateContainer() const
{
  return gate_container;
}
void Map::setGateContainer(const std::string& gateContainer)
{
  gate_container = gateContainer;
}

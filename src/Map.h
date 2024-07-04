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
  const std::string& getName() const;
  void setName(const std::string& name);
  const std::string& getColour() const;
  void setColour(const std::string& colour);
  const std::string& getEnemiesContainer() const;
  void setEnemiesContainer(const std::string& enemiesContainer);
  const std::string& getHazardsContainer() const;
  void setHazardsContainer(const std::string& hazardsContainer);
  const std::string& getKeysContainer() const;
  void setKeysContainer(const std::string& keysContainer);
  const std::string& getPlatformsContainer() const;
  void setPlatformsContainer(const std::string& platformsContainer);
  const std::string& getGateContainer() const;
  void setGateContainer(const std::string& gateContainer);

 private:
  std::string name = "holder map name";
  std::string colour = "black";
  int enemies = 0;
  int hazards = 0;
  int keys = 0;
  int platforms = 0;
  int decay_platforms = 0;
  int colour_red = 0;
  int colour_green = 0;
  int colour_blue = 0;
  std::string enemies_container = "holder";
  std::string hazards_container = "holder";
  std::string keys_container = "holder";
  std::string platforms_container = "holder";
  std::string gate_container = "holder";

};

#endif // PLATFORMERSFML_MAP_H

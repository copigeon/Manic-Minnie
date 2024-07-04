
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStates.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Platform.h"
#include "Audio.h"
#include "Text.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();

  bool init();
  void update(float dt);
  void render();

  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

  void loadFonts();

  void resetGame();
  void resetPlayer();
  void initPlayer();

  Audio *audio = nullptr;
  Text *text = nullptr;
  Player *player = nullptr;
  GameObject *gate = nullptr;
  GameObject *key_array = nullptr;
  GameObject *enemy_array = nullptr;
  GameObject *hazards_array = nullptr;
  Platform *platform_1 = nullptr;
  Platform *platform_2 = nullptr;
  Platform *platform_3 = nullptr;
  Platform *platform_4 = nullptr;
  Platform *platform_5 = nullptr;
  Platform *platform_6 = nullptr;
  Platform *platform_7 = nullptr;
  Platform *platform_8 = nullptr;
  Platform *platform_9 = nullptr;
  Platform *platform_10 = nullptr;
  sf::RectangleShape *platform_array = nullptr;
  sf::Clock animation_clock;
  sf::Sprite life_sprite[3];
  sf::Texture sprite_sheet;
  sf::IntRect life_texture_rect;
  sf::Clock life_animation_clock;
  sf::Clock enemy_animation_clock;
  sf::Clock key_animation_clock;
  sf::Clock platform_decay_clock;
  std::string high_scores_array[10][10];

  int current_map = 0;
  void mapSequencer();

  int life_frame;
  bool flash = false;
  bool key_flash = false;

 //collisions
  void checkPlatformCollide(float dt);
  void checkDecayPlatformCollide(Platform *platform);

  //create map variable stores
  Map *map_central_cavern = nullptr;
  Map *map_the_cold_room = nullptr;
  Map *map_container = nullptr;
  void initMaps();

  //BUILD STATE SCREENS
  void buildSplash();
  void buildIntro();
  void buildPlaying();
  void buildOptions();
  void buildWin();
  void buildLose();
  void buildFinale();
  void buildMap();

  //HIGH SCORE STUFF
  void getHighScores(std::string (&high_scores_array)[10][10]);
  void sortHighScores(std::string (&high_scores_array)[10][10]);
  void updateHighScores(std::string (&high_scores_array)[10][10], Player* player);
  std::string high_score_entry_alphabet[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
  int player_name_letter = 0;
  int player_name_scroll = 0;
  int player_name_position_1 = 0;
  int player_name_position_2 = 0;
  int player_name_position_3 = 0;
  std::string letter_1 = high_score_entry_alphabet[player_name_scroll];
  std::string letter_2 = high_score_entry_alphabet[player_name_scroll];
  std::string letter_3 = high_score_entry_alphabet[player_name_scroll];
  std::string player_name_entry;

  //BUILD MAPS
  void buildMapCavern();
  void buildMapCold();
  void buildMapTest();
  void buildMenuSong();
  int song[3][69] = {16,20,22,7,26,7,24,26,7,16,20,22,8,26,7,24,8,15,18,23,8,26,8,24,8,15,18,23,7,26,7,24,7,16,20,22,24,11,27,11,26,11,16,20,22,24,13,28,13,26,18,20,13,23,13,21,22,7,26,7,24,20,18,23,22,7,0,16,7,
                      33,33,33,11,27,11,33,33,11,33,33,33,11,27,10,26,11,33,33,33,11,28,11,26,11,33,33,33,11,28,11,26,11,33,33,33,33,16,28,16,27,16,33,33,33,33,16,33,16,28,33,33,23,33,23,33,33,26,33,26,33,33,33,33,33,16,16,33,161,
                      100,100,5,5,6,10,2,10,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  };

  void animateLife(sf::Clock& life_animation_clock);
  void setDecayPlatformColours(Platform *platform, int red, int green, int blue);
  void initDecayPlatforms(Platform *platform, Map* map, int x, int y, int size);
  void playerDie();
  void drawDecayPlatforms(Platform *platform, int size);
  void defineMapSpecifics();

  int menu_song_note = 0;
  float menu_timer = 0.3;
  float intro_timer = 1;
  float intro_timer_scroll = 0.2;
  bool background_flag = true;

  // map_variable_generics
  std::string map_name = "holder map name";
  int map_enemies = 0;
  int map_keys = 0;
  std::string map_colour = "black";
  int map_platforms = 0;
  int map_decay = 0;
  int map_hazards = 0;
  int map_red = 0;
  int map_green = 0;
  int map_blue = 0;

 private:
  sf::RenderWindow& window;
  GameState game_state = GameState::SPLASH;
  MapState mapstate = MapState::CENTRAL_CAVERN;

  // SPLASH
  sf::Sprite splash_background;
  sf::Texture splash_background_texture;

  // INTRO
  sf::RectangleShape left_bar;
  sf::RectangleShape right_bar;
  sf::Texture bar_texture;
  sf::RectangleShape top_bar;
  sf::Texture top_bar_texture;
  sf::RectangleShape bottom_bar;
  sf::Texture bottom_bar_texture;

  //PLAYING
  sf::RectangleShape room_name_bar;
  sf::RectangleShape air_red;
  sf::RectangleShape air_green;
  sf::RectangleShape air;
  float air_bar = 800;
  int key_frame = 0;
  sf::Color key_colours[6] = {sf::Color::Red, sf::Color::Blue,sf::Color::Yellow,sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan};

  sf::RectangleShape map_left_wall;
  sf::RectangleShape map_right_wall;
  sf::RectangleShape map_block;
  sf::RectangleShape map_block_2;
  sf::RectangleShape ui_block_bottom;
  sf::RectangleShape ui_block_top;
  sf::Texture wall_texture;

  //ROOMS
  sf::Texture platform_wall_texture;
  sf::Texture elevator_texture_1;
  sf::Texture platform_texture;

  //OPTIONS
  sf::Sprite options_background;
  sf::Texture options_background_texture;
  sf::RectangleShape key_1;
  sf::RectangleShape key_2;

  //HIGH SCORE STUFF
  sf::RectangleShape win_banner;
  sf::Texture win_banner_texture;

  //WIN

  //LOSE
  sf::Color game_over_colour[8] = {sf::Color::Black, sf::Color::Blue,sf::Color::Red,sf::Color::Red, sf::Color::Magenta, sf::Color::Magenta};
  int game_over_counter = 0;
  sf::Sprite lose_player_sprite;
  sf::Sprite lose_boot_sprite;
  sf::RectangleShape lose_leg_rect;
  sf::Texture lose_leg_texture;
  sf::Sprite lose_podium_sprite;
  sf::RectangleShape background_block;

};

#endif // PLATFORMER_GAME_H

//
// Created by copig on 19/06/2024.
//

#ifndef PLATFORMERSFML_TEXT_H
#define PLATFORMERSFML_TEXT_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Text
{
 public:
  Text(sf::RenderWindow& window);
  ~Text();

  //FONTS
  sf::Font title_font;
  sf::Font basic_font;
  sf::Font font;


  // SPLASH
  sf::Text splash_text;

  // INTRO
  sf::Text intro_text;
  sf::Text intro_text_1;
  sf::Text intro_text_2;

  //PLAYING
  sf::Text room_name_text;
  sf::Text air_text;
  sf::Text ui_top_text_quit;
  sf::Text ui_top_text_controls;
  sf::Text ui_top_text_music;

  sf::Text high_score_text;
  sf::Text score_text;

  //ROOMS

  //OPTIONS
  sf::Text options_text;
  sf::Text options_text_1;
  sf::Text options_text_2;
  sf::Text options_enter_play;

  //HIGH SCORE STUFF
  sf::Text well_done;
  sf::Text player_name;
  sf::Text new_high_score_1;
  sf::Text new_high_score_2;
  sf::Text new_high_score_3;
  sf::Text return_to_options;
  sf::Text score_1;
  sf::Text score_2;
  sf::Text score_3;
  sf::Text score_4;
  sf::Text score_5;
  sf::Text score_6;
  sf::Text score_7;
  sf::Text score_8;
  sf::Text score_9;
  sf::Text score_10;

  //WIN

  //LOSE
  sf::Text game_over_text;
  sf::Text restart_text;

};

#endif // PLATFORMERSFML_TEXT_H

//
// Created by copig on 19/06/2024.
//

#ifndef PLATFORMERSFML_AUDIO_H
#define PLATFORMERSFML_AUDIO_H
#include <SFML/Audio.hpp>


class Audio {

 public:
  Audio();
  ~Audio();
  // SOUNDS
  sf::SoundBuffer menu_sound_note_buffer;
  sf::Sound menu_sound_note;
  sf::SoundBuffer sound_jump_buffer;
  sf::Sound sound_jump;
  sf::SoundBuffer sound_falling_buffer;
  sf::Sound sound_falling;
  sf::Music music_mountain_king;
  sf::SoundBuffer sound_game_over_buffer;
  sf::Sound sound_game_over;
  sf::SoundBuffer sound_escape_buffer;
  sf::Sound sound_escape;
  sf::SoundBuffer sound_air_buffer;
  sf::Sound sound_air;
  sf::SoundBuffer sound_die_buffer;
  sf::Sound sound_die;
};

#endif // PLATFORMERSFML_AUDIO_H

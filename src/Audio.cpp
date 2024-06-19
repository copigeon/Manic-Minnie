//
// Created by copig on 19/06/2024.
//

#include "Audio.h"
#include <iostream>

Audio::Audio()
{
    if (!menu_sound_note_buffer.loadFromFile("Data/Sounds/note_2.wav")) {
      // file cannot be loaded
      std::cout << "Sound note_2 file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    menu_sound_note.setBuffer(menu_sound_note_buffer);

    if (!sound_jump_buffer.loadFromFile("Data/Sounds/jumping_1.ogg")) {
      // file cannot be loaded
      std::cout << "Sound jump file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    sound_jump.setBuffer(sound_jump_buffer);
    sound_jump.setVolume(8);

    if (!sound_falling_buffer.loadFromFile("Data/Sounds/falling.ogg")) {
      // file cannot be loaded
      std::cout << "Sound jump file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    sound_falling.setBuffer(sound_falling_buffer);
    sound_falling.setVolume(8);

    if (!sound_game_over_buffer.loadFromFile("Data/Sounds/game-over.ogg")) {
      // file cannot be loaded
      std::cout << "Sound game_over file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    sound_game_over.setBuffer(sound_game_over_buffer);
    sound_game_over.setVolume(8);

    if (!sound_escape_buffer.loadFromFile("Data/Sounds/escape.ogg")) {
      // file cannot be loaded
      std::cout << "Sound escape file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    sound_escape.setBuffer(sound_escape_buffer);
    sound_escape.setVolume(8);

    if (!sound_air_buffer.loadFromFile("Data/Sounds/air.ogg")) {
      // file cannot be loaded
      std::cout << "Sound sound_air file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    sound_air.setBuffer(sound_air_buffer);
    sound_air.setVolume(8);

    if (!sound_die_buffer.loadFromFile("Data/Sounds/die.wav")) {
      // file cannot be loaded
      std::cout << "Sound die file not found" << std::endl;
    }
    // Create a sound instance and set its buffer
    sound_die.setBuffer(sound_die_buffer);
    sound_die.setVolume(8);

    // Create a sound buffer and load a sound file
    if (!music_mountain_king.openFromFile("Data/Sounds/in-game-tune.ogg")) {
      // file cannot be loaded
      std::cout << "Sound mountain_king file not found" << std::endl;
    }
}

Audio::~Audio()
{

}
//
// Created by copig on 19/06/2024.
//

#include "Text.h"

Text::Text(sf::RenderWindow& window) {

    //LOAD THE TITLE FONT HERE
    if(!title_font.loadFromFile(("Data/Fonts/MANIC_MINER.ttf"))) { std::cout << "font did not load \n"; }
    //LOAD THE STANDARD FONT HERE
    if(!font.loadFromFile(("Data/Fonts/open-sans/OpenSans-Light.ttf"))) { std::cout << "font did not load \n"; }
    //LOAD THE FONT HERE
    if(!basic_font.loadFromFile(("Data/Fonts/zx-spectrum.ttf"))) { std::cout << "font did not load \n"; }


    // CREATE THE MENU TEXT HERE
    splash_text.setString("Press [ Enter ] to Start!");
    splash_text.setFont(font);
    splash_text.setLetterSpacing(2);
    splash_text.setCharacterSize(25);
    splash_text.setOutlineThickness(1);
    splash_text.setOutlineColor(sf::Color::White);
    splash_text.setFillColor((sf::Color::White));
    splash_text.setPosition((((float)window.getSize().x - splash_text.getGlobalBounds().width)/2),window.getSize().y - 150);

    // CREATE THE OPTIONS TEXT HERE
    intro_text.setString(
      "Good Luck!"
      "\n\n\n\n"
      "Watch out for deadly obstructions, crazed\n machinery and animals who dwell within...\n"
      "\n"
      "Safely guide Minnie through each room,\n collecting keys to progress into the mines...\n"
      "\n\n"
      "the bad news is, it's still active and\n doesn't take kindly to intruders...\n"
      "\n"
      "The good news is, the mine machinery has been\n piling up wealth which is there for the taking;\n"
      "\n"
      "Minnie has discovered an automated, abandoned\n for untold centuries, mine in Surbiton.\n"
    );
    intro_text.setFont(title_font);
    intro_text.setCharacterSize(15);
    intro_text.setColor(sf::Color::Black);
    intro_text.setPosition((((float)window.getSize().x - intro_text.getGlobalBounds().width)/2),(0-(intro_text.getGlobalBounds().height-92)));

    intro_text_1.setString("Program: Manic Minnie \xa9 Em Tarr 23079062");
    intro_text_1.setFont(font);
    intro_text_1.setCharacterSize(20);
    intro_text_1.setColor(sf::Color::Black);
    intro_text_1.setPosition(60,82-intro_text_1.getGlobalBounds().height);

    intro_text_2.setString("PRESS [ ENTER ] TO SKIP");
    intro_text_2.setFont(font);
    intro_text_2.setCharacterSize(20);
    intro_text_2.setColor(sf::Color::Black);
    intro_text_2.setPosition(window.getSize().x-(intro_text_2.getGlobalBounds().width+92),window.getSize().y-82);

    //BUILD PLAYING
    ui_top_text_quit.setString("PRESS [ ESC ] FOR OPTIONS MENU");
    ui_top_text_quit.setFont(title_font);
    ui_top_text_quit.setLetterSpacing(2);
    ui_top_text_quit.setCharacterSize(15);
    ui_top_text_quit.setFillColor((sf::Color::Black));
    ui_top_text_quit.setPosition((((float)window.getSize().x - ui_top_text_quit.getGlobalBounds().width)/2),25);

    ui_top_text_controls.setString("[ A to move LEFT ] [ D to move RIGHT ] [ SPACE to JUMP ]");
    ui_top_text_controls.setFont(title_font);
    ui_top_text_controls.setLetterSpacing(2);
    ui_top_text_controls.setCharacterSize(15);
    ui_top_text_controls.setFillColor((sf::Color::Black));
    ui_top_text_controls.setPosition((((float)window.getSize().x - ui_top_text_controls.getGlobalBounds().width)/2),55);

    ui_top_text_music.setString("PRESS [ N and M ] TO DISABLE and ENABLE MUSIC ");
    ui_top_text_music.setFont(title_font);
    ui_top_text_music.setLetterSpacing(2);
    ui_top_text_music.setCharacterSize(15);
    ui_top_text_music.setFillColor((sf::Color::Black));
    ui_top_text_music.setPosition((((float)window.getSize().x - ui_top_text_music.getGlobalBounds().width)/2),85);

    room_name_text.setString("THE ROOM NAME HERE");
    room_name_text.setFont(title_font);
    room_name_text.setCharacterSize(15);
    room_name_text.setColor(sf::Color::Black);
    room_name_text.setPosition((window.getSize().x-room_name_text.getGlobalBounds().width)/2,555);

    air_text.setString("AIR");
    air_text.setFont(title_font);
    air_text.setCharacterSize(20);
    air_text.setColor(sf::Color::White);
    air_text.setPosition(10,578);

    high_score_text.setFont(basic_font);
    high_score_text.setLetterSpacing(2);
    high_score_text.setCharacterSize(16);
    high_score_text.setFillColor((sf::Color::Yellow));
    high_score_text.setPosition(20,620);

    score_text.setFont(basic_font);
    score_text.setLetterSpacing(2);
    score_text.setCharacterSize(16);
    score_text.setFillColor((sf::Color::Yellow));
    score_text.setPosition(window.getSize().x-score_text.getGlobalBounds().width-20,620);

    // CREATE THE OPTIONS TEXT HERE
    options_text.setString("MANIC MINNIE");
    options_text.setFont(title_font);
    options_text.setLetterSpacing(2);
    options_text.setCharacterSize(30);
    options_text.setOutlineThickness(0);
    options_text.setOutlineColor(sf::Color::White);
    options_text.setFillColor((sf::Color::White));
    options_text.setPosition((((float)window.getSize().x - options_text.getGlobalBounds().width)/2),280);

    options_text_1.setString("starring:");
    options_text_1.setFont(title_font);
    options_text_1.setLetterSpacing(2);
    options_text_1.setCharacterSize(15);
    options_text_1.setOutlineThickness(0);
    options_text_1.setOutlineColor(sf::Color::White);
    options_text_1.setFillColor((sf::Color::White));
    options_text_1.setPosition((((float)window.getSize().x - options_text_1.getGlobalBounds().width)/2),325);

    options_text_2.setString("MINNIE } MINER");
    options_text_2.setFont(title_font);
    options_text_2.setLetterSpacing(2);
    options_text_2.setCharacterSize(25);
    options_text_2.setOutlineThickness(0);
    options_text_2.setOutlineColor(sf::Color::White);
    options_text_2.setFillColor((sf::Color::White));
    options_text_2.setPosition((((float)window.getSize().x - options_text_2.getGlobalBounds().width)/2),350);

    options_enter_play.setString("Press [ENTER] to play!");
    options_enter_play.setFont(font);
    options_enter_play.setLetterSpacing(2);
    options_enter_play.setCharacterSize(30);
    options_enter_play.setOutlineThickness(0);
    options_enter_play.setOutlineColor(sf::Color::White);
    options_enter_play.setFillColor((sf::Color::White));
    options_enter_play.setPosition((((float)window.getSize().x - options_enter_play.getGlobalBounds().width)/2),450);

    //GAME OVER
    game_over_text.setString("GAME        OVER");
    game_over_text.setFont(title_font);
    game_over_text.setLetterSpacing(4);
    game_over_text.setCharacterSize(25);
    game_over_text.setFillColor((sf::Color::White));
    game_over_text.setPosition((((float)window.getSize().x - game_over_text.getGlobalBounds().width)/2),250);

    restart_text.setString("PRESS [ ENTER ] TO PLAY AGAIN OR [ ESC ] FOR OPTIONS MENU");
    restart_text.setFont(title_font);
    restart_text.setLetterSpacing(2);
    restart_text.setCharacterSize(15);
    restart_text.setFillColor((sf::Color::White));
    restart_text.setPosition((((float)window.getSize().x - restart_text.getGlobalBounds().width)/2),(float)window.getSize().y-50);

    //MAP CAVERN
    room_name_text.setString("Central Cavern");
    room_name_text.setPosition(((float)window.getSize().x-room_name_text.getGlobalBounds().width)/2,555);

    //MAP COLD ROOM
    room_name_text.setString("The Cold Room");
    room_name_text.setPosition(((float)window.getSize().x-room_name_text.getGlobalBounds().width)/2,555);

    //high scores
    player_name.setFont(font);
    player_name.setLetterSpacing(4);
    player_name.setCharacterSize(25);
    player_name.setFillColor((sf::Color::White));
    player_name.setPosition((((float)window.getSize().x - player_name.getGlobalBounds().width)/2),360);

    //FINALE

    well_done.setString("You helped Minnie find her way home!");
    well_done.setFont(title_font);
    well_done.setLetterSpacing(4);
    well_done.setCharacterSize(20);
    well_done.setFillColor((sf::Color::White));
    well_done.setPosition((((float)window.getSize().x - well_done.getGlobalBounds().width)/2),250);

    new_high_score_1.setString("You have a new high score!");
    new_high_score_1.setFont(font);
    new_high_score_1.setLetterSpacing(4);
    new_high_score_1.setCharacterSize(16);
    new_high_score_1.setFillColor((sf::Color::White));
    new_high_score_1.setPosition((((float)window.getSize().x - new_high_score_1.getGlobalBounds().width)/2),280);

    new_high_score_2.setString("Enter your initials using the [UP][DOWN][LEFT][RIGHT] arrow keys.");
    new_high_score_2.setFont(font);
    new_high_score_2.setLetterSpacing(4);
    new_high_score_2.setCharacterSize(16);
    new_high_score_2.setFillColor((sf::Color::White));
    new_high_score_2.setPosition((((float)window.getSize().x - new_high_score_2.getGlobalBounds().width)/2),305);

    new_high_score_3.setString("Hit [ENTER] to record your victory on the leader board!");
    new_high_score_3.setFont(font);
    new_high_score_3.setLetterSpacing(4);
    new_high_score_3.setCharacterSize(16);
    new_high_score_3.setFillColor((sf::Color::White));
    new_high_score_3.setPosition((((float)window.getSize().x - new_high_score_3.getGlobalBounds().width)/2),330);

    return_to_options.setString("Press [ENTER] to return to the [OPTIONS] menu!");
    return_to_options.setFont(font);
    return_to_options.setLetterSpacing(4);
    return_to_options.setCharacterSize(20);
    return_to_options.setFillColor((sf::Color::White));
    return_to_options.setPosition((((float)window.getSize().x - return_to_options.getGlobalBounds().width)/2),290);

    score_1.setFont(font);
    score_1.setLetterSpacing(4);
    score_1.setCharacterSize(20);
    score_1.setFillColor((sf::Color::White));

}

Text::~Text()
{

}
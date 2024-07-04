
#include "Game.h"
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>


Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));

  //Audio object contains all sounds and music for game
  audio = new Audio;
  //Text object contacts all block text elements for game
  text = new Text(window);

  player = new Player;
  gate = new GameObject;
  platform_array = new sf::RectangleShape[15];
  key_array = new GameObject[5];
  enemy_array = new GameObject[2];
  hazards_array = new GameObject[10];

  //decay playforms
  platform_1 = new Platform[10];
  platform_2 = new Platform[10];
  platform_3 = new Platform[10];
  platform_4 = new Platform[10];
  platform_5 = new Platform[10];
  platform_6 = new Platform[10];
  platform_7 = new Platform[10];
  platform_8 = new Platform[10];
  platform_9 = new Platform[10];
  platform_10 = new Platform[10];

  map_the_cold_room = new Map;
  map_central_cavern = new Map;
  map_container = new Map;

}

Game::~Game()
{
  if(audio != nullptr){delete audio; audio = nullptr;}
  if(text != nullptr){delete text; text = nullptr;}


  if(player != nullptr){delete player; player = nullptr;}
  if(gate != nullptr){delete gate; gate = nullptr;}
  if(key_array != nullptr){delete key_array; key_array = nullptr;}
  if(enemy_array != nullptr){delete enemy_array; enemy_array = nullptr;}
  if(hazards_array != nullptr){delete hazards_array; hazards_array = nullptr;}
  if(platform_array != nullptr){delete platform_array; platform_array = nullptr;}
  if(platform_1 != nullptr){delete platform_1; platform_1 = nullptr;}
  if(platform_2 != nullptr){delete platform_2; platform_2 = nullptr;}
  if(platform_3 != nullptr){delete platform_3; platform_3 = nullptr;}
  if(platform_4 != nullptr){delete platform_4; platform_4 = nullptr;}
  if(platform_5 != nullptr){delete platform_5; platform_5 = nullptr;}
  if(platform_6 != nullptr){delete platform_6; platform_6 = nullptr;}
  if(platform_7 != nullptr){delete platform_7; platform_7 = nullptr;}
  if(platform_8 != nullptr){delete platform_8; platform_8 = nullptr;}
  if(platform_9 != nullptr){delete platform_9; platform_9 = nullptr;}
  if(platform_10 != nullptr){delete platform_10; platform_10 = nullptr;}
  if(map_central_cavern != nullptr){delete map_central_cavern; map_central_cavern = nullptr;}
  if(map_the_cold_room != nullptr){delete map_the_cold_room; map_the_cold_room = nullptr;}
  if(map_container != nullptr){delete map_container; map_container = nullptr;}
}

bool Game::init()
{
  initMaps();

  buildSplash();

  buildIntro();

  buildOptions();

  buildMenuSong();

  buildPlaying();

  buildLose();

  buildWin();

  initPlayer();

  mapSequencer();

  buildMapTest();

  return true;
}

void Game::update(float dt)
{
  switch (game_state)
  {
    case SPLASH:
      //std::cout << "UPDATE SPLASH" << std::endl;
      window.clear(sf::Color::Black);

      break;
    case INTRO:
      //std::cout << "UPDATE INTRO" << std::endl;
      window.clear(sf::Color::White);
      intro_timer_scroll -= dt;
      if(intro_timer_scroll < 0)
      {
        text->intro_text.setPosition(text->intro_text.getPosition().x,text->intro_text.getPosition().y+5);
        intro_timer_scroll = 0.2;
      }
      intro_timer -= dt;
      if (intro_timer < 0)
      {
        if(!background_flag)
        {
          background_flag = true;
          if (!bar_texture.loadFromFile("Data/Images/bar.png"))
          {
            std::cout << "bar_1 texture did not load\n";
          }
          if (!top_bar_texture.loadFromFile("Data/Images/top_bar.png"))
          {
            std::cout << "top_bar texture did not load\n";
          }
          if (!bottom_bar_texture.loadFromFile("Data/Images/bottom_bar.png"))
          {
            std::cout << "bottom_bar texture did not load\n";
          }
        }
        else
        {
          background_flag = false;
          if (!bar_texture.loadFromFile("Data/Images/bar_1.png"))
          {
            std::cout << "bar_1 texture did not load\n";
          }
          if (!top_bar_texture.loadFromFile("Data/Images/top_bar_1.png"))
          {
            std::cout << "top_bar_1 texture did not load\n";
          }
          if (!bottom_bar_texture.loadFromFile("Data/Images/bottom_bar_1.png"))
          {
            std::cout << "bottom_bar_1 texture did not load\n";
          }
        }
        intro_timer = 1;
      }
      if(text->intro_text.getPosition().y > window.getSize().y-82) {
        game_state = GameState::OPTIONS;
      }
      break;
    case PLAYING:
      //std::cout << "UPDATE PLAYING" << std::endl;
      //DEFINE MAP SPECIFICS
      defineMapSpecifics();

      window.clear(sf::Color::Black);
      animateLife(life_animation_clock);

      for(int i = 0; i < map_enemies; i++)
      {
        enemy_array[i].moveEnemy(
          enemy_array[i], dt, enemy_array[i].getMoveDirection().x);

        // USING X AND Y in get movement limits to store the two EXTENTS of movement
        if (
          enemy_array[i].getSprite()->getPosition().x +
            enemy_array[i].getSprite()->getGlobalBounds().width >
          enemy_array[i].getMovementLimits().y)
        {
          enemy_array[i].setMoveDirection(sf::Vector2f(-1, 0));
        }
        else if (
          enemy_array[i].getSprite()->getPosition().x <
          enemy_array[i].getMovementLimits().x)
        {
          enemy_array[i].setMoveDirection(sf::Vector2f(1, 0));
        }
      }

      player->playerMove(dt, *player, animation_clock);
      if(player->is_falling && audio->sound_falling.getStatus() != sf::Sound::Status::Playing) {
        audio->sound_falling.play();
      }
      if(player->checkRectCollision(*player,map_left_wall)) {
        player->getSprite()->move(+1 * player->getSpeed() * dt, 0);
        if(player->is_jumping) { player->is_falling = true; player->is_jumping = false; }
      }
      if(player->checkRectCollision(*player,map_right_wall)) {
        player->getSprite()->move(-1 * player->getSpeed() * dt, 0);
        if(player->is_jumping) { player->is_falling = true; player->is_jumping = false; }
      }

      checkPlatformCollide(dt);

      if(mapstate == MapState::CENTRAL_CAVERN)
      {
        checkDecayPlatformCollide(platform_1);
        checkDecayPlatformCollide(platform_2);
        checkDecayPlatformCollide(platform_3);
      }
      if(mapstate == MapState::THE_COLD_ROOM)
      {
        checkDecayPlatformCollide(platform_1);
        checkDecayPlatformCollide(platform_2);
        checkDecayPlatformCollide(platform_3);
        checkDecayPlatformCollide(platform_4);
        checkDecayPlatformCollide(platform_5);
        checkDecayPlatformCollide(platform_6);
        checkDecayPlatformCollide(platform_7);
        checkDecayPlatformCollide(platform_8);
        checkDecayPlatformCollide(platform_9);
        checkDecayPlatformCollide(platform_10);
      }

      //check collision with keys and set to inactive, plus one to player keys total
      for(int i = 0; i < map_keys; i++)
      {
        if(key_array[i].isActive()) {
        if(player->checkEnemyCollison(*player, key_array[i]))
        {
            key_array[i].setIsActive(false);
            player->setKeys(player->getKeys() + 1);
        }
        }
      }

      // flash the key sprites
      if (key_animation_clock.getElapsedTime().asSeconds() > 0.2)
        {
        if (key_frame > 6) { key_frame = 0; }
        for(int i = 0; i < map_keys; i++)
          {
            key_array[i].getSprite()->setColor(key_colours[key_frame]);
          }
          key_animation_clock.restart();
          key_frame++;
          if(key_frame == 1 || key_frame == 4)
          {
            if (!elevator_texture_1.loadFromFile("Data/Images/elevator_1.png"))
            {
            std::cout << "elevator_texture_1 texture did not load\n";
            }
          }
          if (key_frame == 2 || key_frame == 5)
          {
            if (!elevator_texture_1.loadFromFile("Data/Images/elevator_2.png"))
            {
            std::cout << "elevator_texture_1 texture did not load\n";
            }
          }
          if (key_frame == 3 || key_frame == 6) {
            if (!elevator_texture_1.loadFromFile("Data/Images/elevator_3.png"))
            {
            std::cout << "elevator_texture_1 texture did not load\n";
            }
          }
        }

      // if have all keys enable gate
      if (player->getKeys() == 5 ) {
          //CHANGE THIS TO map_keys
          gate->setIsActive(false);
      }

      // flash the gate sprite when ready to enter ie all five keys
      if (!gate->isActive()) {
          if(flash)
          {
            gate->getSprite()->setColor(sf::Color::Yellow);
            flash = false;
          }
          else
          {
            gate->getSprite()->setColor(sf::Color::Red);
            flash = true;
          }
      }

      // check gate collision and change state if no longer active ie all five keys
      if(player->checkEnemyCollison(*player, *gate)) {
        if(!gate->isActive())
        {
            audio->music_mountain_king.stop();
            audio->sound_jump.stop();
            audio->sound_falling.stop();
            audio->sound_air.play();
            game_state = GameState::GAME_WON;
        }
      }

      // check collisions with enemy and hazards
      for(int i = 0; i < map_enemies; i++)
      {
        if (player->checkEnemyCollison(*player, enemy_array[i]))
        {
            playerDie();
        }
      }
      for(int i = 0; i < map_hazards; i++)
      {
        if (player->checkEnemyCollison(*player, hazards_array[i]))
        {
            playerDie();
        }
      }

      //decrease air bar
      air_bar -= 0.05;
      //air_bar -= 12;
      air.setSize(sf::Vector2f(air_bar,air.getGlobalBounds().height ));

      //check to see if player lives all gone
      if((player->getLives() == 0) or (air_bar <= 0)) {
        audio->music_mountain_king.stop();
        audio->sound_jump.stop();
        audio->sound_falling.stop();
        audio->sound_game_over.play();
        game_state = GameState::GAME_LOST;
      }

      switch(mapstate)
      {
        case MapState::CENTRAL_CAVERN:
            setDecayPlatformColours(platform_1, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_2, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_3, map_red, map_green, map_blue);
            break;
        case MapState::THE_COLD_ROOM:
            setDecayPlatformColours(platform_1, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_2, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_3, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_4, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_5, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_6, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_7, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_8, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_9, map_red, map_green, map_blue);
            setDecayPlatformColours(platform_10, map_red, map_green, map_blue);
            break;
      }

      break;

    case OPTIONS:
      //std::cout << "UPDATE OPTIONS" << std::endl;
      window.clear(sf::Color::Black);
      menu_timer -= dt;
      if (menu_timer < 0)
      {
        key_1.setPosition((float)song[0][menu_song_note]*30, (float)window.getSize().y - 88);
        key_2.setPosition((float)song[1][menu_song_note]*30, (float)window.getSize().y - 88);
        audio->menu_sound_note.setPitch((float)(song[0][menu_song_note]*0.05)+1);
        if(song[0][menu_song_note] != 33) { audio->menu_sound_note.play(); }
        audio->menu_sound_note.setPitch((float)(song[1][menu_song_note]*0.05)+1);
        if(song[1][menu_song_note] != 33) { audio->menu_sound_note.play(); }
        if (menu_song_note < 68) { menu_song_note++; } else { menu_song_note = 0; }
        menu_timer = 0.3;
      }

      break;
    case GAME_WON:
      //std::cout << "UPDATE WON" << std::endl;
        if (air_bar > 0)
        {
            player->setScore(player->getScore() + 4);
            air_bar -= 4;
            air.setSize(sf::Vector2f(air_bar, air.getGlobalBounds().height));
            text->score_text.setString("Score " + std::to_string(player->getScore()));
            text->score_text.setPosition(window.getSize().x-text->score_text.getGlobalBounds().width-20,620);
        }
        if(air_bar < 0)
        {
            resetPlayer();
            player->setKeys(0);
            air_bar = 800;
            current_map ++;
            if(current_map < 2)
            {
            mapSequencer();
            audio->music_mountain_king.play();
            game_state = GameState::PLAYING;
            }
            else {
              getHighScores(high_scores_array);
              sortHighScores(high_scores_array);
              game_state = GameState::GAME_FINALE;
            }
        }
      break;
    case GAME_LOST:
      //std::cout << "UPDATE LOST" << std::endl;
      if(game_over_counter > 5) { game_over_counter = 0; }

      if(lose_boot_sprite.getPosition().y+lose_boot_sprite.getGlobalBounds().height < lose_podium_sprite.getPosition().y) {
        lose_boot_sprite.setPosition(lose_boot_sprite.getPosition().x, lose_boot_sprite.getPosition().y+5);
        lose_leg_rect.setSize(sf::Vector2f(16,lose_leg_rect.getSize().y+2));
        lose_leg_rect.setTextureRect(sf::IntRect(0, 0, 16, lose_leg_rect.getTextureRect().height+2));
        if (animation_clock.getElapsedTime().asSeconds() > 0.2)
        {
          background_block.setFillColor(game_over_colour[game_over_counter]);
          text->game_over_text.setFillColor(game_over_colour[game_over_counter]);
          game_over_counter++;
          animation_clock.restart();
        }
      }
      else {
        if (animation_clock.getElapsedTime().asSeconds() > 0.05)
        {
          text->game_over_text.setFillColor(game_over_colour[game_over_counter]);
          game_over_counter++;
          animation_clock.restart();
        }
        background_block.setFillColor(sf::Color::Black);
      }
      break;
    case QUIT:
      window.clear(sf::Color::Black);
      //std::cout << "UPDATE QUIT" << std::endl;
      break;
    case GAME_FINALE:
      //std::cout << "UPDATE FINALE" << std::endl;
      window.clear(sf::Color::Black);
      getHighScores(high_scores_array);
      sortHighScores(high_scores_array);
      updateHighScores(high_scores_array, player);
      buildFinale();
      break;
  }
}

void Game::render()
{
  switch (game_state)
  {
    case SPLASH:
      //std::cout << "RENDER SPLASH" << std::endl;
      window.draw(splash_background);
      window.draw(text->splash_text);

      break;
    case INTRO:
      //std::cout << "RENDER INTRO" << std::endl
      window.draw(text->intro_text);
      window.draw(top_bar);
      window.draw(bottom_bar);
      window.draw(left_bar);
      window.draw(right_bar);
      window.draw(text->intro_text_1);
      window.draw(text->intro_text_2);
      break;
    case PLAYING:
      defineMapSpecifics();
      //std::cout << "RENDER PLAYING" << std::endl;
      window.draw(background_block);
      window.draw(ui_block_top);
      window.draw(text->ui_top_text_controls);
      window.draw(text->ui_top_text_quit);
      window.draw(text->ui_top_text_music);
      window.draw(ui_block_bottom);
      window.draw(map_left_wall);
      window.draw(map_right_wall);

      window.draw(room_name_bar);
      window.draw(air_green);
      window.draw(air_red);
      window.draw(air);
      window.draw(text->room_name_text);
      window.draw(text->air_text);

      //window.draw(platform_array[0]);

      for (int i = 0; i < map_platforms; i++)
      {
        window.draw(platform_array[i]);
      }

      window.draw(text->high_score_text);
      window.draw(text->score_text);

      for (int i = 0; i < map_enemies; i++) {
        window.draw(*enemy_array[i].getSprite());
      }

      for (int i = 0; i < map_keys; i++) {
        if(key_array[i].isActive())
        {
          window.draw(*key_array[i].getSprite());
        }
      }

      window.draw(*gate->getSprite());
      window.draw(*player->getSprite());


      //if cavern
      if(mapstate == MapState::CENTRAL_CAVERN)
      {
        drawDecayPlatforms(platform_1, 10);
        drawDecayPlatforms(platform_2, 5);
        drawDecayPlatforms(platform_3, 4);
      }

      //if coldstore
      if(mapstate == MapState::THE_COLD_ROOM)
      {
        drawDecayPlatforms(platform_1, 5);
        drawDecayPlatforms(platform_2, 5);
        drawDecayPlatforms(platform_3, 5);
        drawDecayPlatforms(platform_4, 2);
        drawDecayPlatforms(platform_5, 2);
        drawDecayPlatforms(platform_6, 2);
        drawDecayPlatforms(platform_7, 2);
        drawDecayPlatforms(platform_8, 2);
        drawDecayPlatforms(platform_9, 2);
        drawDecayPlatforms(platform_10, 4);
      }

      for (int i = 0; i < map_hazards; i++) {
        window.draw(*hazards_array[i].getSprite());
      }

      for (int i = 0; i < player->getLives(); i++) {
        window.draw(life_sprite[i]);
      }

      break;
    case OPTIONS:
      //std::cout << "RENDER OPTIONS" << std::endl;
      window.draw(options_background);
      window.draw(text->options_text);
      window.draw(text->options_text_1);
      window.draw(text->options_text_2);
      window.draw(key_1);
      window.draw(key_2);
      window.draw(text->options_enter_play);
      break;
    case GAME_WON:
      //std::cout << "RENDER WON" << std::endl;
      window.draw(background_block);
      window.draw(ui_block_bottom);

      window.draw(room_name_bar);
      window.draw(air_green);
      window.draw(air_red);
      window.draw(air);
      window.draw(text->room_name_text);
      window.draw(text->air_text);

      window.draw(text->high_score_text);
      window.draw(text->score_text);

      window.draw(*player->getSprite());

      for (int i = 0; i < player->getLives(); i++) {
        window.draw(life_sprite[i]);
      }
      break;
    case GAME_LOST:
      //std::cout << "RENDER LOST" << std::endl;
      window.draw(background_block);
      window.draw(ui_block_bottom);
      window.draw(map_left_wall);
      window.draw(map_right_wall);

      window.draw(room_name_bar);
      window.draw(air_green);
      window.draw(air_red);
      window.draw(air);
      window.draw(text->room_name_text);
      window.draw(text->air_text);

      window.draw(platform_array[0]);

      window.draw(text->high_score_text);
      window.draw(text->score_text);

      window.draw(lose_boot_sprite);
      window.draw(lose_leg_rect);
      window.draw(lose_podium_sprite);
      window.draw(text->game_over_text);
      window.draw(text->restart_text);

      if(lose_boot_sprite.getPosition().y+lose_boot_sprite.getGlobalBounds().height < lose_player_sprite.getPosition().y) {
        window.draw(lose_player_sprite);
      }

      break;
    case QUIT:
      //std::cout << "RENDER QUIT" << std::endl;
      break;
    case GAME_FINALE:
      //std::cout << "RENDER FINALE" << std::endl;
      window.draw(win_banner);
      window.draw(text->well_done);

      //std::cout << high_scores_array[0][1];
      //std::cout << high_scores_array[0][0];
      //std::cout << "LOOP";

      if(player->getScore() > stoi(high_scores_array[0][1]))
      {
        window.draw(text->new_high_score_1);
        window.draw(text->new_high_score_2);
        window.draw(text->new_high_score_3);
        window.draw(text->player_name);
      }
      else {
        window.draw(text->return_to_options);
      }
      window.draw(text->score_1);

      break;
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  switch (game_state)
  {
    case SPLASH:
      std::cout << "MOUSE CLICKED SPLASH" << std::endl;
      break;
    case INTRO:
      std::cout << "MOUSE CLICKED INTRO" << std::endl;
      break;
    case PLAYING:
      std::cout << "MOUSE CLICKED PLAYING" << std::endl;
      break;
    case OPTIONS:
      std::cout << "MOUSE CLICKED OPTIONS" << std::endl;
      break;
    case GAME_WON:
      std::cout << "MOUSE CLICKED WON" << std::endl;
      break;
    case GAME_LOST:
      std::cout << "MOUSE CLICKED LOST" << std::endl;
      break;
    case QUIT:
      std::cout << "MOUSE CLICKED QUIT" << std::endl;
      break;
    case GAME_FINALE:
      std::cout << "MOUSE CLICKED FINALE" << std::endl;
      break;
  }
}

void Game::keyPressed(sf::Event event)
{
  switch (game_state)
  {
    case SPLASH:
      //std::cout << "KEY PRESSED SPLASH" << std::endl;
      if (event.key.code == sf::Keyboard::Enter)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          game_state = GameState::INTRO;
        }
      }
      break;
    case INTRO:
      //std::cout << "KEY PRESSED INTRO" << std::endl;
      if (event.key.code == sf::Keyboard::Enter)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          game_state = GameState::OPTIONS;
        }
      }
      break;
    case PLAYING:
      //std::cout << "KEY PRESSED PLAYING" << std::endl;
      //PLAYER MOVEMENT
      if(event.key.code == sf::Keyboard::A)
      {
          if (event.type == sf::Event::KeyPressed)
          {
            if (!player->move_left)
            {
              do
              {
                // move player right
                player->move_left = true;
              } while (!player->move_left);
            }
          }
        else if (event.type == sf::Event::KeyReleased)
        {
          // player stop
          player->move_left = false;
        }
      }

      if(event.key.code == sf::Keyboard::D)
      {
        if (event.type == sf::Event::KeyPressed)
        {

            if (!player->move_right)
            {
              do
              {
                // move player right
                player->move_right = true;
              } while (!player->move_right);
            }
            }
        else if (event.type == sf::Event::KeyReleased)
        {
          //player stop
          this->player->move_right = false;
        }
      }

      if (event.key.code == sf::Keyboard::Space)
      {
        if(!player->is_jumping && !player->is_falling)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              player->is_jumping = true;
              player->is_falling = false;
              //set player velocity (up screen) to -12
              player->y_velocity = player->y_velocity_modifier;
              if(player->move_right)
              {
                player->jump_right = true;
                audio->sound_jump.play();
                //std::cout << "JUMPING RIGHT" << std::endl;

              }
              else if(player->move_left)
              {
                player->jump_left = true;
                audio->sound_jump.play();
                //std::cout << "JUMPING LEFT" << std::endl;

              }
              else
              {
                audio->sound_jump.play();
                //std::cout << "JUMPING UP" << std::endl;
              }
          }
        }
      }
      if (event.key.code == sf::Keyboard::M)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          audio->music_mountain_king.stop();
        }
      }
      if (event.key.code == sf::Keyboard::N)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          audio->music_mountain_king.play();
        }
      }
      if (event.key.code == sf::Keyboard::Escape)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          resetGame();
          audio->music_mountain_king.stop();
          game_state = GameState::OPTIONS;
        }
      }
      break;
    case OPTIONS:
      //std::cout << "KEY PRESSED OPTIONS" << std::endl;
      if (event.key.code == sf::Keyboard::Enter)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          resetGame();
          audio->music_mountain_king.play();
          game_state = GameState::PLAYING;
        }
      }
      break;
    case GAME_WON:
      //std::cout << "KEY PRESSED WON" << std::endl;
      break;
    case GAME_LOST:
      //std::cout << "KEY PRESSED LOST" << std::endl;
      //std::cout << "KEY PRESSED INTRO" << std::endl;
      if (event.key.code == sf::Keyboard::Enter)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          resetGame();
          resetPlayer();
          audio->music_mountain_king.play();
          game_state = GameState::PLAYING;
        }
      }
      if (event.key.code == sf::Keyboard::Escape)
      {
        if (event.type == sf::Event::KeyPressed)
        {
          resetGame();
          resetPlayer();
          game_state = GameState::OPTIONS;
        }
      }
      break;
    case QUIT:
      //std::cout << "KEY PRESSED QUIT" << std::endl;
      break;
    case GAME_FINALE:
      //std::cout << "KEY PRESSED FINALE" << std::endl;
      if(player->getScore() > stoi(high_scores_array[0][1]))
      {
        if (event.key.code == sf::Keyboard::Up)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              player_name_scroll++;
              if (player_name_scroll == 0)
              {
                player_name_scroll = 25;
              }
              else if (player_name_scroll == 25)
              {
                player_name_scroll = 0;
              }
          }
        }
        if (event.key.code == sf::Keyboard::Down)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              player_name_scroll--;
              if (player_name_scroll == 0)
              {
                player_name_scroll = 25;
              }
              else if (player_name_scroll == 25)
              {
                player_name_scroll = 0;
              }
          }
        }
        if (event.key.code == sf::Keyboard::Right)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              player_name_letter++;
              if (player_name_letter > 2)
              {
                player_name_letter = 2;
              }
              switch (player_name_letter)
              {
                case 0:
                  player_name_scroll = player_name_position_1;
                  break;
                case 1:
                  player_name_scroll = player_name_position_2;
                  break;
                case 2:
                  player_name_scroll = player_name_position_3;
                  break;
              }
          }
        }
        if (event.key.code == sf::Keyboard::Left)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              player_name_letter--;
              if (player_name_letter < 0)
              {
                player_name_letter = 0;
              }
              switch (player_name_letter)
              {
                case 0:
                  player_name_scroll = player_name_position_1;
                  break;
                case 1:
                  player_name_scroll = player_name_position_2;
                  break;
                case 2:
                  player_name_scroll = player_name_position_3;
                  break;
              }
          }
        }
        if (event.key.code == sf::Keyboard::Enter)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              high_scores_array[0][0] = player_name_entry;
              high_scores_array[0][1] = std::to_string(player->getScore());
              updateHighScores(high_scores_array, player);
              sortHighScores(high_scores_array);
              player->setScore(0);
          }
        }
      }
      else {
        if (event.key.code == sf::Keyboard::Enter)
        {
          if (event.type == sf::Event::KeyPressed)
          {
              resetGame();
              resetPlayer();
              game_state = GameState::OPTIONS;
          }
        }
      }
      break;
  }
}

void Game::resetGame() {
  initPlayer();
  player->sprite_texture_rect = sf::IntRect (0,0,8,16);
  player->getSprite()->setTextureRect(player->sprite_texture_rect);
  player->getSprite()->setPosition(80, platform_array[0].getPosition().y-player->getSprite()->getGlobalBounds().height);

  player->setScore(0);
  text->score_text.setString("Score " + std::to_string(player->getScore()));

  getHighScores(high_scores_array);
  sortHighScores(high_scores_array);
  text->high_score_text.setString("High Score: " + high_scores_array[9][1]);

  player->setLives(3);
  current_map = 0;
  mapSequencer();
  buildLose();
}

void Game::resetPlayer() {
  player->sprite_texture_rect = sf::IntRect (0,0,8,16);
  player->getSprite()->setTextureRect(player->sprite_texture_rect);
  player->getSprite()->setPosition(80, platform_array[0].getPosition().y-player->getSprite()->getGlobalBounds().height);
  player->move_left = false;
  player->move_right = false;
  player->is_jumping = false;
  player->is_falling = false;
}

void Game::initPlayer() {
  //initialise an instance of the player
  player->sprite_rect_pos[0][0] = sf::Vector2f(0,8);;
  player->sprite_rect_pos[0][1] = sf::Vector2f(19,6);;
  player->sprite_rect_pos[0][2] = sf::Vector2f(36,8);;
  player->sprite_rect_pos[0][3] = sf::Vector2f(53,10);;

  player->sprite_rect_pos[1][0] = sf::Vector2f(65,10);;
  player->sprite_rect_pos[1][1] = sf::Vector2f(84,8);;
  player->sprite_rect_pos[1][2] = sf::Vector2f(103,6);;
  player->sprite_rect_pos[1][3] = sf::Vector2f(120,8);;

  player->initSprite(player->texture, "Data/Images/sprite_sheet.png");
  player->sprite_texture_rect = sf::IntRect (0,0,8,16);
  player->getSprite()->setTextureRect(player->sprite_texture_rect);
  player->getSprite()->setScale(2.5,2.5);
  player->getSprite()->setPosition(80, platform_array[0].getPosition().y-player->getSprite()->getGlobalBounds().height);
  player->setScore(0);
  player->move_left = false;
  player->move_right = false;
}

void Game::buildSplash() {

  //LOAD MENU BACKGROUND TEXTURE
  if(!splash_background_texture.loadFromFile("Data/Images/menu_background.png")) {
    std::cout << "Background Menu texture did not load\n";
  }
  splash_background.setTexture(splash_background_texture);
  splash_background.setPosition(sf::Vector2f((window.getSize().x/2)-(splash_background_texture.getSize().x/2),(window.getSize().y/2)-(splash_background_texture.getSize().y/2)-50));
}

void Game::buildIntro() {
  if(!top_bar_texture.loadFromFile("Data/Images/top_bar.png")) {
    std::cout << "Background Menu texture did not load\n";
  }
  top_bar_texture.setRepeated(true);
  top_bar.setSize(sf::Vector2f((float)window.getSize().x,92 ));
  top_bar.setPosition(0,0);
  top_bar.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 92));
  top_bar.setTexture(&top_bar_texture);

  if(!bottom_bar_texture.loadFromFile("Data/Images/bottom_bar.png")) {
    std::cout << "Background Menu texture did not load\n";
  }
  bottom_bar_texture.setRepeated(true);
  bottom_bar.setSize(sf::Vector2f((float)window.getSize().x,92 ));
  bottom_bar.setPosition(0,(float)window.getSize().y-bottom_bar.getSize().y);
  bottom_bar.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 92));
  bottom_bar.setTexture(&bottom_bar_texture);

  if(!bar_texture.loadFromFile("Data/Images/bar.png")) {
    std::cout << "Background Menu texture did not load\n";
  }
  bar_texture.setRepeated(true);
  left_bar.setSize(sf::Vector2f(50,(float)window.getSize().y));
  left_bar.setPosition((float)0,0);
  left_bar.setTextureRect(sf::IntRect(0, 0, 50, window.getSize().y));
  left_bar.setTexture(&bar_texture);

  right_bar.setSize(sf::Vector2f(50,(float)window.getSize().y ));
  right_bar.setPosition((float)window.getSize().x-right_bar.getSize().x,0);
  right_bar.setTextureRect(sf::IntRect(0, 0, 50, window.getSize().y));
  right_bar.setTexture(&bar_texture);
}

void Game::buildPlaying() {

  if(!sprite_sheet.loadFromFile("Data/Images/sprite_sheet.png")) {
    std::cout << "Sprite sheet texture did not load\n";
  }

  if(!wall_texture.loadFromFile("Data/Images/cavern_wall.png")) {
    std::cout << "cavern_room_wall_texture texture did not load\n";
  }
  wall_texture.setRepeated(true);

  for (int i = 0; i < player->getLives(); i++)
  {
    life_sprite[i].setTexture(sprite_sheet);
    life_texture_rect = sf::IntRect(0, 0, 8, 16);
    life_sprite[i].setTextureRect(life_texture_rect);
    life_sprite[i].setPosition(20, 660);
    life_sprite[i].setScale(2.5, 2.5);
    life_sprite[i].setColor(sf::Color::Cyan);
  }
  for (int j = 1; j < player->getLives(); j++)
  {
    life_sprite[j].setPosition(life_sprite[j-1].getPosition().x+32, 660);
  }

  room_name_bar.setSize(sf::Vector2f(window.getSize().x,25 ));
  room_name_bar.setFillColor(sf::Color(192,192,0,255));
  room_name_bar.setPosition(0,550);

  air_green.setSize(sf::Vector2f(window.getSize().x,25 ));
  air_green.setFillColor(sf::Color::Green);
  air_green.setPosition(0,575);

  air_red.setSize(sf::Vector2f(300,25 ));
  air_red.setFillColor(sf::Color::Red);
  air_red.setPosition(0,575);

  air.setSize(sf::Vector2f(air_bar,15 ));
  air.setFillColor(sf::Color::White);
  air.setPosition(100,580);

  map_left_wall.setSize(sf::Vector2f (25,room_name_bar.getPosition().y));
  map_left_wall.setPosition(0,0);
  map_left_wall.setTextureRect(sf::IntRect(0, 0, 25, (int)room_name_bar.getPosition().y));
  map_left_wall.setTexture(&wall_texture);

  map_right_wall.setSize(sf::Vector2f(25,room_name_bar.getPosition().y));
  map_right_wall.setPosition(window.getSize().x-map_right_wall.getGlobalBounds().width,0);
  map_right_wall.setTextureRect(sf::IntRect(0, 0, 25, (int)room_name_bar.getPosition().y));
  map_right_wall.setTexture(&wall_texture);

  ui_block_bottom.setSize(sf::Vector2f(window.getSize().x,200));
  ui_block_bottom.setPosition(0,room_name_bar.getPosition().y+room_name_bar.getGlobalBounds().height);
  ui_block_bottom.setFillColor(sf::Color::Black);

  ui_block_top.setSize(sf::Vector2f(window.getSize().x,120));
  ui_block_top.setPosition(0,0);
  ui_block_top.setFillColor(sf::Color(192,192,0,255));

  audio->music_mountain_king.setVolume(6);
  audio->music_mountain_king.setLoop(true);

  getHighScores(high_scores_array);
  sortHighScores(high_scores_array);
  text->high_score_text.setString("High Score: " + high_scores_array[9][1]);

  text->score_text.setString("Score " + std::to_string(player->getScore()));
}

void Game::buildOptions() {
  //LOAD OPTIONS BACKGROUND TEXTURE
  if(!options_background_texture.loadFromFile("Data/Images/options_background.png")) {
    std::cout << "Background Menu texture did not load\n";
  }
  options_background_texture.setRepeated(true);
  options_background.setTexture(options_background_texture);
  options_background.setScale(1.5,1.5);
}

void Game::buildWin() {

}

void Game::buildLose() {
  background_block.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
  background_block.setPosition(0,0);
  background_block.setFillColor(sf::Color::Black);

  lose_boot_sprite.setTexture(sprite_sheet);
  lose_boot_sprite.setTextureRect(sf::IntRect(192, 128, 16, 16));
  lose_boot_sprite.setScale(2.5, 2.5);
  lose_boot_sprite.setPosition(window.getSize().x/2-lose_boot_sprite.getGlobalBounds().width/2, 0);

  if(!lose_leg_texture.loadFromFile("Data/Images/leg.png")) {
    std::cout << "Background Menu texture did not load\n";
  }
  lose_leg_texture.setRepeated(true);
  lose_leg_rect.setTexture(&lose_leg_texture);
  lose_leg_rect.setTextureRect(sf::IntRect(0, 0, 16, 0));
  lose_leg_rect.setScale(2.5, 2.5);
  lose_leg_rect.setPosition(lose_boot_sprite.getPosition().x, 0);
  lose_leg_rect.setSize(sf::Vector2f(16,0));

  lose_podium_sprite.setTexture(sprite_sheet);
  lose_podium_sprite.setTextureRect(sf::IntRect(208, 128, 16, 16));
  lose_podium_sprite.setScale(2.5, 2.5);
  lose_podium_sprite.setPosition(window.getSize().x/2-(lose_podium_sprite.getGlobalBounds().width/2), 485);

  lose_player_sprite.setTexture(sprite_sheet);
  lose_player_sprite.setTextureRect(sf::IntRect(0, 0, 8, 16));
  lose_player_sprite.setScale(2.5, 2.5);
  lose_player_sprite.setPosition(window.getSize().x/2-(lose_player_sprite.getGlobalBounds().width/2), lose_podium_sprite.getPosition().y-lose_player_sprite.getGlobalBounds().height);

}

void Game::buildMenuSong() {

  key_1.setSize(sf::Vector2f(25,28 ));
  key_2.setSize(sf::Vector2f(25,28 ));
  key_2.setFillColor(sf::Color::Cyan);
  key_1.setFillColor(sf::Color::Red);
  key_2.setPosition((float)-50,(float)window.getSize().y-88);
  key_1.setPosition((float)-50,(float)window.getSize().y-88);

}
void Game::buildMapCavern() {

  player->setKeys(0);
  air_bar = 800;

  background_block.setFillColor(sf::Color::Black);

  if(!platform_wall_texture.loadFromFile("Data/Images/cavern_wall.png")) {
    std::cout << "cavern_room_wall_texture texture did not load\n";
  }
  platform_wall_texture.setRepeated(true);

  if(!platform_texture.loadFromFile("Data/Images/cavern_platform.png")) {
    std::cout << "cavern_floor_texture texture did not load\n";
  }
  platform_texture.setRepeated(true);

  if(!elevator_texture_1.loadFromFile("Data/Images/elevator_1.png")) {
    std::cout << "elevator_texture_1 texture did not load\n";
  }
  elevator_texture_1.setRepeated(true);

  platform_array[0].setSize(sf::Vector2f (window.getSize().x-(map_left_wall.getSize().x*2),25));
  platform_array[0].setPosition(map_left_wall.getSize().x,room_name_bar.getPosition().y-platform_array[0].getGlobalBounds().height);
  platform_array[0].setFillColor(sf::Color::Red);
  platform_array[0].setTextureRect(sf::IntRect(0, 0, window.getSize().x-(map_left_wall.getSize().x*2), 25));
  platform_array[0].setTexture(&platform_texture);

  platform_array[1].setSize(sf::Vector2f (350,25));
  platform_array[1].setPosition(150,platform_array[0].getPosition().y-60);
  platform_array[1].setFillColor(sf::Color::Red);
  platform_array[1].setTextureRect(sf::IntRect(0, 0, 350, 25));
  platform_array[1].setTexture(&platform_texture);

  platform_array[2].setSize(sf::Vector2f (95,25));
  platform_array[2].setPosition(map_right_wall.getPosition().x-platform_array[2].getGlobalBounds().width,platform_array[0].getPosition().y-85);
  platform_array[2].setFillColor(sf::Color::Red);
  platform_array[2].setTextureRect(sf::IntRect(0, 0, 90, 25));
  platform_array[2].setTexture(&platform_texture);

  platform_array[3].setSize(sf::Vector2f (60,25));
  platform_array[3].setPosition(map_right_wall.getPosition().x-platform_array[3].getSize().x,platform_array[0].getPosition().y-145);
  platform_array[3].setFillColor(sf::Color::Red);
  platform_array[3].setTextureRect(sf::IntRect(0, 0, 60, 25));
  platform_array[3].setTexture(&platform_texture);

  platform_array[4].setSize(sf::Vector2f (110,25));
  platform_array[4].setPosition(map_left_wall.getPosition().x+map_left_wall.getGlobalBounds().width,platform_array[0].getPosition().y-170);
  platform_array[4].setFillColor(sf::Color::Red);
  platform_array[4].setTextureRect(sf::IntRect(0, 0, 110, 25));
  platform_array[4].setTexture(&platform_texture);

  platform_array[5].setSize(sf::Vector2f (80,25));
  platform_array[5].setPosition(map_left_wall.getPosition().x+map_left_wall.getGlobalBounds().width,platform_array[0].getPosition().y-230);
  platform_array[5].setFillColor(sf::Color::Red);
  platform_array[5].setTextureRect(sf::IntRect(0, 0, 80, 25));
  platform_array[5].setTexture(&platform_texture);

  platform_array[6].setSize(sf::Vector2f (300,25));
  platform_array[6].setPosition(map_left_wall.getPosition().x+map_left_wall.getGlobalBounds().width,platform_array[0].getPosition().y-290);
  platform_array[6].setFillColor(sf::Color::Red);
  platform_array[6].setTextureRect(sf::IntRect(0, 0, 300, 25));
  platform_array[6].setTexture(&platform_texture);

  platform_array[7].setSize(sf::Vector2f (40,25));
  platform_array[7].setPosition(445,platform_array[0].getPosition().y-290);
  platform_array[7].setFillColor(sf::Color::Red);
  platform_array[7].setTextureRect(sf::IntRect(0, 0, 40, 25));
  platform_array[7].setTexture(&platform_texture);

  platform_array[8].setSize(sf::Vector2f (354,25));
  platform_array[8].setPosition(581,platform_array[0].getPosition().y-290);
  platform_array[8].setFillColor(sf::Color::Red);
  platform_array[8].setTextureRect(sf::IntRect(0, 0, 335, 25));
  platform_array[8].setTexture(&platform_texture);

  platform_array[9].setSize(sf::Vector2f (0,25));
  platform_array[9].setPosition(200,platform_array[0].getPosition().y-60);
  platform_array[9].setFillColor(sf::Color::Red);
  platform_array[9].setTextureRect(sf::IntRect(0, 0, 0, 25));
  platform_array[9].setTexture(&platform_texture);

  //GREEN MOVING
  platform_array[10].setSize(sf::Vector2f (650,25));
  platform_array[10].setPosition(200,platform_array[0].getPosition().y-170);
  platform_array[10].setTextureRect(sf::IntRect(0, 0, 650, 14));
  platform_array[10].setFillColor(sf::Color::Green);
  platform_array[10].setTexture(&elevator_texture_1);

  platform_array[11].setSize(sf::Vector2f (100,25));
  platform_array[11].setPosition(400,platform_array[0].getPosition().y-195);
  platform_array[11].setTextureRect(sf::IntRect(0, 0, 100, 25));
  platform_array[11].setTexture(&platform_wall_texture);

  platform_array[12].setSize(sf::Vector2f (100,25));
  platform_array[12].setPosition(platform_array[1].getPosition().x+platform_array[1].getGlobalBounds().width,platform_array[0].getPosition().y-85);
  platform_array[12].setTextureRect(sf::IntRect(0, 0, 100, 25));
  platform_array[12].setTexture(&platform_wall_texture);

  platform_array[13].setSize(sf::Vector2f (0,25));
  platform_array[13].setPosition(map_right_wall.getPosition().x-platform_array[13].getSize().x,platform_array[0].getPosition().y-85);
  platform_array[13].setTextureRect(sf::IntRect(0, 0, 0, 25));
  platform_array[13].setTexture(&platform_texture);

  //DECAY PLATFORMS
  for(int i = 0; i < 10; i++)
  {
    platform_1[i].initSprite(
      platform_1[i].texture, "Data/Images/cavern_platform_3.png");
    platform_1[i].getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
    platform_1[i].getSprite()->setScale(1.5, 1.5);
    if(i == 0)
    {
      platform_1[0].getSprite()->setPosition(platform_array[12].getPosition().x+platform_array[12].getGlobalBounds().width, platform_array[12].getPosition().y);
    }
    else
    {
      platform_1[i].getSprite()->setPosition(
        platform_1[0].getSprite()->getPosition().x +
          (i * platform_1[i].getSprite()->getGlobalBounds().width),
        platform_1[0].getSprite()->getPosition().y);

    }
    platform_1[i].setIsActive(true);
    platform_1[i].getSprite()->setColor(sf::Color(145,10,10,255));
    platform_1[i].setDecayTimer(4);

    platform_2[i].initSprite(
      platform_2[i].texture, "Data/Images/cavern_platform_3.png");
    platform_2[i].getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
    platform_2[i].getSprite()->setScale(1.5, 1.5);
    if(i == 0)
    {
      platform_2[0].getSprite()->setPosition(platform_array[6].getPosition().x+platform_array[6].getGlobalBounds().width, platform_array[6].getPosition().y);
    }
    else
    {
      platform_2[i].getSprite()->setPosition(
        platform_2[0].getSprite()->getPosition().x +
          (i * platform_2[i].getSprite()->getGlobalBounds().width),
        platform_2[0].getSprite()->getPosition().y);
    }
    platform_2[i].setIsActive(true);
    platform_2[i].getSprite()->setColor(sf::Color(145,10,10,255));
    platform_2[i].setDecayTimer(4);

    platform_3[i].initSprite(
      platform_3[i].texture, "Data/Images/cavern_platform_3.png");
    platform_3[i].getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
    platform_3[i].getSprite()->setScale(1.5, 1.5);
    if(i == 0)
    {
      platform_3[0].getSprite()->setPosition(platform_array[7].getPosition().x+platform_array[7].getGlobalBounds().width, platform_array[7].getPosition().y);
    }
    else
    {
      platform_3[i].getSprite()->setPosition(
        platform_3[0].getSprite()->getPosition().x +
          (i * platform_3[i].getSprite()->getGlobalBounds().width),
        platform_3[0].getSprite()->getPosition().y);
    }
    platform_3[i].setIsActive(true);
    platform_3[i].getSprite()->setColor(sf::Color(145,10,10,255));
    platform_3[i].setDecayTimer(4);
  }

  // init the GATE
  gate->initSprite(gate->texture,"Data/Images/gate_sprites.png");
  gate->getSprite()->setTextureRect(sf::IntRect (0,0,16,16));
  gate->getSprite()->setScale(2.5,2.5);
  gate->getSprite()->setPosition(map_right_wall.getPosition().x-gate->getSprite()->getGlobalBounds().width,platform_array[0].getPosition().y-gate->getSprite()->getGlobalBounds().height);
  gate->setIsActive(true);

  /*
  // init the GATE
  gate->initSprite(gate->texture,"Data/Images/gate_sprites.png");
  gate->getSprite()->setTextureRect(sf::IntRect (0,0,16,16));
  gate->getSprite()->setScale(2.5,2.5);
  gate->getSprite()->setPosition(map_right_wall.getPosition().x-gate->getSprite()->getGlobalBounds().width,platform_array[0].getPosition().y-gate->getSprite()->getGlobalBounds().height);
  gate->setIsActive(true);
   */

  //INIT THE HAZARDS
  for(int i = 0; i < 10; i++)
  {
    hazards_array[i].initSprite(hazards_array[0].texture, "Data/Images/hazard_sprites.png");
    hazards_array[i].getSprite()->setScale(2.5, 2.5);
    hazards_array[i].getSprite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
  }
  //ICICLES
  hazards_array[0].getSprite()->setTextureRect(sf::IntRect(24, 0, 8, 8));
  hazards_array[0].getSprite()->setPosition(400, 120);
  hazards_array[0].getSprite()->setColor(sf::Color::Cyan);
  hazards_array[1].getSprite()->setTextureRect(sf::IntRect(24, 0, 8, 8));
  hazards_array[1].getSprite()->setPosition(250, 120);
  hazards_array[1].getSprite()->setColor(sf::Color::Cyan);
  //GRASSES
  hazards_array[2].getSprite()->setTextureRect(sf::IntRect(16, 0, 8, 8));
  hazards_array[2].getSprite()->setColor(sf::Color::Green);
  hazards_array[2].getSprite()->setPosition(610, platform_array[8].getPosition().y-hazards_array[2].getSprite()->getGlobalBounds().height);
  hazards_array[3].getSprite()->setTextureRect(sf::IntRect(16, 0, 8, 8));
  hazards_array[3].getSprite()->setColor(sf::Color::Green);
  hazards_array[3].getSprite()->setPosition(740, platform_array[8].getPosition().y-hazards_array[3].getSprite()->getGlobalBounds().height);
  hazards_array[4].getSprite()->setTextureRect(sf::IntRect(16, 0, 8, 8));
  hazards_array[4].getSprite()->setColor(sf::Color::Green);
  hazards_array[4].getSprite()->setPosition(540, platform_array[10].getPosition().y-hazards_array[4].getSprite()->getGlobalBounds().height);
  hazards_array[5].getSprite()->setTextureRect(sf::IntRect(16, 0, 8, 8));
  hazards_array[5].getSprite()->setColor(sf::Color::Green);
  hazards_array[5].getSprite()->setPosition(300, platform_array[1].getPosition().y-hazards_array[5].getSprite()->getGlobalBounds().height);


  // INIT THE KEYS
  for(int i = 0; i < 5; i++) {
    key_array[i].initSprite(key_array[i].texture,"Data/Images/object_sprites.png");
    key_array[i].getSprite()->setTextureRect(sf::IntRect (0,0,7,8));
    key_array[i].getSprite()->setScale(2.5,2.5);
    key_array[i].setIsActive(true);
    key_array[i].getSprite()->setColor(sf::Color::Yellow);
  }
  key_array[0].getSprite()->setPosition(map_right_wall.getPosition().x-key_array[0].getSprite()->getGlobalBounds().width,platform_array[8].getPosition().y+platform_array[8].getGlobalBounds().height);
  key_array[1].getSprite()->setPosition(220,120);
  key_array[2].getSprite()->setPosition(400,hazards_array[0].getSprite()->getPosition().y+hazards_array[0].getSprite()->getGlobalBounds().height);
  key_array[3].getSprite()->setPosition(630,platform_array[8].getPosition().y-key_array[3].getSprite()->getGlobalBounds().height);
  key_array[4].getSprite()->setPosition(map_right_wall.getPosition().x-40,120);

  // YELLOW ENEMY
  enemy_array[0].sprite_rect_pos[1][0] = sf::Vector2f(128,11);
  enemy_array[0].sprite_rect_pos[1][1] = sf::Vector2f(146,12);
  enemy_array[0].sprite_rect_pos[1][2] = sf::Vector2f(164,11);
  enemy_array[0].sprite_rect_pos[1][3] = sf::Vector2f(182,10);

  enemy_array[0].sprite_rect_pos[0][0] = sf::Vector2f(192,10);
  enemy_array[0].sprite_rect_pos[0][1] = sf::Vector2f(209,11);
  enemy_array[0].sprite_rect_pos[0][2] = sf::Vector2f(226,12);
  enemy_array[0].sprite_rect_pos[0][3] = sf::Vector2f(245,11);

  enemy_array[0].initSprite(enemy_array[0].texture,"Data/Images/sprite_sheet.png");
  enemy_array[0].getSprite()->setTextureRect(sf::IntRect (128,0,11,16));
  enemy_array[0].getSprite()->setScale(2.5,2.5);
  enemy_array[0].getSprite()->setPosition(200,platform_array[10].getPosition().y-enemy_array[0].getSprite()->getGlobalBounds().height);
  enemy_array[0].setSpeed(50);
  // USING X AND Y in get movement limits to store the two EXTENTS of movement
  enemy_array[0].setMovementLimits(sf::Vector2f (platform_array[10].getPosition().x, platform_array[11].getPosition().x));
  enemy_array[0].setMoveDirection(sf::Vector2f (1,0));

}

void Game::buildMapTest() {
  std::string file_name;
  file_name = "Data/map.txt";
  std::fstream ifs(file_name);

  // map needs to store:
/*
  The Cold Room
  sf::Color::Blue
  0texture,                           1texturerect,   2scale,     3position,  4fill,                  5speed,  6movelimits 7movedir   8size       9type
  &platform_texture;-                 *;-             *;-         300;300;-   sf::Color::Magenta;-    *;-      *;-         *;-        200;25;-    -standard;-,
  Data/Images/sprite_sheet.png;-      0;16;10;16;-    2.5;2.5;-   200;200;-   *;-                     50;-     210;250;-   1;0;-      *;-         *;-,
  Data/Images/object_sprites.png;-    0;8;8;8;-       2.5;2.5;-   500;200;-   sf::Color::Yellow;-     *;-,     *;-         *;-        *;-         *;-,
  Data/Images/hazard_sprites.png;-    24;0;8;8;-      2.5;2.5;-   400;200;-   sf::Color::Cyan;-       *;-,     *;-         *;-        *;-         *;-,
  Data/Images/gate_sprites.png;-      0;0;16;16;-     2.5;2.5;-   500;500;-   yellow-true;-           *;-,     *;-         *;-        *;-         *;-,
 */

  if(ifs.is_open()) {
    int i = 0;
    std::string line;
    while (std::getline(ifs, line) )
    {
      switch (i)
      {
        case 0:
          // map name -
          map_container->setName(line);
          break;
        case 1:
          // background colour
          map_container->setColour(line);
          break;
        case 2:
          // platforms - size (x y),pos (x y),fill,texture, type
          map_container->setPlatformsContainer(line);
          break;
        case 3:
          // enemies - texture rect (l t w h), scale (x y), position (x y), speed, movement_limits (x y), move direction (x y)
          map_container->setEnemiesContainer(line);
          break;
        case 4:
          // keys - texture, texture rect (l t w h), scale (x y), position (x y), fill
          map_container->setKeysContainer(line);
          break;
        case 5:
          // hazards - texture, texture rect (l t w h), scale (x y), position (x y), fill
          map_container->setHazardsContainer(line);
          break;
        case 6:
          // gate - texture, texture rect (l t w h), scale (x y), position (x y), fill
          map_container->setGateContainer(line);
          break;
      }
      i++;
    }
  }

  std::string obj_delimiter = ",";
  std::string var_delimiter = "-";
  std::string val_delimiter = ";";
  size_t pos_obj = 0;
  std::string obj_output;
  int obj_counter = 0;
  //denotes which object in the array
  std::string line = map_container->getEnemiesContainer();
  while ((pos_obj = line.find(obj_delimiter)) != std::string::npos)
    {
      //split the object lines these are either each key, platform or similar stored and denoted by a comma
      obj_output = line.substr(0, pos_obj);
      //std::cout << "This is the object: " << obj_output << std::endl;
      std::string var_output;
      size_t pos_var= 0;
      int var_counter = 0;
      while ((pos_var = obj_output.find(var_delimiter)) != std::string::npos)
        {
          // split down the variables within these object lines
          var_output = obj_output.substr(0, pos_var);
          //std::cout << "This is the var: " << var_counter  << ": " << var_output << std::endl;
          std::string val_output;
          size_t pos_val = 0;
          //denotes which var

          int texture_rect_counter = 0;
          int scale_counter = 0;
          int position_counter = 0;
          int movement_counter = 0;
          int move_direction_counter = 0;


          while ((pos_val = var_output.find(val_delimiter)) != std::string::npos)
            {
              val_output = var_output.substr(0, pos_val);
              //std::cout << "This is the value: " << val_output << std::endl;
              var_output.erase(0, pos_val + val_delimiter.length());
              // create the object here - first enemy created at 0 in array
              switch (var_counter)
              {
                case 0:
                  // single value
                  std::cout << "This is the texture: " << val_output << std::endl;
                  enemy_array[obj_counter].initSprite(enemy_array[obj_counter].texture,val_output);
                    /*
                  // USING X AND Y in get movement limits to store the two EXTENTS of movement
                  enemy_array[0].setMovementLimits(sf::Vector2f (380, map_right_wall.getPosition().x));
                  enemy_array[0].setMoveDirection(sf::Vector2f (1,0));
                    */

                break;
                case 1:
                  // 4 values
                  std::cout << "This is the texture rect: " << val_output << std::endl;
                  switch (texture_rect_counter)
                  {
                    case 0:
                      enemy_array[obj_counter].sprite_texture_rect.left = stoi(val_output);
                    break;
                    case 1:
                      enemy_array[obj_counter].sprite_texture_rect.top = stoi(val_output);
                    break;
                    case 2:
                      enemy_array[obj_counter].sprite_texture_rect.width = stoi(val_output);
                    break;
                    case 3:
                      enemy_array[obj_counter].sprite_texture_rect.height = stoi(val_output);
                    break;
                  }
                  texture_rect_counter ++;
                break;
                case 2:
                  // 2 values
                  std::cout << "This is the scale: " << val_output << std::endl;
                  switch (scale_counter)
                  {
                    case 0:
                      enemy_array[obj_counter].getSprite()->setScale(stof(val_output),enemy_array[obj_counter].getSprite()->getScale().y);
                    break;
                    case 1:
                      enemy_array[obj_counter].getSprite()->setScale(enemy_array[obj_counter].getSprite()->getScale().x,stof(val_output));
                    break;
                  }
                  scale_counter ++;
                break;
                case 3:
                  // 2 values
                  std::cout << "This is the position: " << val_output << std::endl;
                  switch (position_counter)
                  {
                    case 0:
                      enemy_array[obj_counter].getSprite()->setPosition(stof(val_output),enemy_array[obj_counter].getSprite()->getPosition().y);
                    break;
                    case 1:
                      enemy_array[obj_counter].getSprite()->setPosition(enemy_array[obj_counter].getSprite()->getPosition().x,stof(val_output));
                    break;
                  }
                  position_counter ++;
                break;
                case 4:
                  // single value
                  std::cout << "This is the fill: " << val_output << std::endl;
                  break;
                case 5:
                  // single value
                  std::cout << "This is the speed: " << val_output << std::endl;
                  enemy_array[obj_counter].setSpeed(stoi(val_output));
                break;
                case 6:
                  // 2 values
                  std::cout << "This is the movement limits: " << val_output << std::endl;
                  switch (movement_counter)
                  {
                      case 0:
                      enemy_array[obj_counter].setMovementLimits(sf::Vector2f (stof(val_output), enemy_array[obj_counter].getMovementLimits().y));
                      break;
                      case 1:
                      enemy_array[obj_counter].setMovementLimits(sf::Vector2f (enemy_array[obj_counter].getMovementLimits().x,stof(val_output)));
                      break;
                  }
                  movement_counter ++;
                break;
                case 7:
                  // 2 values
                  std::cout << "This is the movement direction: " << val_output << std::endl;
                  switch (move_direction_counter)
                  {
                      case 0:
                      enemy_array[obj_counter].setMoveDirection(sf::Vector2f (stof(val_output), enemy_array[obj_counter].getMoveDirection().y));
                      break;
                      case 1:
                      enemy_array[obj_counter].setMoveDirection(sf::Vector2f (enemy_array[obj_counter].getMoveDirection().x,stof(val_output)));
                      break;
                  }
                  move_direction_counter ++;
                break;
                case 8:
                  // single value
                  std::cout << "This is the fill: " << val_output << std::endl;
                break;
                case 9:
                  // single value
                  std::cout << "This is the fill: " << val_output << std::endl;
                break;
              }
            }
          obj_output.erase(0, pos_var + var_delimiter.length());
          var_counter ++;
        }
      line.erase(0, pos_obj + obj_delimiter.length());
      obj_counter ++;
    }
    //std::cout << enemy_array[0].getMoveDirection().y;
}

void Game::buildMap() {

}

void Game::buildMapCold() {

  background_block.setFillColor(sf::Color::Blue);

  player->setKeys(0);
  air_bar = 800;

  // init the GATE
  gate->initSprite(gate->texture,"Data/Images/gate_sprites.png");
  gate->getSprite()->setTextureRect(sf::IntRect (0,0,16,16));
  gate->getSprite()->setScale(2.5,2.5);
  gate->setIsActive(true);

  if(!platform_wall_texture.loadFromFile("Data/Images/cavern_wall.png")) {
    std::cout << "cavern_room_wall_texture texture did not load\n";
  }
  platform_wall_texture.setRepeated(true);

  if(!platform_texture.loadFromFile("Data/Images/cavern_platform.png")) {
    std::cout << "cavern_floor_texture texture did not load\n";
  }
  platform_texture.setRepeated(true);

  if(!elevator_texture_1.loadFromFile("Data/Images/elevator_1.png")) {
    std::cout << "elevator_texture_1 texture did not load\n";
  }
  elevator_texture_1.setRepeated(true);

  // FLOOR
  platform_array[0].setSize(sf::Vector2f (window.getSize().x-(map_left_wall.getSize().x*2),25));
  platform_array[0].setPosition(map_left_wall.getSize().x,room_name_bar.getPosition().y-platform_array[0].getGlobalBounds().height);
  platform_array[0].setFillColor(sf::Color::Magenta);
  platform_array[0].setTextureRect(sf::IntRect(0, 0, window.getSize().x-(map_left_wall.getSize().x*2), 25));
  platform_array[0].setTexture(&platform_texture);

  platform_array[1].setSize(sf::Vector2f (100,25));
  platform_array[1].setPosition(450,platform_array[0].getPosition().y-80);
  platform_array[1].setFillColor(sf::Color::Magenta);
  platform_array[1].setTextureRect(sf::IntRect(0, 0, 100, 25));
  platform_array[1].setTexture(&platform_texture);

  platform_array[2].setSize(sf::Vector2f (200,25));
  platform_array[2].setPosition(300,platform_array[0].getPosition().y-165);
  platform_array[2].setFillColor(sf::Color::Magenta);
  platform_array[2].setTextureRect(sf::IntRect(0, 0, 200, 25));
  platform_array[2].setTexture(&platform_texture);

  platform_array[3].setSize(sf::Vector2f (40,25));
  platform_array[3].setPosition(map_left_wall.getPosition().x+map_left_wall.getSize().x,platform_array[0].getPosition().y-230);
  platform_array[3].setFillColor(sf::Color::Magenta);
  platform_array[3].setTextureRect(sf::IntRect(0, 0, 40, 25));
  platform_array[3].setTexture(&platform_texture);

  platform_array[4].setSize(sf::Vector2f (600,25));
  platform_array[4].setPosition(map_left_wall.getPosition().x+map_left_wall.getSize().x,platform_array[0].getPosition().y-290);
  platform_array[4].setFillColor(sf::Color::Magenta);
  platform_array[4].setTextureRect(sf::IntRect(0, 0, 600, 25));
  platform_array[4].setTexture(&platform_texture);

  platform_array[5].setSize(sf::Vector2f (130,25));
  platform_array[5].setPosition(667,platform_array[4].getPosition().y+23);
  platform_array[5].setFillColor(sf::Color::Magenta);
  platform_array[5].setTextureRect(sf::IntRect(0, 0, 130, 25));
  platform_array[5].setTexture(&platform_texture);

  platform_array[6].setSize(sf::Vector2f (32,25));
  platform_array[6].setPosition(763,platform_array[0].getPosition().y-340);
  platform_array[6].setFillColor(sf::Color::Magenta);
  platform_array[6].setTextureRect(sf::IntRect(0, 0, 40, 25));
  platform_array[6].setTexture(&platform_texture);

  //moving
  platform_array[7].setSize(sf::Vector2f (100,25));
  platform_array[7].setPosition(60,platform_array[0].getPosition().y-85);
  platform_array[7].setTextureRect(sf::IntRect(0, 0, 100, 14));
  platform_array[7].setFillColor(sf::Color::Yellow);
  platform_array[7].setTexture(&elevator_texture_1);

  platform_array[8].setPosition(0,0);
  platform_array[9].setPosition(0,0);

  // walls
  platform_array[11].setSize(sf::Vector2f (25,238));
  platform_array[11].setPosition(map_right_wall.getPosition().x-25-gate->getSprite()->getGlobalBounds().width,platform_array[0].getPosition().y-gate->getSprite()->getGlobalBounds().height-platform_array[11].getSize().y-2);
  platform_array[11].setTextureRect(sf::IntRect(0, 0, 25, 238));
  platform_array[11].setFillColor(sf::Color::White);
  platform_array[11].setTexture(&platform_wall_texture);

  platform_array[10].setSize(sf::Vector2f (25,223));
  platform_array[10].setPosition(797,(platform_array[11].getPosition().y+platform_array[11].getGlobalBounds().height)-platform_array[10].getGlobalBounds().height-2);
  platform_array[10].setTextureRect(sf::IntRect(0, 0, 25, 223));
  platform_array[10].setFillColor(sf::Color::White);
  platform_array[10].setTexture(&platform_wall_texture);

  platform_array[12].setSize(sf::Vector2f (350,25));
  platform_array[12].setPosition(map_right_wall.getPosition().x-platform_array[12].getGlobalBounds().width,platform_array[0].getPosition().y-405);
  platform_array[12].setTextureRect(sf::IntRect(0, 0, 350, 25));
  platform_array[12].setFillColor(sf::Color::White);
  platform_array[12].setTexture(&platform_wall_texture);

  //decay platforms
  initDecayPlatforms(platform_1, map_the_cold_room, 250, platform_array[0].getPosition().y-60, 5);
  initDecayPlatforms(platform_2, map_the_cold_room, 600, platform_array[0].getPosition().y-120, 5);
  initDecayPlatforms(platform_3, map_the_cold_room, platform_array[3].getPosition().x+platform_array[3].getGlobalBounds().width, platform_array[3].getPosition().y, 5);
  initDecayPlatforms(platform_4, map_the_cold_room, platform_array[11].getPosition().x-48, 457, 2);
  initDecayPlatforms(platform_5, map_the_cold_room, platform_array[11].getPosition().x-48, 423, 2);
  initDecayPlatforms(platform_6, map_the_cold_room, platform_array[11].getPosition().x-48, 388, 2);
  initDecayPlatforms(platform_7, map_the_cold_room, platform_array[11].getPosition().x-48, 352, 2);
  initDecayPlatforms(platform_8, map_the_cold_room, platform_array[11].getPosition().x-48, 318, 2);
  initDecayPlatforms(platform_9, map_the_cold_room, platform_array[11].getPosition().x-48, 262, 2);
  initDecayPlatforms(platform_10, map_the_cold_room, platform_array[5].getPosition().x, platform_array[6].getPosition().y, 4);

  // init the GATE
  gate->getSprite()->setPosition(map_right_wall.getPosition().x-gate->getSprite()->getGlobalBounds().width,platform_array[0].getPosition().y-gate->getSprite()->getGlobalBounds().height);

  //INIT THE HAZARDS
  for(int i = 0; i < 10; i++)
  {
    hazards_array[i].initSprite(hazards_array[0].texture, "Data/Images/hazard_sprites.png");
    hazards_array[i].getSprite()->setScale(2.5, 2.5);
    hazards_array[i].getSprite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
  }
  //ICICLES
  hazards_array[0].getSprite()->setTextureRect(sf::IntRect(24, 0, 8, 8));
  hazards_array[0].getSprite()->setPosition(map_right_wall.getPosition().x-hazards_array[0].getSprite()->getGlobalBounds().width, platform_array[12].getPosition().y+25);
  hazards_array[0].getSprite()->setColor(sf::Color::Cyan);

  // INIT THE KEYS
  for(int i = 0; i < 5; i++) {
    key_array[i].initSprite(key_array[i].texture,"Data/Images/object_sprites.png");
    key_array[i].getSprite()->setTextureRect(sf::IntRect (0,8,8,8));
    key_array[i].getSprite()->setScale(2.5,2.5);
    key_array[i].setIsActive(true);
    key_array[i].getSprite()->setColor(sf::Color::Yellow);
  }
  key_array[0].getSprite()->setPosition(60,380);
  key_array[1].getSprite()->setPosition(220,150);
  key_array[2].getSprite()->setPosition(570,platform_array[1].getPosition().y);
  key_array[3].getSprite()->setPosition(platform_array[6].getPosition().x,platform_array[12].getPosition().y+25);
  key_array[4].getSprite()->setPosition(platform_array[10].getPosition().x+25,290);

  // YELLOW ENEMY
  enemy_array[0].sprite_rect_pos[1][0] = sf::Vector2f(0,10);
  enemy_array[0].sprite_rect_pos[1][1] = sf::Vector2f(18,10);
  enemy_array[0].sprite_rect_pos[1][2] = sf::Vector2f(36,10);
  enemy_array[0].sprite_rect_pos[1][3] = sf::Vector2f(54,10);

  enemy_array[0].sprite_rect_pos[0][0] = sf::Vector2f(64,10);
  enemy_array[0].sprite_rect_pos[0][1] = sf::Vector2f(82,10);
  enemy_array[0].sprite_rect_pos[0][2] = sf::Vector2f(100,10);
  enemy_array[0].sprite_rect_pos[0][3] = sf::Vector2f(118,10);

  enemy_array[1].sprite_rect_pos[1][0] = sf::Vector2f(0,10);
  enemy_array[1].sprite_rect_pos[1][1] = sf::Vector2f(18,10);
  enemy_array[1].sprite_rect_pos[1][2] = sf::Vector2f(36,10);
  enemy_array[1].sprite_rect_pos[1][3] = sf::Vector2f(54,10);

  enemy_array[1].sprite_rect_pos[0][0] = sf::Vector2f(64,10);
  enemy_array[1].sprite_rect_pos[0][1] = sf::Vector2f(82,10);
  enemy_array[1].sprite_rect_pos[0][2] = sf::Vector2f(100,10);
  enemy_array[1].sprite_rect_pos[0][3] = sf::Vector2f(118,10);

  enemy_array[0].initSprite(enemy_array[0].texture,"Data/Images/sprite_sheet.png");
  enemy_array[0].getSprite()->setTextureRect(sf::IntRect (0,16,10,16));
  enemy_array[0].getSprite()->setScale(2.5,2.5);
  enemy_array[0].getSprite()->setPosition(map_right_wall.getPosition().x-enemy_array[0].getSprite()->getGlobalBounds().width,platform_array[0].getPosition().y-enemy_array[0].getSprite()->getGlobalBounds().height);
  enemy_array[0].setSpeed(50);
  // USING X AND Y in get movement limits to store the two EXTENTS of movement
  enemy_array[0].setMovementLimits(sf::Vector2f (380, map_right_wall.getPosition().x));
  enemy_array[0].setMoveDirection(sf::Vector2f (1,0));

  enemy_array[1].initSprite(enemy_array[0].texture,"Data/Images/sprite_sheet.png");
  enemy_array[1].getSprite()->setTextureRect(sf::IntRect (0,16,10,16));
  enemy_array[1].getSprite()->setScale(2.5,2.5);
  enemy_array[1].getSprite()->setPosition(platform_array[4].getPosition().x,platform_array[4].getPosition().y-enemy_array[0].getSprite()->getGlobalBounds().height);
  enemy_array[1].setSpeed(50);
  // USING X AND Y in get movement limits to store the two EXTENTS of movement
  enemy_array[1].setMovementLimits(sf::Vector2f (platform_array[4].getPosition().x, platform_array[4].getPosition().x+platform_array[4].getGlobalBounds().width));
  enemy_array[1].setMoveDirection(sf::Vector2f (1,0));

}

void Game::animateLife(sf::Clock& life_animation_clock) {
  if (life_animation_clock.getElapsedTime().asSeconds() > 0.2)
  {
    for (int i = 0; i < player->getLives(); i++)
    {
      life_texture_rect = sf::IntRect(
        player->sprite_rect_pos[0][life_frame].x,
        0,
        player->sprite_rect_pos[0][life_frame].y,
        16);
      life_sprite[i].setTextureRect(life_texture_rect);
    }
    if (life_frame < 3)
    {
      life_frame++;
    }
    else
    {
      life_frame = 0;
    }
    life_animation_clock.restart();
  }
}

void Game::initMaps() {
  map_central_cavern->setEnemies(1);
  map_central_cavern->setHazards(6);
  map_central_cavern->setKeys(5);
  map_central_cavern->setPlatforms(13);
  map_central_cavern->setDecayPlatforms(3);
  map_central_cavern->setColourRed(145);
  map_central_cavern->setColourGreen(10);
  map_central_cavern->setColourBlue(10);

  map_the_cold_room->setEnemies(2);
  map_the_cold_room->setHazards(1);
  map_the_cold_room->setKeys(5);
  map_the_cold_room->setPlatforms(13);
  map_the_cold_room->setDecayPlatforms(10);
  map_the_cold_room->setColourRed(160);
  map_the_cold_room->setColourGreen(0);
  map_the_cold_room->setColourBlue(160);
}

void Game::checkPlatformCollide(float dt){

  //CHECK MOVING PLATFORMS
  for(int i = 0; i < map_platforms; i++)
  {
    if(platform_array[i].getTexture() == &platform_wall_texture)
    {
      if (player->checkPlatformCollisionWall(*player, platform_array[i]))
      {
        if(player->move_left) {
          player->getSprite()->move(1 * player->getSpeed() * dt, 0);
        }
        if(player->move_right) {
          player->getSprite()->move(-1 * player->getSpeed() * dt, 0);
        }
        if (player->is_jumping)
        {
          player->is_falling = true;
          player->is_jumping = false;
        }
      }
    }
  }

    //check for platform collisions
    for(int i = 0; i < map_platforms; i++)
    {
      if (!player->on_platform || player->is_falling)
      {
        // check full collision
        if (player->checkPlatformCollision(*player, platform_array[i]))
        {
          if(player->y_velocity > 230) {
            playerDie();
          }
          player->on_platform = true;
          player->y_velocity = 0;
          player->is_falling = false;
          player->is_jumping = false;
          player->jump_left = false;
          player->jump_right = false;
          audio->sound_jump.stop();
          audio->sound_falling.stop();
          player->current_platform_constraints = {
            platform_array[i].getPosition().x,
            platform_array[i].getPosition().x +
              platform_array[i].getGlobalBounds().width
          };
          if(platform_array[i].getTexture() == &elevator_texture_1)
          {
            player->setMovingPlatform(true);
          }
          player->getSprite()->setPosition(player->getSprite()->getPosition().x, platform_array[i].getPosition().y-player->getSprite()->getGlobalBounds().height);
        }
      }
      else
      {
        if(player->is_jumping) {
          player->on_platform = false;
          player->moving_platform = false;
        }
        else
        {
          if (
            (player->getSprite()->getPosition().x +
               player->getSprite()->getGlobalBounds().width <
             player->getCurrentPlatformConstraints().x) ||
            (player->getSprite()->getPosition().x >
             player->getCurrentPlatformConstraints().y))
          {
            player->on_platform = false;
            player->is_falling  = true;
            player->moving_platform = false;
            player->setCurrentPlatformConstraints(sf::Vector2f(0, 0));
          }
        }
      }
    }
}

void Game::checkDecayPlatformCollide(Platform *platform)
{
  //PLAY HERE WITH DECAY
  for (int i = 0; i < 10; i++)
  {
        if (platform[i].getDecayTimer() > 0)
        {
          if (player->checkDecayingPlatformCollision(
                *player, *platform[i].getSprite()) && platform[i].getDecayTimer() > 0)
          {
        player->on_platform = true;
        player->y_velocity = 0;
        player->is_falling  = false;
        player->is_jumping  = false;
        player->jump_left   = false;
        player->jump_right  = false;
        audio->sound_jump.stop();
        audio->sound_falling.stop();

        if (platform_decay_clock.getElapsedTime().asSeconds() > 0.3)
        {
          platform[i].setDecayTimer(platform[i].getDecayTimer() - 1);
          platform_decay_clock.restart();
          if (platform[i].getDecayTimer() <= 0)
          {
              player->on_platform = false;
              player->is_falling = true;
              player->current_platform_constraints = { 0, 0 };
          }
        }

        if (player->y_velocity > 230)
        {
          playerDie();
        }
        player->current_platform_constraints = {
          platform[i].getSprite()->getPosition().x,
          platform[i].getSprite()->getPosition().x +
            platform[i].getSprite()->getGlobalBounds().width
        };
        player->getSprite()->setPosition(
          player->getSprite()->getPosition().x,
          platform[i].getSprite()->getPosition().y -
            player->getSprite()->getGlobalBounds().height + 1);
          }
        }
  }
}

void Game::playerDie() {
  player->setLives(player->getLives()-1);
  audio->sound_die.play();
  audio->sound_jump.stop();
  audio->sound_falling.stop();
  resetPlayer();
}

void Game::setDecayPlatformColours(Platform* platform, int red, int green, int blue) {
  for(int i = 0; i < 10; i++)
  {
        if(platform[i].getDecayTimer() == 4) {
          platform[i].getSprite()->setColor(sf::Color(red,green,blue,255));
        }
        if(platform[i].getDecayTimer() == 3) {
          platform[i].getSprite()->setColor(sf::Color(red,green,blue,220));
        }
        if(platform[i].getDecayTimer() == 2) {
          platform[i].getSprite()->setColor(sf::Color(red,green,blue,180));
        }
        if(platform[i].getDecayTimer() == 1) {
          platform[i].getSprite()->setColor(sf::Color(red,green,blue,100));
        }
        if(platform[i].getDecayTimer() == 0) {
          platform[i].getSprite()->setColor(sf::Color(red,green,blue,0));
        }
  }
}

void Game::initDecayPlatforms(Platform* platform, Map* map, int x, int y, int size) {
  //THIS MUST REMAIN 10 TO EQUAL SIZE OF THE ARRAY DO NOT USE MAP_DECAY
  for(int i = 0; i < 10; i++)
  {
        platform[i].initSprite(
          platform[i].texture, "Data/Images/cavern_platform_3.png");
        platform[i].getSprite()->setTextureRect(sf::IntRect(0, 0, 16, 16));
        platform[i].getSprite()->setScale(1.5, 1.5);
        if (i == 0)
        {
          platform[0].getSprite()->setPosition(x, y);
        }
        else
        {
          platform[i].getSprite()->setPosition(
            platform[0].getSprite()->getPosition().x +
              (i * platform[i].getSprite()->getGlobalBounds().width),
            platform[0].getSprite()->getPosition().y);
        }
        platform[i].getSprite()->setColor(sf::Color(map->getColourRed(), map->getColourGreen(), map->getColourBlue(), 255));
        platform[i].setDecayTimer(0);
  }
  for (int i = 0; i < size; i++)
  {
        platform[i].setDecayTimer(4);
  }
}
void Game::drawDecayPlatforms(Platform* platform, int size) {
  for (int i = 0; i < size; i++)
  {
        window.draw(*platform[i].getSprite());
  }
}
void Game::defineMapSpecifics() {
  //DEFINE MAP SPECIFICS
  switch(mapstate)
  {
        case CENTRAL_CAVERN:
          map_enemies = map_central_cavern->getEnemies();
          map_decay = map_central_cavern->getDecayPlatforms();
          map_keys = map_central_cavern->getKeys();
          map_hazards = map_central_cavern->getHazards();
          map_platforms = map_central_cavern->getPlatforms();
          map_red = map_central_cavern->getColourRed();
          map_green = map_central_cavern->getColourGreen();
          map_blue = map_central_cavern->getColourBlue();
          break;
        case THE_COLD_ROOM:
          map_enemies = map_the_cold_room->getEnemies();
          map_decay = map_the_cold_room->getDecayPlatforms();
          map_keys = map_the_cold_room->getKeys();
          map_hazards = map_the_cold_room->getHazards();
          map_platforms = map_the_cold_room->getPlatforms();
          map_red = map_the_cold_room->getColourRed();
          map_green = map_the_cold_room->getColourGreen();
          map_blue = map_the_cold_room->getColourBlue();
          break;
  }
}
void Game::mapSequencer() {

  for(int i = 0; i < 10; i++)
  {
        platform_array[i].setSize(sf::Vector2f(0, 0));
  }
  platform_1->setDecayTimer(0);
  platform_2->setDecayTimer(0);
  platform_3->setDecayTimer(0);
  platform_4->setDecayTimer(0);
  platform_5->setDecayTimer(0);
  platform_6->setDecayTimer(0);
  platform_7->setDecayTimer(0);
  platform_8->setDecayTimer(0);
  platform_9->setDecayTimer(0);
  platform_10->setDecayTimer(0);

  switch(current_map) {
        case 0:
          buildMapCavern();
          mapstate = MapState::CENTRAL_CAVERN;
          break;
        case 1:
          buildMapCold();
          mapstate = MapState::THE_COLD_ROOM;
          break;
  }
}
void Game::buildFinale() {
  // display win message
  // get high scores, sort scores
  // check to see if score is above slot 0
  //is yes request enter high score entry
  //replace slot 0 in array and then resort array
  //display high score table
  //set enter to return to menu

  switch(player_name_letter) {
        case 0:
        player_name_position_1 = player_name_scroll;
        break;
        case 1:
        player_name_position_2 = player_name_scroll;
        break;
        case 2:
        player_name_position_3 = player_name_scroll;
        break;
  }

  player_name_entry = std::string(high_score_entry_alphabet[player_name_position_1] + high_score_entry_alphabet[player_name_position_2] + high_score_entry_alphabet[player_name_position_3]);
  text->player_name.setString(player_name_entry);

  if(!win_banner_texture.loadFromFile("Data/Images/win_banner.png")) {
        std::cout << "cavern_room_wall_texture texture did not load\n";
  }
  win_banner_texture.setRepeated(false);

  win_banner.setSize(sf::Vector2f (window.getSize().x,300));
  win_banner.setPosition(0,0);
  win_banner.setScale(3.75,3.75);
  win_banner.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 300));
  win_banner.setTexture(&win_banner_texture);

  std::string score_chart;
  score_chart = "Name:   Score:\n" +
                high_scores_array[9][0] + ":   " + high_scores_array[9][1] + "\n" +
                high_scores_array[8][0] + ":   " + high_scores_array[8][1] + "\n" +
                high_scores_array[7][0] + ":   " + high_scores_array[7][1] + "\n" +
                high_scores_array[6][0] + ":   " + high_scores_array[6][1] + "\n" +
                high_scores_array[5][0] + ":   " + high_scores_array[5][1] + "\n" +
                high_scores_array[4][0] + ":   " + high_scores_array[4][1] + "\n" +
                high_scores_array[3][0] + ":   " + high_scores_array[3][1] + "\n" +
                high_scores_array[2][0] + ":   " + high_scores_array[2][1] + "\n" +
                high_scores_array[1][0] + ":   " + high_scores_array[1][1] + "\n" +
                high_scores_array[0][0] + ":   " + high_scores_array[0][1] + "\n";
  text->score_1.setString(score_chart);
  text->score_1.setPosition((((float)window.getSize().x - text->score_1.getGlobalBounds().width)/2),400);
}

void Game::getHighScores(std::string (&high_scores_array)[10][10]) {
  // pull the selected npc's text file and add into the npc_response_array[]
  std::string file_name;
  file_name = "Data/high_scores.txt";
  std::fstream ifs(file_name);
  std::string delimiter = ",";
  size_t pos = 0;
  std::string output;

  if(ifs.is_open()) {
        int i = 0;
        std::string line;
        while (std::getline(ifs, line) )
        {
          while ((pos = line.find(delimiter)) != std::string::npos)
          {
            output = line.substr(0, pos);
            if(!isdigit(output[0]))
            {
              high_scores_array[i][0] = output;
            }
            else
            {
              high_scores_array[i][1] = output;
            }
            line.erase(0, pos + delimiter.length());
          }
          i++;
        }
  }
  /*
  for(int i = 0; i < 10; i++)
  {
        std::cout << "SCORE " << i << ": " << high_scores_array[i][0] << " score is: " << high_scores_array[i][1] << std::endl;
  }
   */

}
void Game::sortHighScores(std::string (&high_scores_array)[10][10]) {
  //BUBBLESORT THE SCORES
  int n, m;
  bool swapped;
  for (n = 0; n < 10 - 1; n++)
  {
        swapped = false;
        for (m = 0; m < 10 - n - 1; m++)
        {
          if (stoi(high_scores_array[m][1]) > stoi(high_scores_array[m + 1][1]))
          {
            swap(high_scores_array[m][1], high_scores_array[m + 1][1]);
            swap(high_scores_array[m][0], high_scores_array[m + 1][0]);
            swapped = true;
          }
        }
        // If no two elements were swapped
        if (swapped == false)
          break;
  }
  /*
  for(int i = 0; i < 10; i++)
  {
        std::cout<< "sorted scores " << i << ": " << high_scores_array[i][0] << " score is: " << high_scores_array[i][1] << std::endl;
  }
   */
}
void Game::updateHighScores(std::string (&high_scores_array)[10][10], Player* player) {
  std::ofstream high_score_file("Data/high_scores.txt");
  // Write to the file
  for(int i = 0; i < 10; i++) {
        high_score_file << high_scores_array[i][0] << "," << high_scores_array[i][1] << ",\n";
  }
  // Close the file
  high_score_file.close();
}



#ifndef game_hpp
#define game_hpp

#include "grid.hpp"
#include "tetris.hpp"
#include "scoreboard.hpp"
#include "RichText.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>

struct game {
private:
    bool game_active; 
public:
    game(); 
    void display_menu(sf::RenderWindow &window);
    void play_game();
    void reset_game(grid &grid, tetris &tetris);
};

#endif /* game_hpp */

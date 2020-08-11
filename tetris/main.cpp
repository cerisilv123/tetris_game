
#include "grid.hpp"
#include "tetris.hpp"
#include "scoreboard.hpp"
#include "game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {

    game Game;
    Game.play_game();
    
    return 0;
}

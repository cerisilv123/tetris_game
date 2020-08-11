
#ifndef scoreboard_hpp
#define scoreboard_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "tetris.hpp"
#include "grid.hpp"

class scoreboard {
private:
    
public:
    void draw_seperating_line(sf::RenderWindow &window);
    void draw_next_shape(sf::RenderWindow &window, tetris &tetris);
    void draw_score(sf::RenderWindow &window, grid &grid);
};

#endif /* scoreboard_hpp */

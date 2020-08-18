
#ifndef grid_hpp
#define grid_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <vector>
#include "tetris.hpp"

class grid {
private:
    int columns;
    int rows;
    sf::RectangleShape grid_square; // square shape to draw out the grid with (not the tetrominoes)
    sf::RectangleShape grid_block; // Square block to draw out the collided tetrominoes
public:
    grid();
    int points; // RESET when game is over
    bool game_over; 
    std::vector<std::vector<int>> grid_coords {}; // RESET when game is over
    void add_shape_to_grid(std::vector<sf::Vector2f> &coords, tetris &tetris);
    bool has_collided_bottom(tetris &tetris);
    bool has_collided_grid(tetris &tetris); 
    void draw_grid(sf::RenderWindow &window, tetris &tetris);
    void delete_line(tetris &tetris, sf::RenderWindow &window, float &min_time);
    void against_shape_right(tetris &tetris);
    void against_shape_left(tetris &tetris);
    void against_shape_right_angle(tetris &tetris);
    void against_shape_left_angle(tetris &tetris);
    void draw_future_position(tetris tetris, sf::RenderWindow &window);
    bool bottom_of_grid(std::vector<sf::Vector2f> &temp);
    bool above_grid(std::vector<sf::Vector2f> &temp);
    bool line_deleted; // RESET when game is over
    int return_points();
};

#endif /* grid_hpp */

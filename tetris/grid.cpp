
#include <iostream>
#include <vector>
#include <iterator>
#include "grid.hpp"

grid::grid() {
    this->columns = 10;
    this->rows = 25;
    
    this->points = 0;
    this->game_over = false; 
    
    this->line_deleted = false; 
        
    grid_square.setSize(sf::Vector2f(30,30));
    grid_square.setFillColor(sf::Color(sf::Color::Black));
    grid_square.setOutlineColor(sf::Color(211,211,211));
    grid_square.setOutlineThickness(1);
    
    grid_block.setSize(sf::Vector2f(30,30));
    grid_block.setFillColor(sf::Color(sf::Color::Green));
    
    grid_coords = {
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,7,7,7,7,7,7}
    };
}

// Adds shape to the grid after it's reached its bounds
void grid::add_shape_to_grid(std::vector<sf::Vector2f> &coords, tetris &tetris) {
    for (size_t i = 0; i < 4; i++) {
        grid_coords[coords[i].y][coords[i].x] = tetris.colour;
    }
}

// Checks to see if the Tetris has fallen to the bottom of the grid - then adds shape to grid_coords
bool grid::has_collided_bottom(tetris &tetris) {
    bool result {false};
    std::vector<sf::Vector2f> temp{};
    temp = tetris.return_live_coords();
    
    for (size_t i = 0; i < temp.size(); i++) {
       if (temp[i].y == 24) {
           add_shape_to_grid(temp, tetris);
           tetris.tetris_active = false;
           result = true;
       }
    }
    return result; 
}

// Checks to see if shape has landed on top of another shape - then adds shape to grid_coords
bool grid::has_collided_grid(tetris &tetris) {
    bool result{false};
    std::vector<sf::Vector2f> temp{};
    temp = tetris.return_live_coords();
    
    for (size_t i = 0; i < temp.size(); i++) {
        if (grid_coords[temp[i].y + 1][temp[i].x] < 7) {
            result = true;
        }
    }
    if (result == true) {
        add_shape_to_grid(temp, tetris);
        tetris.tetris_active = false; 
    }
    return result;
}

// Draws all shapes out on the grid
void grid::draw_grid(sf::RenderWindow &window, tetris &tetris) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            if (grid_coords[i][j] < 7) {
                sf::RectangleShape block;
                block.setSize(sf::Vector2f(30,30));
                
                if (grid_coords[i][j] == 0)
                    block.setFillColor(sf::Color::Red);
                else if (grid_coords[i][j] == 1)
                    block.setFillColor(sf::Color(255,165,0)); // Orange
                else if (grid_coords[i][j] == 2)
                    block.setFillColor(sf::Color::Green);
                else if (grid_coords[i][j] == 3)
                    block.setFillColor(sf::Color::Blue);
                else if (grid_coords[i][j] == 4)
                    block.setFillColor(sf::Color::Yellow);
                else if (grid_coords[i][j] == 5)
                    block.setFillColor(sf::Color::Magenta); // Pink
                else if (grid_coords[i][j] == 6)
                    block.setFillColor(sf::Color::Cyan); // Light Blue
                
                block.setPosition(sf::Vector2f(j * 30, i * 30));
                window.draw(block);
            }
        }
    }
}

// Checks to see if any lines are full and need to be deleted from the grid
void grid::delete_line(tetris &tetris, sf::RenderWindow &window, float &min_time) {
    std::vector<int> line_numbers{}; // Line numbers to delete
    for (int i = 0; i < rows; i++) {
        bool is_filled = true;
        for (size_t j = 0; j < columns; j++) {
            if (grid_coords[i][j] == 7) {
                is_filled = false;
            }
        }
        if (is_filled == true) {
            line_numbers.push_back(i);
        }
    }
    
    if (line_numbers.size() == 4) { // Add points to score
        points += 800; 
    }
    else {
        points += (line_numbers.size() * 100); // Add points to score
    }
    
    if (line_numbers.size() != 0) { // Delete and move down lines
        std::vector<std::vector<int>> temp_coords = grid_coords;
        // j = temp_coords iterator - starts at line_numbers.size();
        // i = grid_coords iterator - starts at first row
        // if we come to the line that needs to be deleted = i++
        int count{0};
        
        for (size_t i = 0, j = line_numbers.size(); i < rows; i++, j++) {
            for (size_t x = 0; x < columns; x++) {
                if (i == line_numbers[count]) {
                    if (i != 24) { // Check to see if it's last line
                       i++;
                       count++;
                    }
                }
                if (i != line_numbers[count]) {
                    temp_coords[j][x] = grid_coords[i][x];
                }
            }
        }
        grid_coords = temp_coords;
        line_deleted = true; 
    }
}

// Checks to see if theres a shape to the right - will stop shape from moving in that direction
void grid::against_shape_right(tetris &tetris) {
    bool result {false};
    std::vector<sf::Vector2f> temp;
    temp = tetris.return_live_coords();
    for (size_t i = 0; i < temp.size(); i++) {
        if (grid_coords[temp[i].y][temp[i].x + 1] < 7) {
            result = true;
        }
    }
    tetris.against_shape_right_side = result; 
}

// Checks to see if theres a shape to the left - will stop shape from moving in that direction
void grid::against_shape_left(tetris &tetris) {
    bool result {false};
    std::vector<sf::Vector2f> temp;
    temp = tetris.return_live_coords();
    for (size_t i = 0; i < temp.size(); i++) {
        // Checks to left of shape
        if (grid_coords[temp[i].y][temp[i].x - 1] < 7) {
            result = true;
        }
    }
    tetris.against_shape_left_side = result; 
}

// Checks to see if theres a shape to bottom right (45 degree angle) - will stop shape from moving in that direction
void grid::against_shape_right_angle(tetris &tetris) {
    bool result {false};
    std::vector<sf::Vector2f> temp;
    temp = tetris.return_live_coords();
    for (size_t i = 0; i < temp.size(); i++) {
        if (temp[i].y != 24) {
            if (grid_coords[temp[i].y + 1][temp[i].x + 1] < 7) {
                result = true;
            }
        }
    }
    tetris.against_shape_right_side = result;
}

// Checks to see if theres a shape to bottom left (45 degree angle) - will stop shape from moving in that direction
void grid::against_shape_left_angle(tetris &tetris) {
    bool result{false};
    std::vector<sf::Vector2f> temp;
    temp = tetris.return_live_coords();
    for (size_t i = 0; i < temp.size(); i++) {
        // Checks to left of shape & down 45 degree angle
        if (temp[i].y != 24) {
            if (grid_coords[temp[i].y + 1][temp[i].x - 1] < 7) {
                result = true;
            }
        }
    }
    tetris.against_shape_left_side = result;
}

// Draws the area where the shape will land to make it easier for the player
void grid::draw_future_position(tetris tetris, sf::RenderWindow &window) {
    std::vector<sf::Vector2f> future_pos{};
    std::vector<sf::Vector2f> temp{};
    temp = tetris.return_live_coords();
    
    bool result {false};
    while (result == false) {
        for (size_t i = 0; i < temp.size(); i++) {
            // Calling function to check if the coords have collided with part of the grid
            if (bottom_of_grid(temp) == true || above_grid(temp) == true) {
                result = true;
                for (size_t i = 0; i < temp.size(); i++) {
                    temp[i].y --;
                }
            }
        }
        for (size_t i = 0; i < temp.size(); i++) {
            temp[i].y ++; // Increment the Y coord until it collides
        }
    }
    
    future_pos = temp;
    
    for (size_t i = 0; i < future_pos.size(); i++) { // Draws temporary shape to the grid
        grid_square.setPosition(sf::Vector2f(future_pos[i].x * 30, future_pos[i].y * 30));
        window.draw(grid_square);
    }
}

// Checks if coordinates are at the bottom of the grid
bool grid::bottom_of_grid(std::vector<sf::Vector2f> &temp) {
    bool result {false};
    for (size_t i = 0; i < temp.size(); i++) {
        if (temp[i].y == 24) {
            result = true;
        }
    }
    return result;
}

// Checks if coordinates are on top of another shape
bool grid::above_grid(std::vector<sf::Vector2f> &temp) {
    bool result{false};
    for (size_t i = 0; i < temp.size(); i++) {
        if (grid_coords[temp[i].y + 1][temp[i].x] < 7 && temp[i].y != 0 && temp[i].y != 1) {
            result = true;
        }
        else if (grid_coords[temp[i].y + 1][temp[i].x] < 7 && (temp[i].y == 0 || temp[i].y == 1)) {
            game_over = true;
        }
    }
    return result;
}

int grid::return_points() {
    return points;
}




#include "tetris.hpp"
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <iostream>

tetris::tetris() {
    // No rotation points
    this->spawn_coords.push_back(I); // 0 - Colour: Red
    this->spawn_coords.push_back(O); // 1 - Color: Orange
//     Rotation points = index 0
    this->spawn_coords.push_back(L); // 2 - Coloru: Green
    this->spawn_coords.push_back(T); // 3 - Colour: Blue
    this->spawn_coords.push_back(S); // 4 - Colour: Yellow
    this->spawn_coords.push_back(Z); // 5 - Colour: Magenta
    this->spawn_coords.push_back(J); // 6 - Colour: Cyan
    
    this->tetris_active = false;
    
    this->rotate_left_coords.push_back(sf::Vector2f(0,1));
    this->rotate_left_coords.push_back(sf::Vector2f(-1,0));
    this->rotate_right_coords.push_back(sf::Vector2f(0,-1));
    this->rotate_right_coords.push_back(sf::Vector2f(1,0));
    
    this->I_tetris_active = false;
    this->O_tetris_active = false;
    
    this->rotate_left = false;
    this->rotate_right = false;
    
    // Collision detection
    this->against_shape_left_side = false;
    this->against_shape_right_side = false;
    
    this->first_spawn = true;
}

void tetris::spawn_tetris(float &min_time) {
    if (tetris_active == false && first_spawn == true) {
        int i = rand() % 6;
        live_coords = spawn_coords[i];
        rotation_point = live_coords[0];
        colour = i;
        min_time = 0.2;
        calculate_next_coords();
        tetris_active = true;
        first_spawn = false;
    }
    else if (tetris_active == false) {
        live_coords = next_coords;
        rotation_point = live_coords[0];
        colour = next_colour_index;
        min_time = 0.2;
        calculate_next_coords();
        tetris_active = true;
    }
}

void tetris::draw_tetris(sf::RenderWindow &window) {
    for (size_t i = 0; i < live_coords.size(); i++) {
        sf::RectangleShape block;
        block.setSize(sf::Vector2f(30,30));
        
        if (colour == 0)
           block.setFillColor(sf::Color::Red);
        else if (colour == 1)
           block.setFillColor(sf::Color(255,165,0)); // Orange
        else if (colour == 2)
           block.setFillColor(sf::Color::Green);
        else if (colour == 3)
           block.setFillColor(sf::Color::Blue);
        else if (colour == 4)
           block.setFillColor(sf::Color::Yellow);
        else if (colour == 5)
           block.setFillColor(sf::Color::Magenta); // Pink
        else if (colour == 6)
           block.setFillColor(sf::Color::Cyan); // Light Blue

        sf::Vector2f temp;
        temp = sf::Vector2f(live_coords[i].x * 30, live_coords[i].y * 30);
        block.setPosition(temp);
        window.draw(block);
    }
}

void tetris::drop_shape() {
    for (size_t i = 0; i < live_coords.size(); i++) {
        live_coords[i].y += 1;
    }
    this->rotation_point = live_coords[0]; 
}

void tetris::move_sideways(sf::RenderWindow &window) {
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
           if (this->against_left_side() == false && this->against_shape_left_side == false) {
              for (size_t i = 0; i < live_coords.size(); i++) {
                 live_coords[i].x -= 1;
              }
           }
       }
    
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
           if (this->against_right_side() == false && this->against_shape_right_side == false) {
             for (size_t i = 0; i < live_coords.size(); i++) {
                live_coords[i].x += 1;
             }
           }
       }
}

void tetris::rotate(sf::RenderWindow &window) {
    // Rotate Left
    if (rotate_left == true && against_left_side() == false && against_right_side() == false && against_shape_left_side == false && against_shape_right_side == false) {
           for (size_t i = 0; i < live_coords.size(); i++) {
               if (i != 0) {
                   sf::Vector2f VR;
                   VR.x = live_coords[i].x - rotation_point.x;
                   VR.y = live_coords[i].y - rotation_point.y;
                   sf::Vector2f VT;
                   VT.x = (rotate_left_coords[0].x * (VR.x) + (rotate_left_coords[1].x) * VR.y);
                   VT.y = (rotate_left_coords[0].y * (VR.x) + (rotate_left_coords[1].y) * VR.y);
                   sf::Vector2f V;
                   V.x = rotation_point.x + VT.x;
                   V.y = rotation_point.y + VT.y;
                   live_coords[i].x = V.x;
                   live_coords[i].y = V.y;
               }
           }
        rotate_left = false;
    }
    // Rotate Right
    if (rotate_right == true && against_left_side() == false && against_right_side() == false && against_shape_left_side == false && against_shape_right_side == false) {
        for (size_t i = 0; i < live_coords.size(); i++) {
                if (i != 0) {
                    sf::Vector2f VR;
                    VR.x = live_coords[i].x - rotation_point.x;
                    VR.y = live_coords[i].y - rotation_point.y;
                    sf::Vector2f VT;
                    VT.x = (rotate_right_coords[0].x * (VR.x) + (rotate_right_coords[1].x) * VR.y);
                    VT.y = (rotate_right_coords[0].y * (VR.x) + (rotate_right_coords[1].y) * VR.y);
                    sf::Vector2f V;
                    V.x = rotation_point.x + VT.x;
                    V.y = rotation_point.y + VT.y;
                    live_coords[i].x = V.x;
                    live_coords[i].y = V.y;
                }
        }
        rotate_right = false; 
    }
}

bool tetris::against_left_side() {
    bool result {false};
    for (size_t i = 0; i < live_coords.size(); i++) {
        if (live_coords[i].x == 0) {
            result = true;
        }
    }
    return result; 
}

bool tetris::against_right_side() {
    bool result {false};
    for (size_t i = 0; i < live_coords.size(); i++) {
        if (live_coords[i].x == 9) {
            result = true;
        }
    }
    return result; 
}

std::vector<sf::Vector2f> tetris::return_live_coords() {
    return live_coords;
}

std::vector<sf::Vector2f> tetris::return_next_coords() {
    return next_coords;
}

int tetris::return_next_colour() {
    return next_colour_index;
}

void tetris::calculate_next_coords() {
    int i = rand() % 6;
    next_coords = spawn_coords[i];
    next_colour_index = i; 
}

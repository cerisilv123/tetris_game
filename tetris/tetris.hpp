
#ifndef tetris_hpp
#define tetris_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

class tetris {
private:
    std::vector <std::vector<sf::Vector2f>> spawn_coords;
    std::vector <sf::Vector2f> O {sf::Vector2f(3,0), sf::Vector2f(4,0), sf::Vector2f(3,1), sf::Vector2f(4,1)};
    std::vector <sf::Vector2f> I {sf::Vector2f(3,0), sf::Vector2f(4,0), sf::Vector2f(5,0), sf::Vector2f(6,0)};
    std::vector <sf::Vector2f> T {sf::Vector2f(4,0), sf::Vector2f(3,0), sf::Vector2f(4,1), sf::Vector2f(5,0)};
    std::vector <sf::Vector2f> L {sf::Vector2f(4,0), sf::Vector2f(3,0), sf::Vector2f(3,1), sf::Vector2f(5,0)};
    std::vector <sf::Vector2f> J {sf::Vector2f(4,0), sf::Vector2f(3,0), sf::Vector2f(5,0), sf::Vector2f(5,1)};
    std::vector <sf::Vector2f> Z {sf::Vector2f(4,1), sf::Vector2f(3,0), sf::Vector2f(4,0), sf::Vector2f(5,1)};
    std::vector <sf::Vector2f> S {sf::Vector2f(4,1), sf::Vector2f(4,0), sf::Vector2f(5,0), sf::Vector2f(3,1)};
    std::vector <sf::Vector2f> live_coords; 
    std::vector <sf::Vector2f> next_coords;
    sf::Vector2f rotation_point;
    std::vector<sf::Vector2f> rotate_left_coords;
    std::vector<sf::Vector2f> rotate_right_coords;
    bool I_tetris_active;
    bool O_tetris_active;
public:
    tetris();
    int colour{};
    bool tetris_active; // RESET
    bool first_spawn; // RESET
    int next_colour_index{}; 
    bool rotate_left;
    bool rotate_right; 
    void spawn_tetris(float &min_time);
    void draw_tetris(sf::RenderWindow & window);
    void move_sideways(sf::RenderWindow & window);
    void rotate(sf::RenderWindow & window);
    bool against_left_side();
    bool against_right_side();
    bool against_shape_left_side;
    bool against_shape_right_side;
    std::vector<sf::Vector2f> return_live_coords();
    std::vector<sf::Vector2f> return_next_coords();
    int return_next_colour();
    void drop_shape();
    void calculate_next_coords();
};

#endif /* tetris_hpp */

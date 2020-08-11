
#include "scoreboard.hpp"
#include <iostream>

void scoreboard::draw_seperating_line(sf::RenderWindow &window) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(300,0)),
        sf::Vertex(sf::Vector2f(300,750))
    };
    window.draw(line, 2, sf::Lines);
}

void scoreboard::draw_next_shape(sf::RenderWindow &window, tetris &tetris) {
    
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error loading font from file" << std::endl;
        window.close();
    }
    
    sf::Text text;
    text.setFont(font);
    text.setString("Next Piece:");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(320, 30));
    
    
    std::vector<sf::Vector2f> temp;
    temp = tetris.return_next_coords();
    int colour = tetris.return_next_colour();
    
    for (size_t i = 0; i < temp.size(); i++) {
        sf::RectangleShape block;
        block.setPosition(sf::Vector2f((temp[i].x + 8.6) * 30, (temp[i].y + 3)* 30));
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
            block.setFillColor(sf::Color::Cyan); // Light
        
        window.draw(text); 
        window.draw(block); 
    }
}

void scoreboard::draw_score(sf::RenderWindow &window, grid &grid) {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error loading font from file" << std::endl;
        window.close();
    }
       
    int points = grid.return_points();
    std::string points_text = std::to_string(points);
    std::string score = "Score: ";
    score.append(points_text);
    
    sf::Text text;
    text.setFont(font);
    text.setString(score);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(320, 220));
    
    window.draw(text);
}

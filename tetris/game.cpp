
#include "game.hpp"

game::game()  {
    this->game_active = false;
}

// Displays menu
void game::display_menu(sf::RenderWindow &window) {
    while (this->game_active == false) {
        
        // Clear Screen
        window.clear();
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->game_active = true;
                window.close();
            }
        }
        
        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            std::cerr << "Error loading font from file" << std::endl;
            window.close();
        }
        
        sfe::RichText text(font);
        text << sf::Color::Red << "T"
           << sf::Color(255,165,0) << "E"
           << sf::Color::Green << "T"
           << sf::Color::Blue << "R"
           << sf::Color::Magenta << "I"
           << sf::Color::Cyan << "S";
        
        text.setCharacterSize(120);
        text.setPosition(sf::Vector2f(260, 375));
        sf::FloatRect width = text.getGlobalBounds();
        text.setOrigin(sf::Vector2f(width.width / 2, width.width / 2));
    
        sf::Text text2;
        text2.setFont(font);
        text2.setCharacterSize(30);
        text2.setString("Press Spacebar To Play");
        text2.setPosition(sf::Vector2f(260, 550));
        sf::FloatRect width2 = text2.getGlobalBounds();
        text2.setOrigin(sf::Vector2f(width2.width / 2, width2.width / 2));
        
        window.draw(text);
        window.draw(text2);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            this->game_active = true;
        }
        
        // Display Screen
        window.display();
    }
}

// Manages the whole game flow
void game::play_game() {
    sf::RenderWindow window(sf::VideoMode(520,750), "Tetris" );
        
        // Playing theme song
        sf::Music music;
        if (!music.openFromFile("tetris_theme.wav")) {
            std::cerr << "Error Playing Music" << std::endl;
        }
        music.play();
        
        // Creating Objects
        grid Grid;
        tetris Tetris;
        scoreboard Scoreboard;
        
        // Handling Time
        sf::Clock clock;
        float min_time = 0.2;
        
        while (window.isOpen()) {
            
            // Handle Events
            sf::Event event;
            while(window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            
            
            float delta_time = clock.getElapsedTime().asSeconds();
            if (delta_time > min_time) {
                
                // Clear Screen
                window.clear();
                
                // Display Menu
                this->reset_game(Grid, Tetris);
                display_menu(window);
                
                Tetris.spawn_tetris(min_time);
                Grid.delete_line(Tetris, window, min_time);
                Grid.against_shape_left(Tetris);
                Grid.against_shape_right(Tetris);
                Grid.against_shape_left_angle(Tetris);
                Grid.against_shape_right_angle(Tetris);
                Grid.draw_future_position(Tetris, window);
                Grid.draw_grid(window, Tetris);
                Scoreboard.draw_seperating_line(window);
                Scoreboard.draw_next_shape(window, Tetris);
                Scoreboard.draw_score(window, Grid);
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                    min_time = 0.02;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
                    Tetris.rotate_left = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    Tetris.rotate_right = true;
                }
                
                if (Grid.has_collided_bottom(Tetris) == false && Grid.has_collided_grid(Tetris) == false) {
                    Tetris.drop_shape();
                    Tetris.move_sideways(window);
                    Tetris.rotate(window);
                }
                
                Tetris.draw_tetris(window);
                
                // Display Screen
                window.display();
                // Reset Clock
                clock.restart();
                
            }
        }
}

// Resets variables when the player loses
void game::reset_game(grid &grid, tetris &tetris) {
    if (grid.game_over == true) {
        grid.game_over = false;
        grid.points = 0;
        grid.line_deleted = false;
        grid.grid_coords = {
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
        
        tetris.tetris_active = false;
        tetris.first_spawn = true;
        
        this->game_active = false;
    }
}

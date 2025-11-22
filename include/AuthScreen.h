#ifndef AUTHSCREEN_H
#define AUTHSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Database.h"

class AuthScreen {
public:
    AuthScreen();
    void run();
    
private:
    void handleEvents();
    void render();
    bool validatePassword(const std::string& password);
    void handleMouseClick(int x, int y);
    
    sf::RenderWindow window;
    Database db;
    sf::Font font;
    
    std::string emailInput;
    std::string passwordInput;
    std::string message;
    int attempts;
    bool emailFieldActive;
    
    sf::RectangleShape emailBox;
    sf::RectangleShape passwordBox;
    sf::RectangleShape recoveryButton;
};

#endif

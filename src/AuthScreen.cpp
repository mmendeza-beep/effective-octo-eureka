#include "AuthScreen.h"
#include "PasswordValidator.h"
#include <iostream>

AuthScreen::AuthScreen() 
    : window(sf::VideoMode(800, 600), "Pantalla de Autenticacion"),
      db("auth.db"),
      attempts(0),
      emailFieldActive(true),
      message("") {
    db.initialize();
    
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error cargando fuente" << std::endl;
    }
    
    // Email box
    emailBox.setSize(sf::Vector2f(400, 50));
    emailBox.setPosition(200, 200);
    emailBox.setFillColor(sf::Color(50, 50, 50));
    emailBox.setOutlineThickness(2);
    emailBox.setOutlineColor(sf::Color(100, 200, 255));
    
    // Password box
    passwordBox.setSize(sf::Vector2f(400, 50));
    passwordBox.setPosition(200, 280);
    passwordBox.setFillColor(sf::Color(50, 50, 50));
    passwordBox.setOutlineThickness(2);
    passwordBox.setOutlineColor(sf::Color(150, 150, 150));
    
    // Recovery button
    recoveryButton.setSize(sf::Vector2f(200, 40));
    recoveryButton.setPosition(300, 360);
    recoveryButton.setFillColor(sf::Color(70, 70, 70));
    recoveryButton.setOutlineThickness(2);
    recoveryButton.setOutlineColor(sf::Color(100, 100, 100));
}

void AuthScreen::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

void AuthScreen::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                char c = static_cast<char>(event.text.unicode);
                
                if (c == '\b') {
                    if (emailFieldActive && !emailInput.empty()) {
                        emailInput.pop_back();
                    } else if (!emailFieldActive && !passwordInput.empty()) {
                        passwordInput.pop_back();
                    }
                } else if (c == '\r' || c == '\n') {
                    if (emailFieldActive) {
                        emailFieldActive = false;
                        passwordBox.setOutlineColor(sf::Color(100, 200, 255));
                        emailBox.setOutlineColor(sf::Color(150, 150, 150));
                    } else {
                        if (validatePassword(passwordInput)) {
                            if (db.validateUser(emailInput, passwordInput)) {
                                message = "Autenticacion exitosa!";
                                std::cout << message << std::endl;
                            } else {
                                attempts++;
                                message = "Credenciales invalidas. Intentos: " + std::to_string(attempts) + "/5";
                                if (attempts >= 5) {
                                    message = "Maximo de intentos alcanzado.";
                                    std::cout << message << std::endl;
                                    sf::sleep(sf::seconds(2));
                                    window.close();
                                }
                                passwordInput.clear();
                            }
                        } else {
                            message = "Contrasena debe tener 5-10 chars, 1 mayuscula, 1 especial";
                            passwordInput.clear();
                        }
                    }
                } else if (c == '\t') {
                    emailFieldActive = !emailFieldActive;
                    if (emailFieldActive) {
                        emailBox.setOutlineColor(sf::Color(100, 200, 255));
                        passwordBox.setOutlineColor(sf::Color(150, 150, 150));
                    } else {
                        passwordBox.setOutlineColor(sf::Color(100, 200, 255));
                        emailBox.setOutlineColor(sf::Color(150, 150, 150));
                    }
                } else {
                    if (emailFieldActive) {
                        emailInput += c;
                    } else if (passwordInput.length() < 10) {
                        passwordInput += c;
                    }
                }
            }
        }
    }
}

void AuthScreen::handleMouseClick(int x, int y) {
    if (emailBox.getGlobalBounds().contains(x, y)) {
        emailFieldActive = true;
        emailBox.setOutlineColor(sf::Color(100, 200, 255));
        passwordBox.setOutlineColor(sf::Color(150, 150, 150));
    } else if (passwordBox.getGlobalBounds().contains(x, y)) {
        emailFieldActive = false;
        passwordBox.setOutlineColor(sf::Color(100, 200, 255));
        emailBox.setOutlineColor(sf::Color(150, 150, 150));
    } else if (recoveryButton.getGlobalBounds().contains(x, y)) {
        message = "Recuperacion de clave via email: " + emailInput;
        std::cout << message << std::endl;
    }
}

void AuthScreen::render() {
    window.clear(sf::Color(30, 30, 30));
    
    // Title
    sf::Text title("AUTENTICACION", font, 48);
    title.setFillColor(sf::Color(100, 200, 255));
    title.setPosition(250, 80);
    window.draw(title);
    
    // Email label
    sf::Text emailLabel("Email:", font, 20);
    emailLabel.setFillColor(sf::Color::White);
    emailLabel.setPosition(200, 170);
    window.draw(emailLabel);
    
    // Email box and text
    window.draw(emailBox);
    sf::Text emailText(emailInput, font, 24);
    emailText.setFillColor(sf::Color::White);
    emailText.setPosition(210, 210);
    window.draw(emailText);
    
    // Password label
    sf::Text passwordLabel("Contrasena:", font, 20);
    passwordLabel.setFillColor(sf::Color::White);
    passwordLabel.setPosition(200, 250);
    window.draw(passwordLabel);
    
    // Password box and text (masked)
    window.draw(passwordBox);
    std::string maskedPassword(passwordInput.length(), '*');
    sf::Text passwordText(maskedPassword, font, 24);
    passwordText.setFillColor(sf::Color::White);
    passwordText.setPosition(210, 290);
    window.draw(passwordText);
    
    // Recovery button
    window.draw(recoveryButton);
    sf::Text recoveryText("Recuperar Clave", font, 18);
    recoveryText.setFillColor(sf::Color::White);
    recoveryText.setPosition(320, 370);
    window.draw(recoveryText);
    
    // Message
    if (!message.empty()) {
        sf::Text messageText(message, font, 16);
        messageText.setFillColor(sf::Color(255, 100, 100));
        messageText.setPosition(150, 450);
        window.draw(messageText);
    }
    
    // Instructions
    sf::Text instructions("Tab para cambiar campo | Enter para enviar", font, 14);
    instructions.setFillColor(sf::Color(150, 150, 150));
    instructions.setPosition(220, 520);
    window.draw(instructions);
    
    window.display();
}

bool AuthScreen::validatePassword(const std::string& password) {
    return PasswordValidator::validate(password);
}

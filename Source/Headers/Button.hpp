#pragma once
#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Button
{
protected:
    sf::Color color_ = sf::Color::Red;
    sf::Font font_;
    const sf::Vector2f frameSize_  {400.f, 100.f};
    bool status_ = false;
    sf::Vector2f position_ {400.f, 400.f};
    sf::RectangleShape frame_;
    std::string textToPrint_ = "Button";
    sf::Text text_;

public:
    Button(const sf::Vector2f position, const std::string textToPrint);
    ~Button() = default;

    void draw(sf::RenderWindow& i_window);
    void setStatus(const bool newStatus);
    
    bool getStatus();

};
#endif


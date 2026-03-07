#include "Headers/Button.hpp"

Button::Button(const sf::Vector2f position, const std::string textToPrint)
    : position_(position)
    , textToPrint_(textToPrint)
{
    font_.loadFromFile("Images/Arial.ttf");
    text_.setFont(font_);
    text_.setPosition(position_);
    text_.setFillColor(sf::Color::Red);
    text_.setCharacterSize(50);
    text_.setStyle(sf::Text::Bold);
    text_.setString(textToPrint);
    
    frame_.setPosition(sf::Vector2f(position_.x - 25, position_.y - 20));
    frame_.setSize(frameSize_);
    frame_.setFillColor(sf::Color::Black);
    frame_.setOutlineColor(sf::Color::White);
    frame_.setOutlineThickness(5.f);
}

void Button::setStatus(const bool newStatus)
{
    status_ = newStatus;
}

void Button::draw(sf::RenderWindow& i_window)
{   
    if(status_)
    {
        text_.setFillColor(sf::Color::Green);
    }
    else
    {
        text_.setFillColor(sf::Color::Red);
    }
    i_window.draw(frame_);
    i_window.draw(text_);
}

bool Button::getStatus()
{
    return this->status_;
}


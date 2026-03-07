#pragma once
#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>
#include <thread>
#include <vector>
#include "Button.hpp"

using Time = std::chrono::time_point<std::chrono::steady_clock>;

class Menu
{
protected:
    std::array<Button, 2> buttons_{Button(sf::Vector2f(400.f, 400.f), "PLAY"),
                                   Button(sf::Vector2f(400.f, 550.f), "EXIT")};

    unsigned int deltaTime = 0;
    bool optionConfirmed_ = false;
    Time previousOptionChangeTime_;
    enum class Selected
    {
        PLAY = 0,
        EXIT = 1
    };
    Selected selected_ = Selected::PLAY;

public:
    Menu();
    ~Menu() = default;
    
    void changeSelected();
    void confirmOption();
    void drawButtons(sf::RenderWindow& i_window);
    void organizeButtons();

    bool getOptionConfirmed();
    Selected getSelected();

    void setOptionConfirmed(bool newStatus);
};
#endif


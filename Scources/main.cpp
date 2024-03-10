#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <complex>
#include <array>
#include <vector>
#include <cmath>
#include <chrono>
#include <iostream>

#include "InputEventParser.h"
#include "MySprite.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    my_game::Formula1Sprite car;
    car.SetPosition({100, 100});
    car.SetRotation(my_game::MySprite::CosSin(-1));
    car.RedrawSprite();

    sf::CircleShape circle(100);
    circle.setPosition(0, 0);
    circle.setFillColor(sf::Color::Green);

    window.clear(sf::Color(255,255,255,0));
    window.draw(circle);
    car.DrawSprite(window);
    window.display();

    my_game::InputEventParser event_parser(window);

    while (window.isOpen())
    {
        event_parser.ReadEvents();
        if(event_parser.HasUpdate())
        {
            std::cout << "throttle " << event_parser.GetThrottle() << " steering " << event_parser.GetSteering() << std::endl;
        }
        if(event_parser.IsClosed())
        {
            window.close();
        }
    }

    return 0;
}

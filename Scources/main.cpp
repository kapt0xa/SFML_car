#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <complex>
#include <array>
#include <vector>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    sf::RenderTexture rend_texture;

    sf::CircleShape circle(10.f);
    circle.setFillColor(sf::Color(0, 255, 0, 255));
    circle.setPosition(10.f, 10.f);

    rend_texture.create(100u, 50u);
    rend_texture.clear(sf::Color(0,0,255,255));
    rend_texture.draw(circle);

    sf::IntRect int_rect;
    int_rect.height = 50;
    int_rect.width = 100;
    int_rect.left = 0;
    int_rect.top = 0;
    sf::Sprite sprite(rend_texture.getTexture(), int_rect);

    window.clear(sf::Color::Black);
    window.draw(sprite);
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

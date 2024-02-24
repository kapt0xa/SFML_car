#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <complex>
#include <array>
#include <vector>
#include <cmath>

sf::Sprite MakeCarSptite(sf::Texture& texture);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    /*
    {
        int line_width = 8;

        sf::RectangleShape rect;

        //size for spoiler's wheels
        rect.setSize(sf::Vector2f(30, line_width));

        //color for wheels
        rect.setFillColor(sf::Color::Black);

        //rear wheels
        rect.setPosition(orig_x + 55, orig_y - 60 - line_width/2);
        texture.draw(rect);
        rect.setPosition(orig_x + 55, orig_y + 60 - line_width/2);
        texture.draw(rect);

        //front wheels
        rect.setPosition(orig_x + 205, orig_y - 60 - line_width/2);
        texture.draw(rect);
        rect.setPosition(orig_x + 205, orig_y + 60 - line_width/2);
        texture.draw(rect);

        line_width = 4;

        //rear axis
        rect.setSize(sf::Vector2f(line_width, 120));
        rect.setPosition(orig_x + 70 - line_width/2, orig_y - 60);
        texture.draw(rect);

        //front axis
        rect.setSize(sf::Vector2f(line_width, 120));
        rect.setPosition(orig_x + 220 - line_width/2, orig_y - 60);
        texture.draw(rect);

        line_width = 2;

        //front wheel's steering system
        rect.setSize(sf::Vector2f(line_width, 104));
        rect.setPosition(orig_x + 210 - line_width/2, orig_y - 52);
        texture.draw(rect);

        //diagonal elements of steering system
        sf::ConvexShape polygon;
        polygon.setPointCount(4);
        polygon.setFillColor(sf::Color::Black);
        polygon.setPoint(0, sf::Vector2f(orig_x + 210, orig_y - 53));
        polygon.setPoint(1, sf::Vector2f(orig_x + 220, orig_y - 57));
        polygon.setPoint(2, sf::Vector2f(orig_x + 220, orig_y - 57 + line_width));
        polygon.setPoint(3, sf::Vector2f(orig_x + 210, orig_y - 53 + line_width));
        texture.draw(polygon);
        polygon.setPoint(3, sf::Vector2f(orig_x + 210, orig_y + 53 - line_width));
        polygon.setPoint(2, sf::Vector2f(orig_x + 220, orig_y + 57 - line_width));
        polygon.setPoint(1, sf::Vector2f(orig_x + 220, orig_y + 57));
        polygon.setPoint(0, sf::Vector2f(orig_x + 210, orig_y + 53));
        texture.draw(polygon);


        line_width = 4;
        //size for spoiler's winglets
        rect.setSize(sf::Vector2f(30, line_width));

        //color for body
        rect.setFillColor(sf::Color::Red);

        //rear winglets
        rect.setPosition(orig_x, orig_y - 60 - line_width/2);
        texture.draw(rect);
        rect.setPosition(orig_x, orig_y + 60 - line_width/2);
        texture.draw(rect);

        //front winglets
        rect.setPosition(orig_x + 255, orig_y - 60 - line_width/2);
        texture.draw(rect);
        rect.setPosition(orig_x + 255, orig_y + 60 - line_width/2);
        texture.draw(rect);

        //spoiler holders
        rect.setPosition(orig_x + 25, orig_y - 40 - line_width/2);
        texture.draw(rect);
        rect.setPosition(orig_x + 25, orig_y + 40 - line_width/2);
        texture.draw(rect);

        //size for spoiler
        rect.setSize(sf::Vector2f(20, 120));

        //spoiler
        rect.setPosition(orig_x + 5, orig_y - 60);
        texture.draw(rect);

        //front antiwing
        rect.setPosition(orig_x + 260, orig_y - 60);
        texture.draw(rect);

        //rear body part
        rect.setSize(sf::Vector2f(70, 100));
        rect.setPosition(orig_x + 50, orig_y - 50);
        texture.draw(rect);

        //front body part
        rect.setSize(sf::Vector2f(250 - 175, 40));
        rect.setPosition(orig_x + 175, orig_y - 20);
        texture.draw(rect);

        //middle triangular part
        polygon.setFillColor(sf::Color::Red);
        polygon.setPoint(0, sf::Vector2f(orig_x + 120, orig_y - 50));
        polygon.setPoint(1, sf::Vector2f(orig_x + 190, orig_y - 20));
        polygon.setPoint(2, sf::Vector2f(orig_x + 190, orig_y + 20));
        polygon.setPoint(3, sf::Vector2f(orig_x + 120, orig_y + 50));
        texture.draw(polygon);

        //round nose part
        sf::CircleShape circle;
        circle.setFillColor(sf::Color::Red);
        circle.setRadius(20);
        circle.setPosition(orig_x + 230, orig_y - 20);
        texture.draw(circle);

        //cockpit
        circle.setFillColor(sf::Color::Black);
        circle.setRadius(15);
        circle.setPosition(orig_x + 105, orig_y - 15);
        texture.draw(circle);
        circle.setPosition(orig_x + 145, orig_y - 15);
        texture.draw(circle);
        rect.setSize(sf::Vector2f(40, 30));
        rect.setPosition(125, orig_y - 15);
        rect.setFillColor(sf::Color::Black);
        texture.draw(rect);
    }
    //*/

    sf::Texture car_texture;
    sf::Sprite car_sprite = MakeCarSptite(car_texture);

    sf::CircleShape circle(100);
    circle.setPosition(50, 50);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255,255,255,0));
        window.draw(circle);
        window.draw(car_sprite);
        window.display();
    }

    return 0;
}

sf::Sprite MakeCarSptite(sf::Texture& texture)
{
    sf::RenderTexture rend_texture;
    constexpr int width = 300;
    constexpr int height = 140;
    constexpr int orig_x = 5;
    constexpr int orig_y = 70;
    rend_texture.clear(sf::Color::Green);
    {
        int line_width = 8;

        sf::RectangleShape rect;

        //size for spoiler's wheels
        rect.setSize(sf::Vector2f(30, line_width));

        //color for wheels
        rect.setFillColor(sf::Color::Black);

        //rear wheels
        rect.setPosition(orig_x + 55, orig_y - 60 - line_width/2);
        rend_texture.draw(rect);
        rect.setPosition(orig_x + 55, orig_y + 60 - line_width/2);
        rend_texture.draw(rect);

        //front wheels
        rect.setPosition(orig_x + 205, orig_y - 60 - line_width/2);
        rend_texture.draw(rect);
        rect.setPosition(orig_x + 205, orig_y + 60 - line_width/2);
        rend_texture.draw(rect);

        line_width = 4;

        //rear axis
        rect.setSize(sf::Vector2f(line_width, 120));
        rect.setPosition(orig_x + 70 - line_width/2, orig_y - 60);
        rend_texture.draw(rect);

        //front axis
        rect.setSize(sf::Vector2f(line_width, 120));
        rect.setPosition(orig_x + 220 - line_width/2, orig_y - 60);
        rend_texture.draw(rect);

        line_width = 2;

        //front wheel's steering system
        rect.setSize(sf::Vector2f(line_width, 104));
        rect.setPosition(orig_x + 210 - line_width/2, orig_y - 52);
        rend_texture.draw(rect);

        //diagonal elements of steering system
        sf::ConvexShape polygon;
        polygon.setPointCount(4);
        polygon.setFillColor(sf::Color::Black);
        polygon.setPoint(0, sf::Vector2f(orig_x + 210, orig_y - 53));
        polygon.setPoint(1, sf::Vector2f(orig_x + 220, orig_y - 57));
        polygon.setPoint(2, sf::Vector2f(orig_x + 220, orig_y - 57 + line_width));
        polygon.setPoint(3, sf::Vector2f(orig_x + 210, orig_y - 53 + line_width));
        rend_texture.draw(polygon);
        polygon.setPoint(3, sf::Vector2f(orig_x + 210, orig_y + 53 - line_width));
        polygon.setPoint(2, sf::Vector2f(orig_x + 220, orig_y + 57 - line_width));
        polygon.setPoint(1, sf::Vector2f(orig_x + 220, orig_y + 57));
        polygon.setPoint(0, sf::Vector2f(orig_x + 210, orig_y + 53));
        rend_texture.draw(polygon);


        line_width = 4;
        //size for spoiler's winglets
        rect.setSize(sf::Vector2f(30, line_width));

        //color for body
        rect.setFillColor(sf::Color::Red);

        //rear winglets
        rect.setPosition(orig_x, orig_y - 60 - line_width/2);
        rend_texture.draw(rect);
        rect.setPosition(orig_x, orig_y + 60 - line_width/2);
        rend_texture.draw(rect);

        //front winglets
        rect.setPosition(orig_x + 255, orig_y - 60 - line_width/2);
        rend_texture.draw(rect);
        rect.setPosition(orig_x + 255, orig_y + 60 - line_width/2);
        rend_texture.draw(rect);

        //spoiler holders
        rect.setPosition(orig_x + 25, orig_y - 40 - line_width/2);
        rend_texture.draw(rect);
        rect.setPosition(orig_x + 25, orig_y + 40 - line_width/2);
        rend_texture.draw(rect);

        //size for spoiler
        rect.setSize(sf::Vector2f(20, 120));

        //spoiler
        rect.setPosition(orig_x + 5, orig_y - 60);
        rend_texture.draw(rect);

        //front antiwing
        rect.setPosition(orig_x + 260, orig_y - 60);
        rend_texture.draw(rect);

        //rear body part
        rect.setSize(sf::Vector2f(70, 100));
        rect.setPosition(orig_x + 50, orig_y - 50);
        rend_texture.draw(rect);

        //front body part
        rect.setSize(sf::Vector2f(250 - 175, 40));
        rect.setPosition(orig_x + 175, orig_y - 20);
        rend_texture.draw(rect);

        //middle triangular part
        polygon.setFillColor(sf::Color::Red);
        polygon.setPoint(0, sf::Vector2f(orig_x + 120, orig_y - 50));
        polygon.setPoint(1, sf::Vector2f(orig_x + 190, orig_y - 20));
        polygon.setPoint(2, sf::Vector2f(orig_x + 190, orig_y + 20));
        polygon.setPoint(3, sf::Vector2f(orig_x + 120, orig_y + 50));
        rend_texture.draw(polygon);

        //round nose part
        sf::CircleShape circle;
        circle.setFillColor(sf::Color::Red);
        circle.setRadius(20);
        circle.setPosition(orig_x + 230, orig_y - 20);
        rend_texture.draw(circle);

        //cockpit
        circle.setFillColor(sf::Color::Black);
        circle.setRadius(15);
        circle.setPosition(orig_x + 105, orig_y - 15);
        rend_texture.draw(circle);
        circle.setPosition(orig_x + 145, orig_y - 15);
        rend_texture.draw(circle);
        rect.setSize(sf::Vector2f(40, 30));
        rect.setPosition(125, orig_y - 15);
        rect.setFillColor(sf::Color::Black);
        rend_texture.draw(rect);
    }
    texture.create(width, height);
    texture = rend_texture.getTexture();
    sf::Sprite sprite;
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setTexture(texture);
    sprite.setPosition(100,100);
    //sprite.setPosition(-orig_x-70, -orig_y);
    return sprite;
}

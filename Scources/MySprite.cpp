#include "MySprite.h"

#include <cmath>

namespace my_game
{
    float MySprite::GetScale() const noexcept
    {
        return scale;
    }
    MySprite& MySprite::SetScale(float val) noexcept
    {
        scale = val;
        return *this;
    }

    FCompl MySprite::GetPosition() const noexcept
    {
        return position;
    }
    MySprite& MySprite::SetPosition(FCompl val) noexcept
    {
        position = val;
        return *this;
    }

    FCompl MySprite::GetRotation() const noexcept
    {
        return rotation;
    }
    MySprite& MySprite::SetRotation(FCompl val) noexcept
    {
        rotation = val;
        return *this;
    }

    MySprite& MySprite::MoveAbsolute(FCompl translation) noexcept
    {
        position += translation;
        return *this;
    }
    MySprite& MySprite::MoveRelative(FCompl translation) noexcept
    {
        position += translation * rotation;
        return *this;
    }
    MySprite& MySprite::Turn(FCompl additional_rotation) noexcept
    {
        rotation *= additional_rotation;
        return *this;
    }
    MySprite& MySprite::Inflate(float additional_scale) noexcept
    {
        scale *= additional_scale;
        return *this;
    }
    MySprite& MySprite::NormaliseRotationFast() noexcept
    {
        float abs2 = rotation.imag() * rotation.imag() + rotation.real() * rotation.real();
        rotation *= FCompl{ 1.5f - abs2/ 2, 0};
        return *this;
    }
    MySprite& MySprite::NormaliseRotation()
    {
        float abs2 = rotation.imag() * rotation.imag() + rotation.real() * rotation.real();
        rotation *= FCompl{1 / std::sqrt(abs2), 0};
        return *this;
    }

    const sf::Sprite MySprite::GetSprite() const noexcept
    {
        return sprite;
    }

    void MySprite::DrawSprite(sf::RenderTarget& render_target) const
    {
        render_target.draw(sprite, sf::Transform(   rotation.real() * scale,    rotation.imag() * scale,    position.real(),
                                                    -rotation.imag() * scale,   rotation.real() * scale,    position.imag(),
                                                    0, 0, 1));
    }

    FCompl MySprite::CosSin(float radian_angle)
    {
        return {std::cos(radian_angle), std::sin(radian_angle)};
    }

    float MySprite::ACosSin(FCompl a_rotation)
    {
        float abs = std::sqrt(a_rotation.real() * a_rotation.real() + a_rotation.imag() * a_rotation.imag());
        a_rotation /= abs;
        constexpr float sqrt_half = 0.70710678118f;
        if(std::abs(a_rotation.real()) < sqrt_half)
        {
            if(a_rotation.imag() > 0)
            {
                return std::acos(a_rotation.real());
            }
            else
            {
                return -std::acos(a_rotation.real());
            }
        }
        else
        {
            if(a_rotation.real() > 0)
            {
                return std::asin(a_rotation.real());
            }
            else
            {
                if(a_rotation.imag() > 0)
                {
                    return pi - std::asin(a_rotation.real());
                }
                else
                {
                    return -pi - std::asin(a_rotation.real());
                }
            }
        }
    }

    Formula1Sprite& Formula1Sprite::RedrawSprite()
    {

        constexpr int width = 300;
        constexpr int height = 140;
        constexpr int orig_x = 5;
        constexpr int orig_y = 70;

        sf::IntRect int_rect;
        int_rect.width = width;
        int_rect.height = height;
        texture.create(static_cast<unsigned>(width), static_cast<unsigned>(height));
        texture.clear(sf::Color(0, 255, 0, 0));
        {
            int line_width;

            sf::RectangleShape rect;


            //for axises
            line_width = 4;
            rect.setFillColor(axis_color);
            rect.setSize(sf::Vector2f(line_width, 120));

            //rear axis
            rect.setPosition(orig_x + 70 - line_width/2, orig_y - 60);
            texture.draw(rect);

            //front axis
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
            polygon.setFillColor(axis_color);
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



            //for wheels
            line_width = 8;
            rect.setSize(sf::Vector2f(30, line_width));
            rect.setFillColor(tyres_color);

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
        sprite = sf::Sprite(texture.getTexture(), int_rect);
        sprite.setOrigin(orig_x + 70, orig_y); //the origin is between rear wheels, in the middle of rear axis
        return *this;
    }

    MySprite& Formula1Sprite::AsSprite() noexcept
    {
        return *this;
    }
    const MySprite& Formula1Sprite::AsSprite() const noexcept
    {
        return *this;
    }
}

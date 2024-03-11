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
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

    my_game::Formula1Sprite car;
    car.SetPosition({100, 100});
    car.SetRotation(my_game::MySprite::CosSin(0));
    car.glass_color = sf::Color::Cyan;
    car.RedrawSprite();

    sf::CircleShape circle(100);
    circle.setPosition(0, 0);
    circle.setFillColor(sf::Color::Green);

    window.clear(sf::Color(255,255,255,0));
    window.draw(circle);
    car.DrawSprite(window);
    window.display();

    my_game::InputEventParser event_parser(window);

    float const acceleration = 50;
    float speed = 0; // length per second. lenght is measured in pixels, i guess.
    float steering = 0; // radians per meter lenght
    const float max_speed = 300;
    const float max_reverse_spped = -100;
    const float max_steering = 0.005;
    const float steering_speed = max_steering;
    const float passive_decelleration = acceleration / 10;
    const float passive_desteer = steering_speed / 2;
    bool is_braking = false;
    bool is_standing_on_brake = false;
    const float break_time = 0.5; // time of standing on brake before going reverse;
    const float slow_speed_steering = 50;
    const float braking_acceleration_multiplyer = 2;

    sf::Clock clock;
    sf::Clock brake_timer;

    while (window.isOpen())
    {
        float d_time = clock.getElapsedTime().asSeconds();
        clock.restart();
        event_parser.ReadEvents();
        if(event_parser.IsClosed())
        {
            window.close();
            continue;
        }

        //-codesep1---^ delta time and window close managing ^---v speed and input managing v---------------------------------------------------------------------

        float d_speed = acceleration * d_time * event_parser.GetThrottle();
        float d_friction = passive_decelleration * d_time;

        if(speed == 0)
        {
            if(is_braking) // if we still hold break button, that is same as opposite accelerate button, we don't accelerate opposite
            {
                if(d_speed == 0) // as soon as we let go the break button, we can go again
                {
                    is_braking = false;
                    is_standing_on_brake = false;
                }
                else if(is_standing_on_brake)
                {
                    if (brake_timer.getElapsedTime().asSeconds() > break_time)
                    {
                        is_braking = false;
                        is_standing_on_brake = false;
                    }
                }
                else
                {
                    is_standing_on_brake = true;
                    brake_timer.restart();
                }
            }
            else
            {
                speed += d_speed;
            }
        }

        //-codesep1---^ null speed ^---v positive speed v---------------------------------------------------------------------

        else if(speed > 0)
        {
            if(d_speed == 0) // no throttle, no braking, passive slow down
            {
                is_braking = false;
                speed -= d_friction;
                if(speed < 0) // stop by friction, not go reverse
                {
                    speed = 0;
                }
            }
            else
            {
                if(d_speed > 0) // accelerate forward
                {
                    is_braking = false;
                    if(speed <= max_speed) // not overspeed
                    {
                        speed += d_speed;
                    }
                }
                else // brake down
                {
                    is_braking = true;
                    speed += d_speed * braking_acceleration_multiplyer;
                    if(speed < 0) // stop, not go reverse
                    {
                        speed = 0;
                    }
                }
            }
        }

        //-codesep1---^ positive_speed ^---v negative_speed v---------------------------------------------------------------------

        else
        {
            if(d_speed == 0) // no throttle, no braking, passive slow down
            {
                is_braking = false;
                speed += d_friction;
                if(speed > 0) // stop by friction, not go reverse
                {
                    speed = 0;
                }
            }
            else
            {
                if(d_speed < 0) // reverse acceleration
                {
                    is_braking = false;
                    if(speed >= max_reverse_spped) // not overspeed in reverse
                    {
                        speed += d_speed;
                    }
                }
                else // brake in reverse
                {
                    is_braking = true;
                    speed += d_speed * braking_acceleration_multiplyer;
                    if(speed > 0) // stop, not go forward
                    {
                        speed = 0;
                    }
                }
            }
        }

        //-codesep1---^ speed and input managing ^---v steering and input managing v---------------------------------------------------------------------

        float d_steer = steering_speed * d_time * event_parser.GetSteering();
        float d_desteer = passive_desteer * d_time;

        if(speed > slow_speed_steering)
        {
            if((steering > 0 && d_steer > 0) ||
               (steering < 0 && d_steer <0))
            {
                d_steer *= slow_speed_steering / speed;
            }
        }

        steering += d_steer; // adjust steering by input
        if(steering > max_steering) // keep steering inside right limit
        {
            steering = max_steering;
        }
        else if(steering < -max_steering) // keep steering inside left limit
        {
            steering = -max_steering;
        }

        if(steering > 0) // desteering right
        {
            if(d_steer == 0)
            {
                steering -= d_desteer;
                if(steering < 0)
                {
                    steering = 0;
                }
            }
        }
        else if(steering < 0) // desteering left
        {
            if(d_steer == 0)
            {
                steering += d_desteer;
                if(steering > 0)
                {
                    steering = 0;
                }
            }
        }

        //-codesep1---^ steering and input managing ^---v speed and steering to move v---------------------------------------------------------------------

        float d_move = d_time * speed;
        my_game::FCompl d_turn = my_game::MySprite::CosSin(d_move * steering);
        car.MoveRelative({d_move, 0});
        car.Turn(d_turn);
        car.NormaliseRotationFast();

        window.clear(sf::Color::White);
        car.DrawSprite(window);
        window.display();
    }

    return 0;
}

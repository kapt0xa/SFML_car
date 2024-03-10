#include "InputEventParser.h"

#include <iostream>

namespace my_game
{

    void InputEventParser::HandleKeyPressed(const sf::Event& key_pressed_event, bool is_key_pressed) noexcept
    {
        bool is_branch_passed = true;
        switch (key_pressed_event.key.scancode)
        {

        case sf::Keyboard::Scancode::Up:
            {
                is_forward_pressed = is_key_pressed;
            }
            break;

        case sf::Keyboard::Scancode::Down:
            {
                is_backward_pressed = is_key_pressed;
            }
            break;

        case sf::Keyboard::Scancode::Left:
            {
                is_left_pressed = is_key_pressed;
            }
            break;

        case sf::Keyboard::Scancode::Right:
            {
                is_right_pressed = is_key_pressed;
            }
            break;

        default:
            {
                is_branch_passed = false;
            }
            break;
        }

        if(is_branch_passed)
        {
            has_update = true;
            throttle = (is_forward_pressed? 1 : 0) + (is_backward_pressed? -1 : 0);
            steering = (is_left_pressed? -1 : 0) + (is_right_pressed? 1 : 0);
        }

    }

    InputEventParser::InputEventParser(sf::RenderWindow& target_window_ref) noexcept
        : target_window(target_window_ref)
    {}

    void InputEventParser::ReadEvents()
    {
        sf::Event event;
        while (target_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                {
                    ++close_event_counter;
                    if(close_event_counter > max_close_requests)
                    {
                        std::cerr << "close event counter overfilled" << std::endl;
                        close_event_counter = max_close_requests;
                    }
                }
                break;

            case sf::Event::KeyPressed:
                {
                    HandleKeyPressed(event, true);
                }
                break;

            case sf::Event::KeyReleased:
                {
                    HandleKeyPressed(event, false);
                }
                break;

            default:
                {

                }
                break;
            }

        }
    }

    float InputEventParser::GetThrottle() noexcept
    {
        return throttle;
    }

    float InputEventParser::GetSteering() noexcept
    {

        return steering;
    }

    bool InputEventParser::IsClosed() noexcept
    {
        if(close_event_counter > 0)
        {
            --close_event_counter;
            return true;
        }

        return false;
    }

    bool InputEventParser::HasUpdate() noexcept
    {
        if(has_update)
        {
            has_update = false;
            return true;
        }
        return false;
    }
}

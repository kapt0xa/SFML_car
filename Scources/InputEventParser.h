#pragma once

#include <SFML/Graphics.hpp>

namespace my_game
{
    class InputEventParser
    {
    private:
        int close_event_counter = 0;
        static constexpr int max_close_requests = 10;
        bool is_forward_pressed = false;
        bool is_backward_pressed = false;
        bool is_left_pressed = false;
        bool is_right_pressed = false;
        float throttle = 0;
        float steering = 0;
        bool has_update = true;

        sf::RenderWindow& target_window;

        void HandleKeyPressed(const sf::Event& key_pressed_event, bool is_key_pressed) noexcept;

    public:
        InputEventParser(sf::RenderWindow& target_window_ref) noexcept;

        void ReadEvents();

        float GetThrottle() noexcept;
        float GetSteering() noexcept;
        bool IsClosed() noexcept;
        bool HasUpdate() noexcept;
    };
}

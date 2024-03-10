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
}

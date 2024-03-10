#pragma once

#include <SFML/Graphics.hpp>
#include <complex>

namespace my_game
{
    using FCompl = std::complex<float>;

    class MySprite
    {
    private:
        float scale = 1;
        FCompl position = {0, 0};
        FCompl rotation = {1, 0};
    protected:
        sf::RenderTexture texture;
        sf::Sprite sprite;
    public:
        float GetScale() const noexcept;
        MySprite& SetScale(float val) noexcept;

        FCompl GetPosition() const noexcept;
        MySprite& SetPosition(FCompl val) noexcept;

        FCompl GetRotation() const noexcept;
        MySprite& SetRotation(FCompl val) noexcept;

        MySprite& MoveAbsolute(FCompl translation) noexcept;
        MySprite& MoveRelative(FCompl translation) noexcept;
        MySprite& Turn(FCompl additional_rotation) noexcept;
        MySprite& Inflate(float additional_scale) noexcept;
        MySprite& NormaliseRotationFast() noexcept;
        MySprite& NormaliseRotation();

        const sf::Sprite GetSprite() const noexcept;
        void DrawSprite(sf::RenderTarget& render_target) const;

        static FCompl CosSin(float radian_angle);
        static float ACosSin(FCompl a_rotation);
        static constexpr float tau = 6.28318530718f;
        static constexpr float pi = tau/2;
    };
}

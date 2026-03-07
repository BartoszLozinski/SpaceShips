#pragma once

namespace Game
{
    template<typename T>
    struct Vector2t
    {
        T x{};
        T y{};

        Vector2t(const T& x_, const T& y_)
            : x(x_)
            , y(y_)
        {};

        Vector2t() = default;
        Vector2t(const Vector2t& other) = default;
        Vector2t(Vector2t&& other) = default;
        Vector2t& operator=(const Vector2t& other) = default;
        Vector2t& operator=(Vector2t&& other) = default;
        
        [[nodiscard]] bool operator==(const Vector2t& other) const
        {
            return x == other.x && y == other.y;
        }

        Vector2t& operator+=(const Vector2t& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2t& operator-=(const Vector2t& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        template<typename U>
        Vector2t(const Vector2t<U>& other)
            : x(static_cast<U>(other.x))
            , y(static_cast<U>(other.y))
        {};

        ~Vector2t() = default;
    };

    using Vector2f = Vector2t<float>;
    using Vector2u = Vector2t<unsigned>;


};

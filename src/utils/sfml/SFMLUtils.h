#include <SFML/System/Vector2.hpp>

namespace sf
{
    float Dot(sf::Vector2f& v1,sf::Vector2f& v2)
    {
        return v1.x*v2.x + v1.y*v2.y;
    }
}
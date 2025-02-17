#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f previous_position;
    sf::Vector2f acceleration;
    bool is_pinned;

    Particle(float x, float y, sf::Vector2f acceleration, bool pinned = false) : position(x, y), previous_position(x, y),
                                acceleration(acceleration), is_pinned(pinned) {}

    void update(float time_step) {
        // verlet intergration
        if (!is_pinned) {
            sf::Vector2f velocity = position - previous_position;
            previous_position = position;
            position += velocity + acceleration * time_step * time_step;
        }
    }

    void constrain_to_bounds(float width, float height) {
        if (position.x < 0) position.x = 0;
        if (position.x > width) position.x = width;
        if (position.y < 0) position.y = 0;
        if (position.y > height) position.y = height;
    }

};

#endif // PARTICLE_H
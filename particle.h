#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f previous_position;
    sf::Vector2f acceleration;
    bool is_pinned;

    Particle(float x, float y, bool pinned = false) : position(x, y), previous_position(x, y),
                                acceleration(0, 0), is_pinned(pinned) {}

    void apply_force(const sf::Vector2f& force) {
        if (!is_pinned) {
            acceleration += force;
        }
    }

    void update(float time_step) {
        // verlet intergration
        if (!is_pinned) {
            sf::Vector2f velocity = position - previous_position;
            previous_position = position;
            position += velocity + acceleration * time_step * time_step;
            acceleration = sf::Vector2f(0, 0); // reset after update 
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
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "particle.h"
#include <cmath>
#include <limits>

class Constraint {
public:
    Particle *p1;
    Particle *p2;
    float initial_length;
    bool active;

    Constraint(Particle *p1, Particle *p2) : p1(p1), p2(p2) {
        initial_length = std::hypot(p2->position.x - p1->position.x,
                                    p2->position.y - p1->position.y);
        active = true;
    }

    void satisfy() {
        if (!active) return;

        sf::Vector2f delta = p2->position - p1->position;
        float current_length = std::hypot(delta.x, delta.y);
        float difference = (current_length - initial_length) / current_length;
        sf::Vector2f correction = delta * 0.5f * difference;

        if (!p1->is_pinned) p1->position += correction;
        if (!p2->is_pinned) p2->position -= correction;
    }

    void deactivate() {
        active = false;
    }

};

#endif // CONSTRAINT_H

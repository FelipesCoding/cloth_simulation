#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.h"
#include "constraint.h"

const float CLICK_TOLERANCE = 5.0f;


class InputHandler {
public:
    static void handle_mouse_click(const sf::Event& event, std::vector<Particle>& particles,
                                    std::vector<Constraint>& constraints) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            float mouse_x = static_cast<float>(event.mouseButton.x);
            float mouse_y = static_cast<float>(event.mouseButton.y);
            tear_cloth(mouse_x, mouse_y, particles, constraints);
        }
    }
private:
    static float point_to_segment_distance(float px, float py, float x1, float y1, float x2, float y2) {
        float ABx = x2 - x1;
        float ABy = y2 - y1;

        float APx = px - x1;
        float APy = py - y1;

        float BPx = px - x2;
        float BPy = py - y2;

        float AB_AP = ABx * APx + ABy * APy;
        float AB_AB = ABx * ABx + ABy * ABy;
        float t = AB_AP / AB_AB;

        // Project point P ont the line segment AB
        if (t < 0.0f) {
            // P is closer to A
            return std::sqrt(APx * APx + APy * APy);
        }
        else if (t > 1.0f) {
            // P is closer to B
            return std::sqrt(BPx * BPx + BPy * BPy);
        }
        else {
            // projection point is on the segment
            float proj_x = x1 + t * ABx;
            float proj_y = y1 + t * ABy;
            return std::sqrt((px - proj_x) * (px - proj_x) + (py - proj_y) * (py - proj_y));
        }
    }

    static Constraint* find_nearest_constraint(float mouse_x, float mouse_y,
                                    const std::vector<Constraint>& constraints) {
        Constraint *nearest_constraint = nullptr;
        float min_distance = CLICK_TOLERANCE;

        for (const auto& constraint : constraints) {
            float distatnce = point_to_segment_distance(mouse_x, mouse_y,
                                constraint.p1->position.x, constraint.p1->position.y,
                                constraint.p2->position.x, constraint.p2->position.y);
            if (distatnce < min_distance) {
                min_distance = distatnce;
                nearest_constraint = const_cast<Constraint*>(&constraint);
            }
        }
        return nearest_constraint;
    }


    static void tear_cloth(float mouse_x, float mouse_y, const std::vector<Particle>& particles,
                            std::vector<Constraint>& constraints) {
        Constraint *nearest = find_nearest_constraint(mouse_x, mouse_y, constraints);
        if (nearest) {
            nearest->deactivate();
        }
    }
};

#endif // INPUT_HANDLER_H
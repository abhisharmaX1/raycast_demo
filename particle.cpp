#include <SFML/Graphics.hpp>
#include "ray.cpp"
#include <cmath>

#define PI 3.14159
const double rayNumber = 720;

class particle {
    public:

    sf::Vector2f pos;
    std::vector<ray> rays;
    sf::CircleShape circle;


    particle(float x, float y) {
        pos = sf::Vector2f(x, y);
        for (double i = 0; i < 360; i += 360 / rayNumber) {
            ray r(pos, i*(PI / 180));
            rays.push_back(r);
        }
    }

    // draw self
    void draw(sf::RenderWindow& window) {
        circle.setRadius(10);
        circle.setFillColor(sf::Color::White);
        circle.setOrigin(10.0, 10.0);
        circle.setPosition(pos);
        window.draw(circle);
        for (auto rey : rays) {
            rey.draw(window);
        }
    }

    // draw ray cast (rays which intersect a given wall)
    void look(std::vector<boundary>& walls, sf::RenderWindow& window) {
        for (auto rey : rays) {
            int dist = INT_MAX;
            sf::Vector2f closest;
            for (auto wall : walls) {
                bool intersect = rey.check(wall);
                if (intersect) {
                    sf::Vector2f pt = rey.cast(wall);
                    if (distance(pt, pos) < dist) {
                        dist = distance(pt, pos);
                        closest = pt;
                    }
                }
            }
            if (dist != INT_MAX) {
                draw(window, closest);
            }
        }
    }

    // get distance between pt1 and pt2
    float distance(sf::Vector2f pt1, sf::Vector2f pt2) {
        float dx = abs(pt1.x - pt2.x);
        float dy = abs(pt1.y - pt2.y);
        return sqrt(dx*dx + dy*dy);
    }

    // helper draw to above draw
    void draw(sf::RenderWindow& window, sf::Vector2f pt) {
        sf::Vertex line[2];
        line[0] = sf::Vertex(pos);
        line[1] = sf::Vertex(pt);
        line->color = sf::Color(255, 255, 255, 50);
        window.draw(line, 2, sf::Lines);
    }

    // update particle position on mouse movement
    void update(sf::Vector2f mousePos) {
        pos = mousePos;
        for (int i = 0; i < rays.size(); i++) {
            rays[i].updatePos(pos);
        }
    }
};


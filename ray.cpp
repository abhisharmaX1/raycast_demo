#include <SFML/Graphics.hpp>
#include <cmath>
#include "boundary.cpp"

const float SCALE = 25.0;

class ray {
    public:

    sf::Vector2f ipos;
    sf::Vector2f dir;
    sf::Vector2f fpos;

    sf::Vertex line[2];

    ray() {

    }

    ray (sf::Vector2f pos, float angle) {
        ipos = pos;
        dir = sf::Vector2f(cos(angle), sin(angle));
        fpos = sf::Vector2f(ipos.x + SCALE*dir.x, ipos.y + SCALE*dir.y);
    }

    void updatePos(sf::Vector2f pos) {
        ipos = pos;
        fpos = sf::Vector2f(ipos.x + SCALE*dir.x, ipos.y + SCALE*dir.y);
    }

    ray (float x, float y) {
        ipos = sf::Vector2f(x, y);
        dir = sf::Vector2f(1, 0);
        fpos = sf::Vector2f(ipos.x + SCALE*dir.x, ipos.y + SCALE*dir.y);
    }

    void lookAt(float x, float y) {
        x -= ipos.x;
        y -= ipos.y;
        float mod = sqrt(x*x + y*y);
        x /= mod;
        y /= mod;
        dir = sf::Vector2f(x, y);
        fpos = sf::Vector2f(ipos.x + SCALE*dir.x, ipos.y + SCALE*dir.y);
    }

    void draw(sf::RenderWindow& window) {
        line[0] = sf::Vertex(ipos);
        line[1] = sf::Vertex(fpos);
        window.draw(line, 2, sf::Lines);
    }

    // check for collision
    bool check(boundary& wall) {
        float x1 = wall.line[0].position.x;
        float y1 = wall.line[0].position.y;
        float x2 = wall.line[1].position.x;
        float y2 = wall.line[1].position.y;

        float x3 = ipos.x;
        float y3 = ipos.y;
        float x4 = fpos.x;
        float y4 = fpos.y;

        float den = ((x1 - x2)*(y3 - y4)) - ((y1 -y2)*(x3 - x4));
        if (den == 0) return false;
        float t = (((x1 - x3)*(y3 - y4)) - ((y1 - y3)*(x3 - x4))) / den;
        float u = (((x1 - x3)*(y1 - y2)) - ((y1 - y3)*(x1 - x2))) / den;

        if (t >= 0 && t <= 1 && u >= 0) return true; // line intersection condition
        else                            return false;
    }

    // get the point where collision occurs
    sf::Vector2f cast(boundary& wall) {
        float x1 = wall.line[0].position.x;
        float y1 = wall.line[0].position.y;
        float x2 = wall.line[1].position.x;
        float y2 = wall.line[1].position.y;

        float x3 = ipos.x;
        float y3 = ipos.y;
        float x4 = fpos.x;
        float y4 = fpos.y;

        float den = ((x1 - x2)*(y3 - y4)) - ((y1 -y2)*(x3 - x4));
        float t = (((x1 - x3)*(y3 - y4)) - ((y1 - y3)*(x3 - x4))) / den;
        float u = (((x1 - x3)*(y1 - y2)) - ((y1 - y3)*(x1 - x2))) / den;

        sf::Vector2f ans;
        ans.x = x1 + t*(x2 - x1);
        ans.y = y1 + t*(y2 - y1);
        return ans;
    }
};
#include <SFML/Graphics.hpp>

class boundary {
    public:

    sf::Vertex line[2];

    boundary() {
        line[0] = sf::Vertex(sf::Vector2f(600, 100));
        line[1] = sf::Vertex(sf::Vector2f(600, 600)); 
    }

    boundary(float x1, float y1, float x2, float y2) {
        line[0] = sf::Vertex(sf::Vector2f(x1, y1));
        line[1] = sf::Vertex(sf::Vector2f(x2, y2));        
    }

    // draw wall
    void draw(sf::RenderWindow& window) {
        window.draw(line, 2, sf::Lines);
    }
};
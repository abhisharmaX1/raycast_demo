#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "particle.cpp"

const int WIDTH = 800;
const int HEIGHT = 800;

float random(int n) {
    float ans = rand() % n;
    return ans;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "ray-casting");
    window.setFramerateLimit(60);
    srand(time(NULL));

    std::vector<boundary> walls;
    for (int i = 0; i < 5; i++) {
        float x1 = random(WIDTH);
        float y1 = random(HEIGHT);
        float x2 = random(WIDTH);
        float y2 = random(HEIGHT);
        boundary b(x1, y1, x2, y2);
        walls.push_back(b);

    }
    walls.push_back(boundary(1, 1, 1, HEIGHT));
    walls.push_back(boundary(1, 1, WIDTH, 1));
    walls.push_back(boundary(WIDTH, 0, WIDTH, HEIGHT));
    walls.push_back(boundary(0, HEIGHT, WIDTH, HEIGHT));
    particle player(WIDTH / 2, HEIGHT / 2);
    

    while (window.isOpen()) {

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }

            if (e.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
                player.update(mousePos);
            }
        }



        window.clear(sf::Color(0, 0, 0));
        for (auto wall : walls) {
            wall.draw(window);
        }
        player.draw(window);
        player.look(walls, window);
        
        window.display();
    }
    
    return 0;
}
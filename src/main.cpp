#include <SFML/Graphics.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

bool randBool() {
    return rand() % 2;
}

int main() {
    sf::Clock tr;

    sf::Texture texture;
    texture.loadFromFile("src/textures/dababycar.jpg");

    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML window");
    window.setFramerateLimit(10);

    sf::Sprite car;
    car.setTexture(texture);
    car.setScale(.5, .5);

    int speed = 50;

    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // Clear screen

        if (randBool() == true) {
            window.clear(sf::Color::Blue);
        } else {
            window.clear(sf::Color::Red);
        }

        float deltaTime = tr.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            car.move(0.f, -speed * deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            car.move(0.f, speed * deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            car.move(-speed * deltaTime, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            car.move(speed * deltaTime, 0.f);
        }

        window.draw(car);

        window.display();
    }
    return EXIT_SUCCESS;
}
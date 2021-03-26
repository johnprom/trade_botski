#include <SFML/Graphics.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

int window_width = 1200;
int window_height = 900;
int refresh_rate = 20;

//sprite variables
int speed = 200;
int offset = speed/refresh_rate;
float size = 0.2f;
float size2 = 0.6f;

//returns an unseeded random boolean
bool randBool() {
    return rand() % 2;
}

//detemines if sprite can move in given direction 
bool in_bounds_upper(sf::Sprite sprite){
    return (sprite.getPosition().y - offset > 0);
}
bool in_bounds_left(sf::Sprite sprite){
    return (sprite.getPosition().x - offset > 0);
}
bool in_bounds_right(sf::Sprite sprite){
    return (sprite.getPosition().x + sprite.getGlobalBounds().width + offset < window_width);
}
bool in_bounds_lower(sf::Sprite sprite){
    return (sprite.getPosition().y + sprite.getGlobalBounds().height + offset < window_height);
}

int main() {
    sf::Clock tr;

    sf::Texture texture_DaBaby;
    texture_DaBaby.loadFromFile("src/textures/dababycar.jpg");

    sf::Texture texture_CopCar;
    texture_CopCar.loadFromFile("src/textures/cursedEmojiHands.jpg");

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML window");
    window.setFramerateLimit(refresh_rate);

    sf::Sprite car;
    car.setTexture(texture_DaBaby);
    car.setScale(size, size);

    sf::Sprite car2;
    car2.setTexture(texture_CopCar);
    car2.setScale(size2, size2);

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

        //wasd movement for sprite
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if(in_bounds_upper(car)){car.move(0.f, -speed * deltaTime);}
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(in_bounds_lower(car)){car.move(0.f, speed * deltaTime);}
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if(in_bounds_left(car)){car.move(-speed * deltaTime, 0.f);}
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if(in_bounds_right(car)){car.move(speed * deltaTime, 0.f);}
        }

        //ijkl movement for sprite2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            if(in_bounds_upper(car2)){car2.move(0.f, -speed * deltaTime);}
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            if(in_bounds_lower(car2)){car2.move(0.f, speed * deltaTime);}
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            if(in_bounds_left(car2)){car2.move(-speed * deltaTime, 0.f);}
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            if(in_bounds_right(car2)){car2.move(speed * deltaTime, 0.f);}
        }

        window.draw(car);
        window.draw(car2);

        window.display();
    }
    return EXIT_SUCCESS;
}
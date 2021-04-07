#include <SFML/Graphics.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "easyhttpcpp/EasyHttp.h"
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

std::string fn(std::string url) {
    // HTTP GET the url
    std::cout << "HTTP GET url: " << url << std::endl;

    // cache dir = current working dir; cache size = 100 KB
    easyhttpcpp::HttpCache::Ptr pCache = easyhttpcpp::HttpCache::createCache(Poco::Path::current(), 1024 * 100);

    // a default http connection pool
    easyhttpcpp::ConnectionPool::Ptr pConnectionPool = easyhttpcpp::ConnectionPool::createConnectionPool();

    // configure http cache and connection pool instance (optional but recommended)
    easyhttpcpp::EasyHttp::Builder httpClientBuilder;
    httpClientBuilder.setCache(pCache)
        .setConnectionPool(pConnectionPool);

    // create http client
    easyhttpcpp::EasyHttp::Ptr pHttpClient = httpClientBuilder.build();

    // create a new request and execute synchronously
    easyhttpcpp::Request::Builder requestBuilder;
    easyhttpcpp::Request::Ptr pRequest = requestBuilder.setUrl(url).build();
    easyhttpcpp::Call::Ptr pCall = pHttpClient->newCall(pRequest);
    easyhttpcpp::Response::Ptr pResponse = pCall->execute();

    if (!pResponse->isSuccessful()) {
        std::cout << "HTTP GET Error: (" << pResponse->getCode() << ")" << std::endl;
    } else {
        std::cout << "HTTP GET Success!" << std::endl;
    }

    return pResponse->getBody()->toString();
}

std::string fn2(){
    std::string s = fn("https://api.coindesk.com/v1/bpi/currentprice.json");
    // parse explicitly
    auto j3 = json::parse(s);
    return j3["bpi"]["USD"]["rate"];
}

int main() {

    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML window");
    window.setFramerateLimit(10);

    sf::Font font;
    if (!font.loadFromFile("src/fonts/arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text(fn2(), font, 50);

    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close window: exit

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        text.setString(fn2());

        window.clear(sf::Color::Black);

        // Draw the string
        window.draw(text);

        window.display();
    }
    return EXIT_SUCCESS;
}

// int window_width = 1200;
// int window_height = 900;
// int refresh_rate = 20;

// //sprite variables
// int speed = 200;
// int offset = speed / refresh_rate;
// float size = 0.2f;
// float size2 = 0.6f;

// //returns an unseeded random boolean
// bool randBool() {
//     return rand() % 2;
// }

// //return true if there is no collision between sprite a and sprite b on horizontal axis
// bool collision_free(sf::Sprite spriteA, sf::Sprite spriteB) {
//         return !(((spriteA.getGlobalBounds().width / 2 + spriteB.getGlobalBounds().width / 2) >
//               abs((spriteA.getPosition().x + spriteA.getGlobalBounds().width / 2) - (spriteB.getPosition().x + spriteB.getGlobalBounds().width / 2))) &&
//              ((spriteA.getGlobalBounds().height / 2 + spriteB.getGlobalBounds().height / 2) >
//               abs((spriteA.getPosition().y + spriteA.getGlobalBounds().height / 2) - (spriteB.getPosition().y + spriteB.getGlobalBounds().height / 2))));
// }

// //detemines if sprite can move in given direction
// bool in_bounds_upper(sf::Sprite sprite, float dt) {
//     return (sprite.getPosition().y - (dt*speed) > 0);
// }
// bool in_bounds_left(sf::Sprite sprite, float dt) {
//     return (sprite.getPosition().x - (dt*speed) > 0);
// }
// bool in_bounds_right(sf::Sprite sprite, float dt) {
//     return (sprite.getPosition().x + sprite.getGlobalBounds().width + (dt*speed) < window_width);
// }
// bool in_bounds_lower(sf::Sprite sprite, float dt) {
//     return (sprite.getPosition().y + sprite.getGlobalBounds().height + (dt*speed) < window_height);
// }

// int main() {
//     sf::Clock tr;

//     sf::Texture texture_DaBaby;
//     texture_DaBaby.loadFromFile("src/textures/dababycar.jpg");

//     sf::Texture texture_CopCar;
//     texture_CopCar.loadFromFile("src/textures/cursedEmojiHands.jpg");

//     sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML window");
//     window.setFramerateLimit(refresh_rate);

//     sf::Sprite car;
//     car.setTexture(texture_DaBaby);
//     car.setScale(size, size);
//     car.setPosition(300, 300);

//     sf::Sprite car2;
//     car2.setTexture(texture_CopCar);
//     car2.setScale(size2, size2);

//     while (window.isOpen()) {
//         // Process events
//         sf::Event event;

//         while (window.pollEvent(event)) {
//             // Close window: exit

//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//         // Clear screen

//         // if (randBool() == true) {
//         //     window.clear(sf::Color::Blue);
//         // } else {
//         //     window.clear(sf::Color::Red);
//         // }

//         window.clear(sf::Color::Black);

//         float deltaTime = tr.restart().asSeconds();

//         //wasd movement for sprite
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//             if (in_bounds_upper(car, deltaTime) && collision_free(car, car2)) {
//                 car.move(0.f, -speed * deltaTime);
//             }
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//             if (in_bounds_lower(car, deltaTime) && collision_free(car, car2)) {
//                 car.move(0.f, speed * deltaTime);
//             }
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//             if (in_bounds_left(car, deltaTime) && collision_free(car, car2)) {
//                 car.move(-speed * deltaTime, 0.f);
//             }
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//             if (in_bounds_right(car, deltaTime) && collision_free(car, car2)) {
//                 car.move(speed * deltaTime, 0.f);
//             }
//         }

//         //ijkl movement for sprite2
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
//             if (in_bounds_upper(car2, deltaTime) && collision_free(car, car2)) {
//                 car2.move(0.f, -speed * deltaTime);
//             }
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
//             if (in_bounds_lower(car2, deltaTime) && collision_free(car, car2)) {
//                 car2.move(0.f, speed * deltaTime);
//             }
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
//             if (in_bounds_left(car2, deltaTime) && collision_free(car, car2)) {
//                 car2.move(-speed * deltaTime, 0.f);
//             }
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
//             if (in_bounds_right(car2, deltaTime) && collision_free(car, car2)) {
//                 car2.move(speed * deltaTime, 0.f);
//             }
//         }

//         window.draw(car);
//         window.draw(car2);

//         window.display();
//     }
//     return EXIT_SUCCESS;
// }
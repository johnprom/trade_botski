#include <SFML/Graphics.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <string>
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

std::string get_current_price_string(){
    std::string s = fn("https://api.coindesk.com/v1/bpi/currentprice.json");
    // parse explicitly
    auto j3 = json::parse(s);
    return j3["bpi"]["USD"]["rate"];
}

std::string dollar_format (float f, bool is_signed){ //add bool for has commas

    std::string str = std::to_string(f);
    std::string str_format;

    for(int i = 0 ; i < str.length() ; i++){
        if(i == 0){
            if(str.at(i) == '-'){
                if(is_signed){
                    str_format.append(1, '-');
                } 
                str_format.append(1, '$');
            }else{
                if(is_signed){
                    str_format.append(1, '+');
                } 
                str_format.append(1, '$');
                str_format.append(1, str.at(i));
            }
        }else if(str.at(i) == '.'){
            str_format.append(1, '.');
            str_format.append(1, str.at(i+1));
            str_format.append(1, str.at(i+2));
            return str_format;
        }else{
            str_format.append(1, str.at(i));
        }
    }
    return str_format;
}

// std::string format_currency_unsigned(std::string str){
//     //parse through to only 2 numb after dcimal no +-
// }

float get_current_price(){
    std::string s = fn("https://api.coindesk.com/v1/bpi/currentprice.json");
    // parse explicitly
    auto j3 = json::parse(s);
    return j3["bpi"]["USD"]["rate_float"];
}

int marketColor(float current_change){
    if(current_change < 0){
        return 1; //red
    }else{
        return 2; //green
    }
}

int main() {

    float current_change = 0;
    float current_price = get_current_price();

    //init window
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML window");
    window.setFramerateLimit(10);

    //fonts
    sf::Font font;
    if (!font.loadFromFile("src/fonts/arial.ttf"))
        return EXIT_FAILURE;

    //header text for coin name
    sf::Text coin_name("Bitcoin BTC/USD", font, 50);
    coin_name.setFillColor(sf::Color(255,153,0));
    coin_name.setPosition(20, 20);

    //price text
    sf::Text price_text(dollar_format(current_price, false), font, 50);
    price_text.setPosition(20,100);

    //price change text
    sf::Text price_change_text(dollar_format(current_change, true), font, 50) ;
    price_change_text.setPosition(20,160);

    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close window: exit

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //update current price and relative change variables when change occurs
        if(current_price != get_current_price()){
            current_change =  get_current_price() - current_price;
            current_price = get_current_price();
        } 

        //update price text
        price_text.setString(dollar_format(current_price, false));

        //update change text
        price_change_text.setString(dollar_format(current_change, true));


        if(marketColor(current_change) == 1){
            price_change_text.setFillColor(sf::Color::Red);
        }else{
            price_change_text.setFillColor(sf::Color::Green);
        }
        
        window.clear(sf::Color::Black);

        // Draw the string
        window.draw(price_text);
        window.draw(price_change_text);
        window.draw(coin_name);

        window.display();
    }
    return EXIT_SUCCESS;
}

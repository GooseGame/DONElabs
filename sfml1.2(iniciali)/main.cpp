#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 450}), "inicsiali godness programmista");
    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({1000, 450});
    shape1.setRotation(0);
    shape1.setPosition({0, 0});
    shape1.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({50, 300});
    shape2.setRotation(0);
    shape2.setPosition({150, 100});
    shape2.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({250, 50});
    shape3.setRotation(0);
    shape3.setPosition({50, 50});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({50, 350});
    shape4.setPosition({500, 60});
    shape4.setRotation(25);
    shape4.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({50, 350});
    shape5.setPosition({700, 380});
    shape5.setRotation(155);
    shape5.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({200, 50});
    shape6.setRotation(0);
    shape6.setPosition({430, 250});
    shape6.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({200, 50});
    shape7.setRotation(0);
    shape7.setPosition({750, 50});
    shape7.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({200, 50});
    shape8.setRotation(0);
    shape8.setPosition({750, 350});
    shape8.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({50, 300});
    shape9.setRotation(0);
    shape9.setPosition({750, 100});
    shape9.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape9);

    window.display();

    sf::sleep(sf::seconds(15));
}

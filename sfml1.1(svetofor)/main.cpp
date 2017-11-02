#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 620}), "svetofor");
    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({200, 700});
    shape1.setRotation(0);
    shape1.setPosition({0, 0});
    shape1.setFillColor(sf::Color(0x7b, 0x7d, 0x7d));
    window.draw(shape1);

    sf::CircleShape shape2(90);
    shape2.setPosition({10, 20});
    shape2.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(90);
    shape3.setPosition({10, 220});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape3);

    sf::CircleShape shape4(90);
    shape4.setPosition({10, 420});
    shape4.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}
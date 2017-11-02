#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0x99, 0x30, 0x30));
    trapeze.setPosition(400, 150);
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {-100, 0});
    trapeze.setPoint(1, {+100, 0});
    trapeze.setPoint(2, {+250, 100});
    trapeze.setPoint(3, {-250, 100});

    sf::RectangleShape srub;
    srub.setSize({400, 300});
    srub.setPosition({200, 250});
    srub.setFillColor(sf::Color(0xEF, 0x66, 0x18));

    sf::RectangleShape dverka;
    dverka.setSize({75, 200});
    dverka.setPosition({250, 400});
    dverka.setFillColor(sf::Color(0x0, 0x0, 0x0));

    sf::RectangleShape dimohod;
    dimohod.setSize({40, 65});
    dimohod.setPosition({450, 115});
    dimohod.setFillColor(sf::Color(0x7b, 0x7d, 0x7d));

    sf::RectangleShape dimohodV;
    dimohodV.setSize({60, 40});
    dimohodV.setPosition({440, 75});
    dimohodV.setFillColor(sf::Color(0x7d, 0x7d, 0x7d));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Convex Shapes");
    window.clear();
    window.draw(trapeze);
    window.draw(srub);
    window.draw(dverka);
    window.draw(dimohod);
    window.draw(dimohodV);
    window.display();

    sf::sleep(sf::seconds(5));
}
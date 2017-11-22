#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>


int main()
{
    constexpr int pointCount = 200;
    constexpr int moveRadius = 50;
    sf::Vector2f ellipseRadius = { 200.f, 80.f };
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }), "Ellipse",
        sf::Style::Default, settings);

    sf::ConvexShape shape;
    shape.setPosition({400, 320});

    shape.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        ellipseRadius.x = 200 * std::sin(6 * angle);
        ellipseRadius.y = 200 * std::sin(6 * angle);

        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)
        };
        shape.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        shape.setFillColor(sf::Color(rand() % 255, 0, 0));
        window.clear();
        window.draw(shape);
        window.display();
    }
}
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <SFML\System.hpp>

void init(sf::ConvexShape &pointer)
{
    pointer.setPosition({200, 100});
    pointer.setFillColor(sf::Color(233, 237, 0));
    pointer.setPointCount(7);
    pointer.setPoint(0, {200, 150});
    pointer.setPoint(1, {275, 100});
    pointer.setPoint(2, {200, 50});
    pointer.setPoint(3, {200, 75});
    pointer.setPoint(4, {100, 75});
    pointer.setPoint(5, {100, 125});
    pointer.setPoint(6, {200, 125});
    pointer.setOrigin({200, 100});
    pointer.setOutlineColor(sf::Color(0, 0, 0));
    pointer.setOutlineThickness(3);
}
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{

    sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    const float maximAngle = 90;
    const float maximRotationSpeed = maximAngle * deltaTime;
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    float rotation = angle - pointer.getRotation();
    float rotationSpeed = abs(rotation) * deltaTime;
    if (rotation > 0)
    {
        if ((rotation - 180) > 0)
        {
            pointer.setRotation(pointer.getRotation() - std::min(rotationSpeed, maximRotationSpeed));
        }
        else 
        {
            pointer.setRotation(pointer.getRotation() + std::min(rotationSpeed, maximRotationSpeed));
        }
    }
    else
    {
        if ((rotation + 180) < 0)
        {
            pointer.setRotation(pointer.getRotation() + std::min(rotationSpeed, maximRotationSpeed));
        }
        else 
        {
            pointer.setRotation(pointer.getRotation() - std::min(rotationSpeed, maximRotationSpeed));
        }
    }

    float x = delta.x;
    float y = delta.y;
    float dlina = sqrt(pow(x, 2) + pow(y, 2));
    sf::Vector2f direction = {(x / dlina), (y / dlina)};
    if (dlina = 0)
    {
        direction = {0, 0};
    }
    if (dlina = 0)
    {
        direction = {0, 0};
    }
    float speed = 20.f;
    sf::Vector2f position = pointer.getPosition();
    pointer.setPosition({position.x + direction.x * speed * deltaTime, position.y + direction.y * speed * deltaTime});
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(100, 100, 100));
    window.draw(pointer);
    window.display();
}

int main()
{
    sf::Clock clock;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, deltaTime);
        redrawFrame(window, pointer);
    }
}
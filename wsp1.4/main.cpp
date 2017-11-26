#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <windows.h>

struct MegaCat
{
    sf::Texture kitty;
    sf::Sprite cat;
};
struct Laser
{
    sf::Texture pointer;
    sf::Sprite Plaser;
};

void init(MegaCat &megaCat, Laser &laser)
{
    megaCat.kitty.loadFromFile("cat.png");
    laser.pointer.loadFromFile("red_pointer.png");

    megaCat.cat.setTexture(megaCat.kitty);
    megaCat.cat.setPosition(200, 100);
    megaCat.cat.setOrigin({15, 15});

    laser.Plaser.setTexture(laser.pointer);
    laser.Plaser.setPosition(500, 200);
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

void onMouseClick(sf::Event::MouseButtonEvent &event, sf::Vector2f &moPosition, Laser &laser)
{
    moPosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Vector2f &moPosition, Laser &laser)
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
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, moPosition, laser);
            break;
        default:
            break;
        }
    }
}

void update(sf::Vector2f mousePosition, MegaCat &megaCat, float deltaTime, Laser &laser, sf::Vector2f moPosition, sf::RenderWindow &window)
{
    sf::Vector2f delta = moPosition - megaCat.cat.getPosition();
    laser.Plaser.setPosition({moPosition.x, moPosition.y});

    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + float(2 * M_PI);
    }
    angle = toDegrees(angle);
    if (((angle >= 0) && (angle < 90)) || ((angle <= 360) && (angle > 270)))
    {
        megaCat.cat.setScale(1, 1);
    }
    else
    {
        megaCat.cat.setScale(-1, 1);
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
    float speed = 100.f;
    sf::Vector2f position = megaCat.cat.getPosition();
    megaCat.cat.setPosition({position.x + direction.x * speed * deltaTime, position.y + direction.y * speed * deltaTime});
}

void redrawFrame(sf::RenderWindow &window, MegaCat &megaCat, Laser &laser)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(megaCat.cat);
    window.draw(laser.Plaser);
    window.display();
}

int main()
{
    Laser laser;
    MegaCat megaCat;
    sf::Clock clock;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::Sprite cat;
    sf::Texture kitty;
    sf::Vector2f mousePosition;
    sf::Vector2f moPosition;
    // текстуры поставить там где спрайт, и добавить условине на отображение

    init(megaCat, laser);
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition, moPosition, laser);
        update(mousePosition, megaCat, deltaTime, laser, moPosition, window);
        redrawFrame(window, megaCat, laser);
    }
}
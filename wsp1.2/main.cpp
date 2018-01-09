#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    const float maxAnglePerSec = 90;
    float angle = atan2(delta.y, delta.x);
    const float maxRotateSpeed = maxAnglePerSec * deltaTime;
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    float rotationAngle = toDegrees(angle) - arrow.getRotation();
    float rotateSpeed = std::abs(rotationAngle) * deltaTime;
    if (rotationAngle != 0)
    {
        if (rotationAngle > 0)
        {
            if ((rotationAngle - 180) > 0)
            {
                arrow.setRotation(arrow.getRotation() - std::min(rotateSpeed, maxRotateSpeed));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() + std::min(rotateSpeed, maxRotateSpeed));
            }
        }
        else
        {
            if ((rotationAngle + 180) < 0)
            {
                arrow.setRotation(arrow.getRotation() + std::min(rotateSpeed, maxRotateSpeed));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() - std::min(rotateSpeed, maxRotateSpeed));
            }
        }
    }
    const float distance = std::sqrt((delta.x * delta.x) + (delta.y * delta.y));
    sf::Vector2f direction = {0.f, 0.f};
    if (distance != 0)
    {
        direction = {delta.x / distance, delta.y / distance};
    }
    const float maxSpeed = 20.f;
    const float speed = maxSpeed * deltaTime;
    arrow.setPosition(arrow.getPosition() + direction * speed);
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

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(arrow);
    window.display();
}
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;
    sf::Vector2f mousePosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Arrow can move", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    arrow.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    arrow.setFillColor(sf::Color{255, 255, 0});
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, 60});
    arrow.setPoint(1, {60, 0});
    arrow.setPoint(2, {0, -60});
    arrow.setPoint(3, {0, -30});
    arrow.setPoint(4, {-60, -30});
    arrow.setPoint(5, {-60, 30});
    arrow.setPoint(6, {0, 30});
    arrow.setOutlineColor(sf::Color{0, 0, 0});
    arrow.setOutlineThickness(3);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, arrow, deltaTime);
        redrawFrame(window, arrow);
    }
}
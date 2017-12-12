#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>

struct Sharic
{
    sf::CircleShape body;
    sf::Vector2f position;
    sf::Vector2f speed;
};

void update(Sharic (&Ball_count)[5], const float deltaTime, float BALL_SIZE)
{
    for (int i = 0; i < std::size(Ball_count); ++i)
    {
        BALL_SIZE = 35 + 5 * i;
        Ball_count[i].position = Ball_count[i].body.getPosition();
        Ball_count[i].position += Ball_count[i].speed * deltaTime;

        if ((Ball_count[i].position.x + 2 * BALL_SIZE >= 800) && (Ball_count[i].speed.x > 0))
        {
            Ball_count[i].speed.x = -Ball_count[i].speed.x;
        }
        if ((Ball_count[i].position.x < 0) && (Ball_count[i].speed.x < 0))
        {
            Ball_count[i].speed.x = -Ball_count[i].speed.x;
        }
        if ((Ball_count[i].position.y + 2 * BALL_SIZE >= 600) && (Ball_count[i].speed.y > 0))
        {
            Ball_count[i].speed.y = -Ball_count[i].speed.y;
        }
        if ((Ball_count[i].position.y < 0) && (Ball_count[i].speed.y < 0))
        {
            Ball_count[i].speed.y = -Ball_count[i].speed.y;
        }

        Ball_count[i].body.setPosition(Ball_count[i].position);
    }
}

int main()
{
    sf::Clock clock;
    Sharic Ball_count[5];
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned WINDOW_WIDTH = 800;
    float BALL_SIZE;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Programmers balls");

    for (int i = 0; i < std::size(Ball_count); ++i)
    {
        BALL_SIZE = 35 + 5 * i;
        Ball_count[i].position = {100.f * i + 25, 100.f + 100 * i};
        Ball_count[i].body.setPosition(Ball_count[i].position);
        Ball_count[i].body.setFillColor(sf::Color(40 + 40 * i, 250 - 25 * i, 255));
        Ball_count[i].speed = {35.f * i, 99.f};
        Ball_count[i].body.setRadius(BALL_SIZE);
    }

    while (window.isOpen())
    {
        sf::Event event;
        const float deltaTime = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        update(Ball_count, deltaTime, BALL_SIZE);
        window.clear();
        for (int i = 0; i < std::size(Ball_count); ++i)
        {
            window.draw(Ball_count[i].body);
        }
        window.display();
    }
}
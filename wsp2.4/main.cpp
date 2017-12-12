#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <cstdlib>
#include <random>
#include <cassert>

struct PRNG
{
    std::mt19937 engine;
};

struct Sharic
{
    sf::CircleShape body;
    sf::Vector2f position;
    sf::Vector2f speed;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

sf::Color randomColor(sf::Color (&pattern)[8], PRNG &generator)
{
    const unsigned firstInPalitra = random(generator, 0, 7);
    const unsigned secondInPalitra = random(generator, 0, 7);

    sf::Color firstColor = pattern[firstInPalitra];
    sf::Color secondColor = pattern[secondInPalitra];

    sf::Color finalColor;
    finalColor.r = sf::Uint8((firstColor.r + secondColor.r) / 2);
    finalColor.g = sf::Uint8((firstColor.g + secondColor.g) / 2);
    finalColor.b = sf::Uint8((firstColor.b + secondColor.b) / 2);

    return finalColor;
}

float getRandomFloat(PRNG &generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

void update(Sharic (&Ball_count)[5], const float deltaTime, float BALL_SIZE)
{
    sf::Vector2f deltaPos;
    sf::Vector2f deltaSpeed;
    float dlina;
    for (int i = 0; i < std::size(Ball_count); ++i)
    {
        Ball_count[i].position = Ball_count[i].body.getPosition();
        Ball_count[i].position += Ball_count[i].speed * deltaTime;

        for (int si = i + 1; si < std::size(Ball_count); ++si)
        {
            deltaPos = Ball_count[si].position - Ball_count[i].position;
            deltaSpeed = Ball_count[si].speed - Ball_count[i].speed;

            dlina = sqrt(pow((deltaPos.x), 2) + pow((deltaPos.y), 2));
            float change = ((deltaPos.x * deltaSpeed.x) + (deltaPos.y * deltaSpeed.y)) / pow(dlina, 2);
            if (dlina < (BALL_SIZE + BALL_SIZE))
            {

                Ball_count[i].speed = Ball_count[i].speed + change * deltaPos;
                Ball_count[si].speed = Ball_count[si].speed - change * deltaPos;
            }
        }

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

    sf::Color pattern[8];
    pattern[0] = {0, 197, 45};
    pattern[1] = {13, 1, 55};
    pattern[2] = {7, 51, 12};
    pattern[3] = {92, 51, 0};
    pattern[4] = {76, 102, 0};
    pattern[5] = {3, 0, 102};
    pattern[6] = {177, 0, 65};
    pattern[7] = {23, 51, 0};

    PRNG generator;
    initGenerator(generator);
    sf::Clock clock;
    Sharic Ball_count[5];
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned WINDOW_WIDTH = 800;
    float BALL_SIZE = 40;
    

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Programmers balls");

    for (int i = 0; i < std::size(Ball_count); ++i)
    {
        Ball_count[i].position = {100.f * i + 25, 100.f + 100 * i};
        Ball_count[i].body.setPosition(Ball_count[i].position);
        Ball_count[i].body.setFillColor(randomColor(pattern, generator));
        Ball_count[i].speed = {getRandomFloat(generator, 10.f, 50.f), getRandomFloat(generator, 51.f, 100.f)};
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
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <random>
#include <cassert>

constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned BALL_SIZE = 50;
constexpr float MAX_LIFETIME = 10.0;

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f position;
    sf::Vector2f speed;
    float lifetime;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

float randomFloat(PRNG &generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);

    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    return distribution(generator.engine);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);

    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    return distribution(generator.engine);
}

sf::Color randomColor(sf::Color (&pattern)[8], PRNG &generator)
{
    const unsigned irstInPalitra = random(generator, 0, 7);
    const unsigned secondInPalitra = random(generator, 0, 7);

    sf::Color irstColor = pattern[irstInPalitra];
    sf::Color secondColor = pattern[secondInPalitra];

    sf::Color inalColor;
    inalColor.r = sf::Uint8((irstColor.r + secondColor.r) / 2);
    inalColor.g = sf::Uint8((irstColor.g + secondColor.g) / 2);
    inalColor.b = sf::Uint8((irstColor.b + secondColor.b) / 2);

    return inalColor;
}

void createBall(sf::CircleShape &shape, sf::Color (&pattern)[8], PRNG &generator)
{
    shape.setFillColor(randomColor(pattern, generator));
    shape.setOrigin(BALL_SIZE, BALL_SIZE);
    shape.setRadius(BALL_SIZE);
}

void initball(std::vector<Ball> &ball_count, PRNG &generator, sf::Color (&pattern)[8])
{
    for (int i = 0; i < ball_count.size(); ++i)
    {
        ball_count[i].position = {75.f + 50.f * i, 100.f * i};
        ball_count[i].speed = {randomFloat(generator, -250.f, 200.f), randomFloat(generator, -50.f, 250.f)};
        ball_count[i].ball.setPosition(ball_count[i].position);
        createBall(ball_count[i].ball, pattern, generator);
        ball_count[i].lifetime = 0;
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &ball_count)
{
    window.clear();
    for (int i = 0; i < ball_count.size(); ++i)
    {
        window.draw(ball_count[i].ball);
    }
    window.display();
}

void removeDeathBalls(std::vector<Ball> &ball_count)
{
    auto removeSomeBalls = [&](Ball ball) -> bool {
        return ball.lifetime > MAX_LIFETIME;
    };
    ball_count.erase(std::remove_if(ball_count.begin(), ball_count.end(), removeSomeBalls), ball_count.end());
}

void update(std::vector<Ball> &ball_count, const float deltaTime)
{
    for (int i = 0; i < ball_count.size(); ++i)
    {
        ball_count[i].position = ball_count[i].ball.getPosition();
        ball_count[i].position += ball_count[i].speed * deltaTime;
        ball_count[i].lifetime += deltaTime;

        if ((ball_count[i].position.x + BALL_SIZE >= WINDOW_WIDTH) && (ball_count[i].speed.x > 0))
        {
            ball_count[i].speed.x = -ball_count[i].speed.x;
        }
        if ((ball_count[i].position.x - BALL_SIZE < 0) && (ball_count[i].speed.x < 0))
        {
            ball_count[i].speed.x = -ball_count[i].speed.x;
        }
        if ((ball_count[i].position.y + BALL_SIZE >= WINDOW_HEIGHT) && (ball_count[i].speed.y > 0))
        {
            ball_count[i].speed.y = -ball_count[i].speed.y;
        }
        if ((ball_count[i].position.y - BALL_SIZE < 0) && (ball_count[i].speed.y < 0))
        {
            ball_count[i].speed.y = -ball_count[i].speed.y;
        }

        ball_count[i].ball.setPosition(ball_count[i].position);
    }

    for (int i = 0; i < ball_count.size(); ++i)
    {
        for (int si = i + 1; si < ball_count.size(); ++si)
        {
            sf::Vector2f deltaPos = ball_count[si].position - ball_count[i].position;
            sf::Vector2f deltaSpeed = ball_count[si].speed - ball_count[i].speed;
            float distance = std::sqrt(std::pow(deltaPos.x, 2) + std::pow(deltaPos.y, 2));
            float change = (((deltaPos.x * deltaSpeed.x) + (deltaPos.y * deltaSpeed.y)) / std::pow(distance, 2));
            if (distance <= (2 * BALL_SIZE))
            {
                ball_count[i].speed = ball_count[i].speed + change * deltaPos;
                ball_count[si].speed = ball_count[si].speed - change * deltaPos;
            }
        }
    }
    removeDeathBalls(ball_count);
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, std::vector<Ball> &ball_count, sf::Color (&pattern)[8], PRNG &generator)
{
    sf::Vector2f mousePosition = {float(event.x), float(event.y)};
    bool isRight = true;
    for (int i = 0; i < ball_count.size(); ++i)
    {
        sf::Vector2f ballPosition = ball_count[i].ball.getPosition();
        sf::Vector2f delta = mousePosition - ballPosition;
        float length = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));
        if ((length <= 2 * BALL_SIZE) || (mousePosition.x <= BALL_SIZE) || (mousePosition.y <= BALL_SIZE) || (mousePosition.x >= WINDOW_WIDTH - BALL_SIZE) || (mousePosition.y >= WINDOW_HEIGHT - BALL_SIZE))
        {
            isRight = false;
        }
    }
    if (isRight)
    {
        Ball createdNewBall;
        createdNewBall.speed = {randomFloat(generator, -200.f, 200.f), randomFloat(generator, -200.f, 200.f)};
        createBall(createdNewBall.ball, pattern, generator);
        createdNewBall.ball.setPosition(mousePosition);
        createdNewBall.lifetime = 0;
        ball_count.push_back(createdNewBall);
    }
}

int main()
{
    PRNG generator;
    sf::Clock clock;

    initGenerator(generator);

    std::vector<Ball> ball_count(5, Ball());
    sf::Color pattern[8];
    pattern[0] = {0, 197, 45};
    pattern[1] = {13, 1, 55};
    pattern[2] = {7, 51, 12};
    pattern[3] = {92, 51, 0};
    pattern[4] = {76, 102, 0};
    pattern[5] = {3, 0, 102};
    pattern[6] = {177, 0, 65};
    pattern[7] = {23, 51, 0};
    initball(ball_count, generator, pattern);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Programmers balls");

    while (window.isOpen())
    {
        sf::Event event;
        const float deltaTime = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                onMouseClick(event.mouseButton, ball_count, pattern, generator);
                break;
            default:
                break;
            }
        }

        update(ball_count, deltaTime);
        redrawFrame(window, ball_count);
    }
}
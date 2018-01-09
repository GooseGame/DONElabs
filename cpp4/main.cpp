#include <cstdio>
#include <cmath>

int main()
{
    std::puts("Enter a, b, c for ax^2+bx+c-0");

    float a = 0;
    float b = 0;
    float c = 0;

    std::scanf("%f %f %f", &a, &b, &c);

    float d = (b * b) - (4 * a * c);
    float x1 = (-b + sqrt(d)) / (2 * a);
    float x2 = (-b - sqrt(d)) / (2 * a);

    std::printf("%f\n %f\n", x1, x2);
}
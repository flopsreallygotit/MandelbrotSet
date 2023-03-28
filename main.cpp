#include "mainUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main ()
{
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Mandelbrot Set");
    window.setFramerateLimit(MaxFramerateLimit);

    float offset_x = 64;
    float offset_y = 0;
    float scale = 0.004f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (isPressed(Left))
            offset_x += 16.f;
        if (isPressed(Right))
            offset_x -= 16.f;

        if (isPressed(Up))
            offset_y += 16.f;
        if (isPressed(Down))
            offset_y -= 16.f;
            
        if (isPressed(Add))
            scale *= 1.25f;
        if (isPressed(Subtract))
            scale /= 1.25f;

        drawSet(window, offset_x, offset_y, scale);

        printf("FPS: %f;\n", 1 / clock.restart().asSeconds());

        window.display();
        window.clear();
    }

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

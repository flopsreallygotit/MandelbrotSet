#include "mainUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main ()
{
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Mandelbrot Set");
    window.setFramerateLimit(MaxFramerateLimit);

    sf::Image image;
    image.create(Width, Height, sf::Color::Red);

    float offset_x = 64.f;
    float offset_y = 0.f;
    float scale = 0.004f;

    unsigned int counter = 0;

    sf::Clock clock;
    while (window.isOpen())
    {
        clock.restart();

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
            
        if (isPressed(Num1))
            scale *= 1.25f;
        if (isPressed(Num2))
            scale /= 1.25f;

        drawSet(image, offset_x, offset_y, scale);

        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite;
        sprite.setTexture(texture);   
        
        window.draw(sprite);
        window.display();
        window.clear();

        if (counter % 10 == 0)
            printf("FPS: %f;\n", 1.f / (clock.getElapsedTime().asSeconds()));

        counter++;
    }

    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

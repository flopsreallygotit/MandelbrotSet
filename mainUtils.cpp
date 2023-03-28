#include "mainUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sf::Color pickColor (unsigned int n)
{
    n %= 256;

    return sf::Color{(unsigned char) n - 255 % n,
                     (unsigned char) (n % 2) * 255 % n, 
                     (unsigned char) (n / 255) * 128};
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef FAST

void drawSet(sf::RenderWindow &window, float offset_x, float offset_y, float scale)
{
    sf::RectangleShape rectangle(sf::Vector2f(1, 1));

    float center_x = Width  / 2.f + offset_x;
    float center_y = Height / 2.f + offset_y;

    for (unsigned int y = 0; y < Height; y++)
    {
        float y0 = ((float) y - center_y) * scale;

        for (unsigned int x = 0; x < Width; x++)
        {
            float x0 = ((float) x - center_x) * scale;

            float x_i = x0;  
            float y_i = y0;  

            unsigned int iterator = 0;
            while (iterator < MaxIterationNumber)
            {
                float x2 = x_i * x_i;
                float y2 = y_i * y_i;
                float xy = x_i * y_i;

                if (x2 + y2 >= MaxRadius)
                    break;

                x_i = x2 - y2 + x0;
                y_i = xy + xy + y0;

                iterator++;
            }

            rectangle.setPosition((float) x, (float) y);

            if (iterator < MaxIterationNumber)
                rectangle.setFillColor(pickColor(iterator));

            else
                rectangle.setFillColor(sf::Color::Black);

            window.draw(rectangle);
        }
    }

    return;
}

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// TODO Define FAST for activation of fast function.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

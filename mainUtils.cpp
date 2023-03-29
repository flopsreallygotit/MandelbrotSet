#include "mainUtils.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sf::Color pickColor (unsigned int n)
{
    if (n > MaxIterationNumber)
        return sf::Color::Black;

    n %= 256;

    return sf::Color{(unsigned char) (n / 8) * 32,
                     (unsigned char) 0, 
                     (unsigned char) (n / 255) * 128};
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifdef SLOW

void drawSet(sf::Image &image, float offset_x, float offset_y, float scale)
{
    float center_x = Width  / 2.f + offset_x;
    float center_y = Height / 2.f + offset_y;

    for (unsigned int loop = 0; loop < CalculationLoopCount; loop++)
    {
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

                image.setPixel(x, y, pickColor(iterator));
            }
        }
    }

    return;
}

#else

void drawSet(sf::Image &image, float offset_x, float offset_y, float scale)
{
    __m256 center_x = _mm256_set1_ps(Width  / 2.f + offset_x);
    __m256 center_y = _mm256_set1_ps(Height / 2.f + offset_y);

    __m256 offset = _mm256_set_ps(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);

    for (unsigned int loop = 0; loop < CalculationLoopCount; loop++)
    {
        for (unsigned int y = 0; y < Height; y++)
        {
            __m256 y0 = _mm256_mul_ps(_mm256_sub_ps(_mm256_set1_ps((float) y), center_y), 
                                    _mm256_set1_ps(scale));

            for (unsigned int x = 0; x < Width; x += 8)
            {
                __m256 x0 = _mm256_mul_ps(_mm256_sub_ps(
                                        _mm256_add_ps(_mm256_set1_ps((float) x), offset), 
                                        center_x), 
                                        _mm256_set1_ps(scale));

                __m256 x_i = x0;  
                __m256 y_i = y0;  

                __m256i iterators = _mm256_set1_epi32(0);

                for (unsigned int _ = 0; _ < MaxIterationNumber; _++)
                {
                    __m256 x2 = _mm256_mul_ps(x_i, x_i);
                    __m256 y2 = _mm256_mul_ps(y_i, y_i);
                    __m256 xy = _mm256_mul_ps(x_i, y_i);

                    __m256 r2  = _mm256_add_ps(x2, y2);
                    __m256 cmp = _mm256_cmp_ps(r2, _mm256_set1_ps(MaxRadius), _CMP_LE_OQ);

                    if(!_mm256_movemask_ps(cmp))
                        break;

                    iterators = _mm256_sub_epi32(iterators, _mm256_castps_si256(cmp));

                    x_i = _mm256_add_ps(_mm256_sub_ps (x2, y2), x0); 
                    y_i = _mm256_add_ps(_mm256_add_ps (xy, xy), y0);
                }

                unsigned int *iteratorsArray = (unsigned int *) &iterators;

                for (unsigned int point_idx = 0; point_idx < 8; point_idx++)
                    image.setPixel(x + point_idx, y, pickColor(iteratorsArray[point_idx]));
            }
        }
    }

    return;
}

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

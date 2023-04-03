#include <SFML/Graphics.hpp>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <immintrin.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static const int Width  = 800;
static const int Height = 800;

static const int MaxFramerateLimit  = 90;
static const int MaxIterationNumber = 256;

static const float MaxRadius = 100.f;

static const int CalculationLoopCount = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define isPressed(key) sf::Keyboard::isKeyPressed(sf::Keyboard::key)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sf::Color pickColor (unsigned int n);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void drawSet(sf::Image &image, float offset_x, float offset_y, float scale);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



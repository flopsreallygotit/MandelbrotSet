# MandelbrotSet
For average fractal enjoyers.

## Overview

The goal of this project is implementing Mandelbrot Set points calculation speed in the most effecient way.

To maximize performance we are going to use SSE instructions.

> CPU: Intel Core i5 11300H \
> Tests were conducted on 800 x 600 Background image and 236 x 127 Foreground image

![image](https://user-images.githubusercontent.com/89828695/232138172-817596b2-c1dd-4085-a99c-129c227e5205.png)

The Mandelbrot set is an example of a fractal in mathematics. The Mandelbrot set can be explained with the equation: $z_{n + 1} = z_{n} ^ 2 + c$. In that equation, c and z are complex numbers and n n is zero or a positive integer (natural number). Starting with $z_0$ = 0, c is in the Mandelbrot set if the absolute value of $z_n$ never becomes larger than a certain number (that number depends on c), no matter how large n gets.

## Quick Start

First clone repo:
```
git clone "https://github.com/flopsreallygotit/MandelbrotSet.git"
```

Then switch to repo directory, then switch to SFML folder and type this:
```
make
./main
```

Don't forget to change flags in Makefile. Now you can research the SSE instructions optimization by yourself!

## First approach

We can calculate each point iteratively.

~~~C++
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
~~~

## Optimizing with SSE instructions

We can calculate 8 points at once using intrinsic functions. Intrinsic function I won't show the example of code, because it's a bit difficult to perceive. Better check it in SFML/mainUtils.cpp.

## Performance

| Version | Compilation flags       | FPS            | Speed Growth |
| ------  | :---------------------: | :------------: | :----------: |
| SLOW    | None                    | 0.629 +- 0.029 | None         |
| SLOW    | -О3                     | 1.16 +- 0.05   | 1.844        |
| SLOW    | -Оfast                  | 1.22 +- 0.05   | 1.94         |
| SLOW    | -mavx -mavx512dq -Оfast | 1.215 +- 0.027 | 1.932        |
| FAST    | -mavx -mavx512dq -О3    | 6.8 +- 0.5     | 10.811       |
| FAST    | -mavx -mavx512dq -Ofast | 7.2 +- 0.8     | 11.447       |

Speed increased about ***11.5 times*** for slowest and fastest version and about ***6 times*** for slow and fast version with -Ofast compilation flag. This confirms the effectivness of SSE instructions.

Also there is negative growth in speed if we don't use optimization flags or we're using SSE instructions on SLOW version, because of ineffecient usage of SIMD registers. 

## Conclusion

SSE instructions allowed us to speed up the calculations *11.5 times*. However the amount of code and it's difficulty became bigger too.

It was too official. Time to fool around.

![image](https://user-images.githubusercontent.com/89828695/230796967-914cdcb5-ee75-4e77-8e00-35b4ebd6235b.png)

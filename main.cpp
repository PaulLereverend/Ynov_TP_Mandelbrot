#include <iostream>
#include <chrono>
#include "SDL2/SDL.h"
#include "./SDLProgram.hpp"
#include "./Mandelbrot.hpp"
#include "./SDLException.hpp"
#include <thread>

void compute(SDLProgram &program, int height, Mandelbrot &mandelbrot)
{
    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now();
    for (int y = 0; y < height; y++)
    {
        program.updateLine(y, mandelbrot.drawLine(y));
    }
    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();

    // Display the total computation time
    std::cout
        << "It took "
        << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count()
        << " milliseconds to compute the fractal." << std::endl;
}

int main()
{

    // Initialize a mandelbrot object of given width and height
    int width = 1000;
    int height = 1000;
    Mandelbrot mandelbrot(width, height, -2.1, 0.6, -1.2, 1.2, 500);
    try
    {

        // Initialize a SDL Program
        SDLProgram program(width, height);

        // Get a time indicator at the start of the computation

        // Compute the Mandelbrot line by line
        /*for (int y = 0; y < height; y++)
        {
            program.updateLine(y, mandelbrot.drawLine(y));
        }*/
        std::thread t(compute, std::ref(program), height, std::ref(mandelbrot));

        // Get a time indicator at the end of the computation
        program.loop();
        t.join();

        // Launch the render loop
    }
    catch (SDLException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}

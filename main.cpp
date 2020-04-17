#include <iostream>
#include <chrono>
#include "SDL2/SDL.h"
#include "./SDLProgram.hpp"
#include "./Mandelbrot.hpp"
#include "./SDLException.hpp"
#include <thread>

void worker(SDLProgram &program, Mandelbrot &mandelbrot, int num_worker, int height, int total_workers)
{
    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now();
    for (int y = num_worker; y < height; y += total_workers)
    {
        program.updateLine(y, mandelbrot.drawLine(y));
    }
    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
    std::cout
        << "It took "
        << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count()
        << " milliseconds to compute this worker." << std::endl;
}
void compute(SDLProgram &program, int height, Mandelbrot &mandelbrot, int nb_workers)
{
    std::thread workers[nb_workers];
    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now();
    for (int i = 1; i <= nb_workers; i++)
    {
        workers[i] = std::thread(worker, std::ref(program), std::ref(mandelbrot), i, height, nb_workers);
    }
    for (int i = 1; i <= nb_workers; i++)
    {
        workers[i].join();
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
    int nb_workers = 4;
    Mandelbrot mandelbrot(width, height, -2.1, 0.6, -1.2, 1.2, 10000);
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
        std::thread t(compute, std::ref(program), height, std::ref(mandelbrot), nb_workers);

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

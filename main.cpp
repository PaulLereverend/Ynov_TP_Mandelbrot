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
    // std::cout
    //     << "It took "
    //     << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count()
    //     << " milliseconds to compute this worker." << std::endl;
}
void compute(SDLProgram &program, int height, Mandelbrot &mandelbrot, int nb_workers)
{
    std::thread workers[nb_workers+1];
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

    // *timeToCompute = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count();

    std::cout << "timeToCompute for " << nb_workers <<" worker(s) : " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count() << std::endl;
    // Display the total computation time
    // std::cout
    //     << "It took "
    //     << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count()
    //     << " milliseconds to compute the fractal." << std::endl;
}
int beforeEtape4(int width, int height, int nb_workers, Mandelbrot mandelbrot)
{
    try
    {
        // Initialize a SDL Program
        SDLProgram program(width, height);

        // Compute the Mandelbrot line by line
        /*for (int y = 0; y < height; y++)
        {
            program.updateLine(y, mandelbrot.drawLine(y));
        }*/
        std::thread t(compute, std::ref(program), height, std::ref(mandelbrot), nb_workers);

        // Launch the render loop
        program.loop();
        t.join();
        return 0;
    }
    catch (SDLException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
int etape4(int width, int height, Mandelbrot mandelbrot)
{
    try
    {
        // Initialize a SDL Program
        SDLProgram program(width, height);
        std::vector< long > timeToCompute = {};
        
        // Get a time indicator at the start of the computation
        std::vector< int > nb_workers = {1, 2, 4, 6, 8, 12, 16, 20, 30, 40};
        for (size_t i = 0; i < nb_workers.size(); i++)
        {
            std::thread t1(compute, std::ref(program), height, std::ref(mandelbrot), nb_workers[i]);
            t1.join();
        }
        // Launch the render loop
        program.loop();
        return 0;
    }
    catch (SDLException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
int main()
{
    // Initialize a mandelbrot object of given width and height
    int width = 1000;
    int height = 1000;
    int nb_workers = 4;
    Mandelbrot mandelbrot(width, height, -2.1, 0.6, -1.2, 1.2, 1000);
    int res = 0;
    // res = beforeEtape4(width, height, nb_workers, mandelbrot);
    res = etape4(width, height, mandelbrot);
    return res;
}

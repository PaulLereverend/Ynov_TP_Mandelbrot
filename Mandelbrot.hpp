#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP
#include <vector>

class Mandelbrot {
    public:
    Mandelbrot(
        int width,
        int height,
        float xmin,
        float xmax,
        float ymin,
        float ymax,
        int max_iterations
        );
    std::vector<unsigned char> drawLine(int lineNumber);

    private:
    int width = 800;
    int height = 800;
    float xmin = -2.1;
    float xmax = 0.6;
    float ymin = -1.2;
    float ymax = 1.2;
    int max_iterations = 20;
};

#endif
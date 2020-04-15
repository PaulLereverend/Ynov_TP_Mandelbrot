#ifndef SDLPROGRAM_HPP
#define SDLPROGRAM_HPP
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>
#include <vector>
#include "./SDLException.hpp"

class SDLProgram {
    private:
        int width = 800;
        int height = 600;
        SDL_Renderer* renderer = nullptr;
        SDL_Window* window = nullptr;
        SDL_Surface* surface = nullptr;

    public:
        SDLProgram(int width, int height);
        void display();
        void loop();
        void updateLine(int lineNumber,std::vector<unsigned char> linePixels);
        ~SDLProgram();
};

#endif
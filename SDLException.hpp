#ifndef SDLEXCEPTION_HPP
#define SDLEXCEPTION_HPP
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class SDLException
{
public:
    SDLException();
    virtual const char *what() const throw();

private:
    std::string msg;
};

#endif
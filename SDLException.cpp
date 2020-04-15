#include "./SDLException.hpp"

SDLException::SDLException() {
    this->msg = std::string("SDL Encountered an error : ") + std::string(SDL_GetError());
}

const char* SDLException::what() const throw() {
    return this->msg.c_str();
}
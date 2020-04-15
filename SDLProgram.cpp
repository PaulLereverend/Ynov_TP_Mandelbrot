#include "./SDLProgram.hpp"

SDLProgram::SDLProgram(int width, int height){
    this->width = width;
    this->height = height;

    // Try initializing the SDL library
    if (SDL_Init( SDL_INIT_VIDEO ) < 0){
        throw SDLException();
    }

    // Create a new window
    this->window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, 0);
    
    // Create a renderer to render to the window
    this->renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);

    // Create a surface to render to
    this->surface = SDL_CreateRGBSurfaceWithFormat(0, this->width, this->height, 32, SDL_PIXELFORMAT_RGB888);
}

void SDLProgram::loop(){
    SDL_Event event;
    
    while (true) {
        // Poll events and react upon QUIT to stop the render loop
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            break;
        }

        // copy the surface onto the window
        this->display();
    }
}

void SDLProgram::display(){

    // create a new texture from the surface
    SDL_Texture * tex = SDL_CreateTextureFromSurface(this->renderer,this->surface);

    // Copy the texture to the renderer
    SDL_RenderCopy(this->renderer,tex,nullptr,nullptr);

    // Apply the renderer state to the screen
    SDL_RenderPresent(this->renderer);
}

void SDLProgram::updateLine(int lineNumber, std::vector<unsigned char> linePixels){
    std::memcpy((void*) ((size_t) this->surface->pixels + (lineNumber * this->surface->pitch)),&linePixels[0],this->surface->pitch);
}

SDLProgram::~SDLProgram(){
    SDL_FreeSurface(this->surface);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
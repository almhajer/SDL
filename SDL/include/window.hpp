#pragma once
#include <precompiled.hpp>

namespace Window {
    class Window {
    public:
        // Constructors and Destructor
        Window();

        ~Window();

        // Initialization method
        bool init();

        // Main run method
        void run();

        // Cleanup method
        void cleanUp();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Texture *texture;
        SDL_Event event;
    };
}


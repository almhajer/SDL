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

        int windowHeight = 750;
        int windowWidth = 1200;

    private:
        SDL_Window *window;

        SDL_Texture *textureLeft = nullptr;
        SDL_Texture *textureRight = nullptr;
        SDL_Texture *currentTexture = nullptr;

        SDL_Renderer *renderer;

        SDL_Surface *surface;

        SDL_Texture *texture;
        SDL_Texture *backgroundTexture;

        SDL_Event event;
    };
}

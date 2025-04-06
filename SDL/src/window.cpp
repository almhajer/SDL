#include <window.hpp>
namespace Window  {

    Window::Window() : window(nullptr), renderer(nullptr), surface(nullptr), texture(nullptr) {}

    bool  Window::init() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
            return false;
        }

        if (!SDL_CreateWindowAndRenderer("لعبة", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
            return false;
        }

        surface = SDL_LoadBMP("../images/sample.bmp");
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
            return false;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);


        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    void  Window::run() {
        while (true) {
            SDL_PollEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {  // تصحيح من SDL_EVENT_QUIT إلى SDL_QUIT
                break;
            }
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
    }

    void  Window::cleanUp() {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    Window::~Window() {
        cleanUp();
    }


};
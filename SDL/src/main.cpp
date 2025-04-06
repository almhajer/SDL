#include <iostream>
#include<window.hpp>


int main(int argc, char* argv[]) {
    Window::Window app;

    if (!app.init()) {
        return 3;
    }

    app.run();
    app.cleanUp();

    return 0;
}

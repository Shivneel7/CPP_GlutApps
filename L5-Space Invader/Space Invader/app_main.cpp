#include "App.h"

int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv, 640, 640, "Shiv's Space Invader");

    app->run();
}

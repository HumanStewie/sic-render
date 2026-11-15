#include "game_engine/game_engine.h"

GameEngine gEngine{ 1280, 720 };

// This is where i want to initialize the BACKEND and the FRONTEND
int main() {
    
    while (gEngine.GameIsOpen()) {
        gEngine.Update();
    }

    
    return 0;
}
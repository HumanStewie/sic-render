#include "game_engine/game_engine.h"

int main() {
    GameEngine engine{ 1280, 720 };

    while (engine.GameIsOpen()) {
        engine.Update();
    }

    
    return 0;
}
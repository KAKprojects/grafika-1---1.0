#include "Engine.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Engine engine("Demo", 800, 800);
    
    if (!engine.init()) {
        return 1;
    }
    
    // Jeśli argument "demo" — renderuj do PNG bez okna
    if (argc > 1 && std::string(argv[1]) == "demo") {
        engine.renderToFile("screenshot.png");
        std::cout << "Demo screenshot zapisany: screenshot.png" << std::endl;
    } else {
        // Normalnie uruchamia okno
        engine.run();
    }
    
    engine.shutdown();
    
    return 0;
}
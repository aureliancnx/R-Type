#include "GameManager.hpp"
#include "KapEngine.hpp"
#include "Factory.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "Debug.hpp"

static void initWindow(KapEngine::KapEngine *engine) {
    KapEngine::Tools::Vector2 screenSize(720, 480);
    engine->setScreenSize(screenSize);

    engine->getSplashScreen()->setDisplayKapEngineLogo(false);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine->getGraphicalLibManager());
    engine->getGraphicalLibManager()->addLib(raylib);
    engine->getGraphicalLibManager()->changeLib("raylib");
}

static void startClient(KapEngine::KapEngine *engine) {
    initWindow(engine);

    RType::GameManager gameManager(*engine);

    try {
        gameManager.launchGame();
    } catch(KapEngine::Errors::Error e) {
        KAP_DEBUG_ERROR("Problem detected: " + std::string(e.what()));
    }
}

static void startServer(KapEngine::KapEngine *engine) {
    initWindow(engine);

    RType::GameManager gameManager(*engine);

    try {
        gameManager.launchGame();
    } catch(KapEngine::Errors::Error e) {
        KAP_DEBUG_ERROR("Problem detected: " + std::string(e.what()));
    }
}

int main(int argc, char **argv) {
    bool isServer = false;
    if (argc > 1) {
        if (std::string(argv[1]) == "server") {
            isServer = true;
        }
    }

    KapEngine::KapEngine engine(false, "R-Type", "1.0.0", "Epitech");

    if (isServer) {
        startServer(&engine);
    } else {
        startClient(&engine);
    }

    engine.run();
    return 0;
}
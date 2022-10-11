#include "GameManager.hpp"
#include "ServerManager.hpp"
#include "KapEngine.hpp"
#include "Factory.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "Debug.hpp"

static void initWindow(KapEngine::KEngine *engine) {
    KapEngine::Tools::Vector2 screenSize(720, 480);
    engine->setScreenSize(screenSize);

    engine->getSplashScreen()->setDisplayKapEngineLogo(false);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine->getGraphicalLibManager());
    engine->getGraphicalLibManager()->addLib(raylib);
    engine->getGraphicalLibManager()->changeLib("raylib");
}

int main(int argc, char **argv) {
    bool isServer = false;
    if (argc > 1) {
        if (std::string(argv[1]) == "--server") {
            isServer = true;
        }
    }

    KapEngine::KEngine engine(false, "R-Type", "1.0.0", "Epitech");
    initWindow(&engine);

    RType::GameManager gameManager(&engine);
    RType::ServerManager serverManager(&engine);

    if (isServer) {
        serverManager.launchServer();
    } else {
        gameManager.launchGame();
    }

    engine.run();
    return 0;
}
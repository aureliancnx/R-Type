#include "GameManager.hpp"
#include "KapEngine.hpp"
#include "Factory.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "Debug.hpp"

static void initWindow(KapEngine::KapEngine *engine) {
    engine->getSplashScreen()->setDisplayKapEngineLogo(false);

    KapEngine::Tools::Vector2 screenSize(720, 480);
    engine->setScreenSize(screenSize);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine->getGraphicalLibManager());
    engine->getGraphicalLibManager()->addLib(raylib);
    engine->getGraphicalLibManager()->changeLib("raylib");
}

int main(int argc, char **argv) {
    KapEngine::KapEngine engine(false, "R-Type", "1.0.0", "Epitech");
    initWindow(&engine);

    RType::GameManager gameManager(engine);

    try {
        gameManager.launchGame();
    } catch(KapEngine::Errors::Error e) {
        KAP_DEBUG_ERROR("Problem detected: " + std::string(e.what()));
    }

    engine.run();
    return 0;
}
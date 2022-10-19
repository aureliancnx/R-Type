#include "GameManager.hpp"
#include "KapEngine.hpp"
#include "Factory.hpp"
#include "Graphical/RaylibGraphical.hpp"
#include "Debug.hpp"

#include "KapScript/ScriptEngine.hpp"

static void initWindow(KapEngine::KEngine *engine, bool draw)
{
    KapEngine::Tools::Vector2 screenSize(1280, 720);
    engine->setScreenSize(screenSize);

    engine->getSplashScreen()->setDisplayKapEngineLogo(false);

    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*engine->getGraphicalLibManager(), draw);
    engine->getGraphicalLibManager()->addLib(raylib);
    engine->getGraphicalLibManager()->changeLib("raylib");
}

int main(int argc, char **argv)
{
    bool isServer = false;
    bool isTestScript = false;

    if (argc > 1) {
        if (std::string(argv[1]) == "--server") {
            isServer = true;
        } else if (std::string(argv[1]) == "--test-script") {
            isTestScript = true;
        }
    }

    if (isTestScript) {
        std::cout << "Test script" << std::endl;
        KapScript::ScriptEngine scriptEngine;
        scriptEngine.loadScript("Packages/KapScript/Exemples/Test.ks");
        return 0;
    }

    KapEngine::KEngine engine(false, "R-Type", "1.0.0", "Epitech");
    engine.setEngineThread(false);
    initWindow(&engine, !isServer);

    RType::GameManager gameManager(&engine);
    if (isServer) {
        gameManager.launchServer();
    } else {
        gameManager.launchGame();
    }

    engine.run();
    return 0;
}
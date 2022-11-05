#include "GameManager.hpp"
#include "Factory.hpp"
#include "Debug.hpp"
#include "KapRaylib/KapRaylib.hpp"

static void initWindow(KapEngine::KEngine* engine, bool draw) {
    KapEngine::Tools::Vector2 screenSize(1280, 720);
    engine->setScreenSize(screenSize);

    auto libManager = engine->getGraphicalLibManager();
    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*libManager);

    libManager->addLib(raylib);
    libManager->changeLib(raylib->getName());
}

// #include "MapScript/MapScript.hpp"

// static void test_main() {
//     RType::MapScript script;

//     try {
//         script.loadScript("Maps/testMap.lua");
//     } catch (RType::LuaException& e) {
//         KapEngine::Debug::error(e.what());
//     }
// }

int main(int argc, char** argv) {
    // test_main();
    bool isServer = false;

    if (argc > 1) {
        if (std::string(argv[1]) == "--server") {
            isServer = true;
        }
    }

    KapEngine::KEngine engine(false, "R-Type", "1.0.0", "Epitech");

    initWindow(&engine, !isServer);

    RType::GameManager gameManager(&engine, false);
    if (isServer) {
        gameManager.launchServer();
    } else {
        gameManager.launchGame();
    }

    engine.run();
    return 0;
}
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

//#include "MapScript/MapScript.hpp"
//#include "Prefabs.hpp"
//
// static void test_main(KapEngine::KEngine* engine) {
//     RType::MapScript script(engine);
//
//     auto scene = engine->getSceneManager()->getScene("Default Scene");
//
//     RType::Prefabs::registerBoubouleEnemyPrefab(*engine);
//
//     try {
//         script.loadScript("Maps/testMap.lua");
//
//         script.spawnEnemie(scene, "Bouboule2", 0, 100, 100, 50);
//
//         script.closeScript();
//     } catch (RType::LuaException& e) {
//         KapEngine::Debug::error(e.what());
//     } catch (std::exception& e) {
//         KapEngine::Debug::error(e.what());
//     }
// }

int main(int argc, char** argv) {
    bool isServer = false;

    if (argc > 1) {
        if (std::string(argv[1]) == "--server") {
            isServer = true;
        }
    }

    KapEngine::KEngine engine(false, "R-Type", "1.0.0", "Epitech");

    initWindow(&engine, !isServer);

//    test_main(&engine);

    RType::GameManager gameManager(&engine, false);
    if (isServer) {
        gameManager.launchServer();
    } else {
        gameManager.launchGame();
    }

    engine.run();
    return 0;
}
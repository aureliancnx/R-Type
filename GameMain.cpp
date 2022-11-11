#include "GameManager.hpp"
#include "Factory.hpp"
#include "Debug.hpp"
#include "KapRaylib/KapRaylib.hpp"

static void initWindow(KapEngine::KEngine* engine, bool draw) {
    KapEngine::Tools::Vector2 screenSize(1280, 720);
    engine->setScreenSize(screenSize);

    auto libManager = engine->getGraphicalLibManager();
    auto raylib = std::make_shared<KapEngine::Graphical::Raylib::RaylibGraphical>(*libManager, draw);

    libManager->addLib(raylib);
    libManager->changeLib(raylib->getName());
}

/*
#include "MapScript/MapScript.hpp"
#include "Prefabs.hpp"

 static void test_main(KapEngine::KEngine* engine, RType::MapScript& script) {
     auto& scene = engine->getSceneManager()->getScene("Default Scene");

     RType::Prefabs::registerBulletPrefab(*engine);

     try {
         script.loadScript("Maps/TestMap.lua");

         auto spawnEnemies = script.getSpawnedEnemies();
         for (auto& spawnEnemy : spawnEnemies) {
             script.spawnEnemy(scene, spawnEnemy.name, spawnEnemy.startPositionY, spawnEnemy.startPositionX, spawnEnemy.enemyHp);
         }
     } catch (RType::LuaException& e) {
         KapEngine::Debug::error(e.what());
     } catch (std::exception& e) {
         KapEngine::Debug::error(e.what());
     }
 }

int main(int argc, char** argv) {
    // Fix path
    try {
        if (argc > 0 && argv[0]) {
            auto path = std::filesystem::path(argv[0]);
            auto finalPath = std::filesystem::weakly_canonical(path).parent_path();
            std::filesystem::current_path(finalPath);
        }
    }catch(...) {
        KAP_DEBUG_ERROR("Unable to set path of assets to current executable directory.");
    }

    bool isServer = false;

    if (argc > 1) {
        if (std::string(argv[1]) == "--server") {
            isServer = true;
        }
    }

    KapEngine::KEngine engine(false, "R-Type", "1.0.0", "Epitech");

    initWindow(&engine, !isServer);

    RType::MapScript script(&engine);
    test_main(&engine, script);

    engine.run();
    script.closeScript();
    return 0;
}*/

int main(int argc, char** argv) {
    // Fix path
    try {
        if (argc > 0 && argv[0]) {
            auto path = std::filesystem::path(argv[0]);
            auto finalPath = std::filesystem::weakly_canonical(path).parent_path();
            std::filesystem::current_path(finalPath);
        }
    } catch (...) { KAP_DEBUG_ERROR("Unable to set path of assets to current executable directory."); }

    bool isServer = false;
    bool graphical = false;

    if (argc > 1) {
        if (std::string(argv[1]) == "--server") {
            isServer = true;
            graphical = false;
        } else if (std::string(argv[1]) == "--graphicalserver") {
            isServer = true;
            graphical = true;
        }
    }

    KapEngine::KEngine engine(false, "R-Type", "1.0.0", "Epitech");

    initWindow(&engine, !isServer || graphical);

    RType::GameManager gameManager(&engine, false);
    if (isServer) {
        gameManager.launchServer();
    } else {
        gameManager.launchGame();
    }

    engine.run();
    return 0;
}

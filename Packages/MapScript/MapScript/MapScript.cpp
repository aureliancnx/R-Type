#include "MapScript.hpp"
#include "Script/DebugScript.hpp"
#include "Script/Vector2Script.hpp"
#include "Script/RectangleScript.hpp"
#include "Script/MathScript.hpp"
#include "EnemyController.hpp"
#include "Prefabs.hpp"
#include "Collider.hpp"
#include "KapMirror/KapMirror.hpp"
#include "Animations/SpriteAnimation.hpp"
#include <fstream>
#include <cstring>

using namespace RType;

MapScript::MapScript(KapEngine::KEngine* _engine, bool _isLoadedByServer) : engine(*_engine), isLoadedByServer(_isLoadedByServer) {}

void MapScript::loadScript(const std::string& scriptPath) {
    std::ifstream ifs(scriptPath);
    if (!ifs.is_open()) {
        throw LuaException("Can't open file '" + scriptPath + "'");
    }

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    executeScript(content);
}

void MapScript::executeScript(const std::string& script) {
    if (L != nullptr) {
        throw LuaException("Script is already loaded");
    }

    spawnEnemies.clear();
    destroyNewEnemies();

    L = luaL_newstate();

    // Load Lua scripts
    Script::Debug::initScript(L);
    Script::Vector2::initScript(L);
    Script::Rectangle::initScript(L);
    Script::Math::initScript(L);
    Script::Enemy::initScript(L, this);
    initScript();

    int doResult = luaL_dostring(L, script.c_str());
    if (doResult != LUA_OK) {
        std::string error = lua_tostring(L, -1);
        lua_pop(L, 1);
        lua_close(L);
        throw LuaException("Something went wrong during execution: " + error);
    }

    // Check if the script is valid
    verifScript();

    // Create enemies
    for (auto& enemy : newEnemies) {
        createNewEnemy(enemy);
    }
}

void MapScript::initScript() {
    auto setMapName = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapName = lua_tostring(L, 1);
        manager->_setMapName(mapName);
        return 0;
    };

    auto setMapAuthor = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapAuthor = lua_tostring(L, 1);
        manager->_setMapAuthor(mapAuthor);
        return 0;
    };

    auto setMapDescription = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string mapDescription = lua_tostring(L, 1);
        manager->_setMapDescription(mapDescription);
        return 0;
    };

    auto setMapBannerPath = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string path = lua_tostring(L, 1);
        manager->_setMapBannerPath(path);
        return 0;
    };

    auto spawnMapEnemy = [](lua_State* L) -> int {
        auto* manager = (MapScript*)lua_touserdata(L, lua_upvalueindex(1));

        std::string enemyName = lua_tostring(L, 1);
        auto spawnTime = (int)lua_tonumber(L, 2);
        auto startPositionY = (float)lua_tonumber(L, 3);
        auto startPositionX = (float)lua_tonumber(L, 4);
        auto enemyHp = (int)lua_tonumber(L, 5);

        manager->_registerSpawnEnemy(enemyName, spawnTime, startPositionY, startPositionX, enemyHp);
        return 0;
    };

    lua_newtable(L);
    int mapTableIdx = lua_gettop(L);
    lua_pushvalue(L, mapTableIdx);
    lua_setglobal(L, "Map");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapName, 1);
    lua_setfield(L, -2, "SetName");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapAuthor, 1);
    lua_setfield(L, -2, "SetAuthor");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapDescription, 1);
    lua_setfield(L, -2, "SetDescription");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, setMapBannerPath, 1);
    lua_setfield(L, -2, "SetBannerPath");

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, spawnMapEnemy, 1);
    lua_setfield(L, -2, "SpawnEnemy");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, mapTableIdx);
    lua_settable(L, -3);
}

void MapScript::verifScript() {
    if (name.empty()) {
        throw LuaException("Map name is not set or empty");
    }
    if (author.empty()) {
        throw LuaException("Map author is not set or empty");
    }
    if (description.empty()) {
        throw LuaException("Map description is not set or empty");
    }

    // TODO: Transform this into avalaible
    if (isLoadedByServer && !newEnemies.empty()) {
        throw LuaException("Modded map is not supported by server");
    }

    for (auto& enemy : newEnemies) {
        checkNewEnemy(enemy);
    }
}

void MapScript::checkNewEnemy(Script::Enemy* enemy) {
    if (enemy->name.empty()) {
        throw LuaException("Enemy name is not set or empty");
    }
    if (enemy->pathSprite.empty()) {
        throw LuaException("Enemy sprite path is not set or empty");
    }
    if (enemy->rectangle->w <= 0) {
        throw LuaException("Enemy width is not set or empty");
    }
    if (enemy->rectangle->h <= 0) {
        throw LuaException("Enemy height is not set or empty");
    }
}

void MapScript::createNewEnemy(Script::Enemy* enemy) {
    KapEngine::Debug::log("Create new enemy: " + enemy->name);

    engine.getPrefabManager()->createPrefab(
        "Enemy:" + enemy->name, [this](KapEngine::SceneManagement::Scene& scene, const std::string& _name) {
            auto enemy = getNewEnemy(_name);
            if (enemy == nullptr) {
                throw std::runtime_error("Can't find enemy with name: " + _name);
            }

            auto enemyObject = KapEngine::UI::UiFactory::createCanvas(scene, _name);
            enemyObject->setTag("Collider");

            auto networkIdentityComp = std::make_shared<KapMirror::NetworkIdentity>(enemyObject);
            enemyObject->addComponent(networkIdentityComp);

            auto networkTransformComponent = std::make_shared<KapMirror::NetworkTransform>(enemyObject);
            networkTransformComponent->setClientAuthority(false);
            networkTransformComponent->setActiveUpdate(false);
            networkTransformComponent->setActiveLateUpdate(true);
            enemyObject->addComponent(networkTransformComponent);

            auto controller = std::make_shared<EnemyController>(enemyObject);
            enemyObject->addComponent(controller);

            auto collider = std::make_shared<KapEngine::Collider>(enemyObject, true);
            enemyObject->addComponent(collider);

            auto imageComp = std::make_shared<KapEngine::UI::Image>(enemyObject);
            imageComp->setRectangle({enemy->rectangle->x, enemy->rectangle->y, enemy->rectangle->w, enemy->rectangle->h});
            imageComp->setPathSprite(enemy->pathSprite);
            enemyObject->addComponent(imageComp);

            auto& canvas = enemyObject->getComponent<KapEngine::UI::Canvas>();
            canvas.setResizeType(KapEngine::UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);

            auto& transform = enemyObject->getComponent<KapEngine::Transform>();
            transform.setPosition({0, 0, 0});
            transform.setScale({enemy->scale->x, enemy->scale->y, 0});

            // Animation
            auto animationIdle = std::make_shared<SpriteAnimation>(enemyObject);
            enemyObject->addComponent(animationIdle);

            KapEngine::Time::ETime duration;
            duration.setSeconds(.5f);
            animationIdle->setTiming(duration);
            animationIdle->loop(true);
            animationIdle->setRect({enemy->rectangle->x, enemy->rectangle->y, enemy->rectangle->w, enemy->rectangle->h});
            animationIdle->setNbAnimations(12);

            auto animator = std::make_shared<KapEngine::Animator>(enemyObject);
            enemyObject->addComponent(animator);

            animator->addAnim(animationIdle, "Idle");
            animator->addLink("Idle", "Idle");

            return enemyObject;
        });
}

void MapScript::_setMapName(const std::string& _name) { name = _name; }

void MapScript::_setMapAuthor(const std::string& _author) { author = _author; }

void MapScript::_setMapDescription(const std::string& _description) { description = _description; }

void MapScript::_setMapBannerPath(const std::string& _path) { bannerPath = _path; }

void MapScript::_registerNewEnemy(Script::Enemy* enemy) { newEnemies.push_back(enemy); }

void MapScript::_registerSpawnEnemy(const std::string& _name, int spawnTime, float startPositionY, float startPositionX, int enemyHp) {
    // Check values
    if (_name.empty()) {
        throw LuaException("Enemy name is empty");
    }
    if (spawnTime < 0) {
        throw LuaException("Spawn time can't be negative");
    }
    if (startPositionY < 0) {
        throw LuaException("Start position Y can't be negative");
    }
    if (startPositionX < 0) {
        throw LuaException("Start position X can't be negative");
    }
    if (enemyHp < 0) {
        throw LuaException("Enemy HP can't be negative");
    }
    if (enemyHp == 0) {
        throw LuaException("Enemy HP can't be 0");
    }
    if (startPositionX == 0) {
        startPositionX = 1280 + 100; // Constant
    }

    spawnEnemies.push_back({_name, spawnTime, startPositionY, startPositionX, enemyHp});
}

void MapScript::destroyNewEnemies() {
    for (auto enemy : newEnemies) {
        enemy->~Enemy();
    }
    newEnemies.clear();
}

void MapScript::closeScript() {
    if (L == nullptr) {
        return;
    }

    lua_close(L);
    destroyPrefabEnemies();
    destroyNewEnemies();

    spawnEnemies.clear();

    L = nullptr;
}

void MapScript::destroyPrefabEnemies() {
    for (auto& enemy : spawnEnemies) {
        engine.getPrefabManager()->removePrefab("Enemy:" + enemy.name);
    }
}

void MapScript::spawnEnemy(KapEngine::SceneManagement::Scene& scene, const std::string& enemyName, float startPositionY,
                           float startPositionX, int enemyHp) {
    std::shared_ptr<KapEngine::GameObject> enemy;
    if (!engine.getPrefabManager()->instantiatePrefab("Enemy:" + enemyName, scene, enemy)) {
        KapEngine::Debug::error("Can't spawn enemy: " + enemyName + " (Prefab: 'Enemy:" + enemyName + "' not found)");
        return;
    }

    auto& controller = enemy->getComponent<EnemyController>();
    controller.setHp(enemyHp);

    auto& transform = enemy->getComponent<KapEngine::Transform>();
    if (startPositionX == 0) {
        startPositionX = 1280 + 100; // Constant
    } else {
        startPositionX = 1280 - startPositionX;
    }
    transform.setPosition({startPositionX, startPositionY, 0});
}

Script::Enemy* MapScript::getNewEnemy(const std::string& enemyName) {
    for (auto& enemy : newEnemies) {
        if ("Enemy:" + enemy->name == enemyName) {
            return enemy;
        }
    }
    return nullptr;
}

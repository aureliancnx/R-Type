#pragma once

#include "KapEngine.hpp"
#include "Debug.hpp"
#include "Lua.hpp"
#include "Script/EnemyScript.hpp"
#include "LuaException.hpp"
#include <vector>

namespace RType::Script {
    class Enemy;
}

namespace RType {
    struct SpawnEnemy {
        std::string name;     // Name of the enemy
        int spawnTime;        // Time when the enemy will spawn (in seconds)
        float startPositionY; // Start position Y of the enemy
        float startPositionX; // Start position X of the enemy
        int enemyHp;          // Enemy HP
    };

    class MapScript {
      private:
        KapEngine::KEngine &engine;
        bool isLoadedByServer;

        lua_State *L = nullptr;

        std::string name;        // Name of the map
        std::string author;      // Author of the map
        std::string description; // Description of the map
        std::string bannerPath;  // Path of the banner of the map

        std::vector<Script::Enemy *> newEnemies; // List of new enemies
        std::vector<SpawnEnemy> spawnEnemies;    // List of enemies to spawn

      public:
        explicit MapScript(KapEngine::KEngine *_engine, bool _isLoadedByServer = false);
        ~MapScript();

        /**
         * @brief Load map script.
         * @param scriptPath Path to script
         * @throw LuaException If script can't be loaded or if script is invalid.
         */
        void loadScript(const std::string &scriptPath);

        /**
         * @brief Close map script.
         */
        void closeScript();

        /**
         * @brief Get map name.
         * @return Map name
         */
        std::string getName() const { return name; }

        /**
         * @brief Get map author.
         * @return Map author
         */
        std::string getAuthor() const { return author; }

        /**
         * @brief Get map description.
         * @return Map description
         */
        std::string getDescription() const { return description; }

        /**
         * @brief Get map banner path.
         * @return Map banner path
         */
        std::string getBannerPath() const { return bannerPath; }

        /**
         * @brief Get spawn enemies.
         * @return Spawn enemies
         */
        std::vector<SpawnEnemy> getSpawnedEnemies() const { return spawnEnemies; }

        /**
         * @brief Is Modded Map (new enemies, custom path, ...).
         * @return True if map is modded, false otherwise
         */
        bool isModded() const;

        /**
         * @brief Spawn enemy.
         * @param scene Scene where enemy will be spawned
         * @param enemyName Name of the enemy (without "Enemy" suffix)
         * @param startPositionY Start position Y of the enemy
         * @param startPositionX Start position X of the enemy
         * @param enemyHp Enemy HP
         */
        void spawnEnemy(KapEngine::SceneManagement::Scene &scene, const std::string &enemyName, float startPositionY, float startPositionX,
                        int enemyHp);

        // Internal functions for Lua
        void _setMapName(const std::string &name);
        void _setMapAuthor(const std::string &author);
        void _setMapDescription(const std::string &description);
        void _setMapBannerPath(const std::string &bannerPath);
        void _registerNewEnemy(Script::Enemy *enemy);
        void _registerSpawnEnemy(const std::string &name, int spawnTime, float startPositionY, float startPositionX, int enemyHp);
        void _instanciatePrefab(const std::string &prefabName, float positionX, float positionY);

        KapEngine::Tools::Vector3 _updateEnemy(const std::string &enemyName, const KapEngine::Tools::Vector3 &position);

      private:
        void executeScript(const std::string &script);

        void verifScript();

        Script::Enemy *getNewEnemy(const std::string &enemyName);

        void checkNewEnemy(Script::Enemy *enemy);

        void createNewEnemy(Script::Enemy *enemy);

        void initScript();

        void destroyPrefabEnemies();
    };
} // namespace RType

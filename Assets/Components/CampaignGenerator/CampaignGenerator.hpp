//
// Created by leq on 25/10/22.
//

#ifndef RTYPE_CAMPAIGNGENERATOR_HPP
#define RTYPE_CAMPAIGNGENERATOR_HPP

#include <utility>

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
namespace RType {
    class CampaignGenerator : public KapEngine::Component {
      public:
        struct Enemy {
            int _positionY;
            int _positionX;
            int _time;
            std::string _mobName;
            explicit Enemy(std::string mobName, int positionY = 0, int time = 10, int positionX = 1280) {
                _mobName = std::move(mobName);
                _time = time;
                _positionY = positionY;
                _positionX = positionX;
            }
        };
        explicit CampaignGenerator(std::shared_ptr<KapEngine::GameObject> go);

        ~CampaignGenerator();

        void onFixedUpdate() override;

        void onAwake() override;

        std::shared_ptr<KapEngine::GameObject> spawnMob(std::string const &mobName, KapEngine::SceneManagement::Scene &scene);

        void addEnemy(Enemy const &enemy);

      private:
        std::vector<Enemy> _enemies;
        KapEngine::Time::EClock _clock;
        KapEngine::Time::ETime _time;
    };
} // namespace RType
#endif // RTYPE_CAMPAIGNGENERATOR_HPP

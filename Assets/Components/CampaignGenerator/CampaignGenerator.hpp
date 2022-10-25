//
// Created by leq on 25/10/22.
//

#ifndef RTYPE_CAMPAIGNGENERATOR_HPP
#define RTYPE_CAMPAIGNGENERATOR_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
namespace RType
{
    class CampaignGenerator : public KapEngine::Component
    {

      public:
        CampaignGenerator(std::shared_ptr<KapEngine::GameObject> go);

        ~CampaignGenerator();

        void onFixedUpdate() override;

        void onAwake() override;

        std::shared_ptr<KapEngine::GameObject> spawnMob(std::string const &mobName, KapEngine::SceneManagement::Scene &scene);

      private:
        std::vector<int> positionYEnemy;
        int Id;
        int delay;
    };
} // namespace RType
#endif // RTYPE_CAMPAIGNGENERATOR_HPP

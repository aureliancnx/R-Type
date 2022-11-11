/*
** EPITECH PROJECT, 2022
** RType
** File description:
** CampaignManager
*/

#ifndef RTYPE_CAMPAIGNMANAGER_HPP_
#define RTYPE_CAMPAIGNMANAGER_HPP_

#include "KapEngine.hpp"
#include "MapScript/MapScript.hpp"

namespace RType {

    class CampaignManager : public KapEngine::Component {
      public:
        CampaignManager(std::shared_ptr<KapEngine::GameObject> go);
        ~CampaignManager();

        void onAwake() override;
        void onFixedUpdate() override;

        #if IS_MAX_KAPENGINE_VERSION(1, 215)
          void onSceneChanged();
        #else
          void onSceneChanged() override;
        #endif

      protected:
      private:
        KapEngine::Time::EClock _clock;
        std::shared_ptr<MapScript> _mapScript;
        std::vector<SpawnEnemy> _enemies;
        KapEngine::Time::ETime _lastElapsed;
        KapEngine::SceneManagement::Scene& _scene;
    };

} // namespace RType

#endif /* !CAMPAIGNMANAGER_HPP_ */
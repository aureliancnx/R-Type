#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "GameManager.hpp"

namespace RType {
    class MenuCampaignSelector : public KapEngine::Component {
      private:
        struct Campaign {
            std::string name;
            std::string description;
            std::string scriptPath;
            std::string author;
            std::string image;
        };

      private:
        GameManager &gameManager;

        std::size_t _currentMap = 0;
        std::size_t _nbMaps = 0;
        std::vector<Campaign> _campaigns;

        std::shared_ptr<KapEngine::GameObject> _buttonLevel1;
        std::shared_ptr<KapEngine::GameObject> _buttonLevel2;
        std::shared_ptr<KapEngine::GameObject> _buttonLeft;
        std::shared_ptr<KapEngine::GameObject> _buttonRight;

      public:
        explicit MenuCampaignSelector(std::shared_ptr<KapEngine::GameObject> go, GameManager &_gameManager);
        ~MenuCampaignSelector() = default;

        void onAwake() override;

        void buttonNextMaps();
        void buttonPreviousMaps();
        void buttonPlayFirst();
        void buttonPlaySecond();

        void setButtonLevel1(const std::shared_ptr<KapEngine::GameObject> &btn);
        void setButtonLevel2(const std::shared_ptr<KapEngine::GameObject> &btn);
        void setButtonLeft(const std::shared_ptr<KapEngine::GameObject> &btn);
        void setButtonRight(const std::shared_ptr<KapEngine::GameObject> &btn);

      private:
        void getLuaInformation();
        void openFolderLua();

        void updateButtons();
        std::string formatText(const std::string &text);
    };
} // namespace RType

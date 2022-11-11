#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "MapScript/MapScript.hpp"

#ifndef BENJI_MODIF
#define BENJI_MODIF true
#endif

namespace RType {
    class MenuCampaignSelector : public KapEngine::Component {
      public:
        MenuCampaignSelector(std::shared_ptr<KapEngine::GameObject> go, KapEngine::KEngine* engine);
        ~MenuCampaignSelector();

        void onUpdate() override;

        void onAwake() override;

#if BENJI_MODIF
        struct Campaign {
            std::string name;
            std::string description;
            std::string scriptPath;
            std::string author;
            std::string image;

            Campaign() {
                name = "";
                description = "";
                scriptPath = "";
                author = "";
                image = "";
            }
        };

        void buttonNextMaps();
        void buttonPreviousMaps();
        void buttonPlayFirst();
        void buttonPlaySecond();

        void setButtonLevel1(std::shared_ptr<KapEngine::GameObject> btn);
        void setButtonLevel2(std::shared_ptr<KapEngine::GameObject> btn);
        void setButtonLeft(std::shared_ptr<KapEngine::GameObject> btn);
        void setButtonRight(std::shared_ptr<KapEngine::GameObject> btn);
#endif

      private:
        KapEngine::KEngine* _engine;

        void getLuaInformation();
        void openFolderLua();

        void updateButtons();

#if BENJI_MODIF
        std::size_t _currentMap = 0;
        std::size_t _nbMaps = 0;
        std::vector<Campaign> _campaigns;

        std::shared_ptr<KapEngine::GameObject> _buttonLevel1;
        std::shared_ptr<KapEngine::GameObject> _buttonLevel2;
        std::shared_ptr<KapEngine::GameObject> _buttonLeft;
        std::shared_ptr<KapEngine::GameObject> _buttonRight;
#else
        void foundDescription();
        void foundCreator();
        void foundName();
        void foundButton();
        std::vector<std::string> _img;
        std::vector<std::string> _name;
        std::vector<std::string> _description;
        std::vector<std::string> _creator;
        std::vector<std::string> _pathScript;

        std::shared_ptr<KapEngine::GameObject> _txtDescription;
        std::shared_ptr<KapEngine::GameObject> _txtDescriptionBis;
        std::shared_ptr<KapEngine::GameObject> _txtCreator;
        std::shared_ptr<KapEngine::GameObject> _txtName;
        std::shared_ptr<KapEngine::GameObject> _imgCampaign;
        std::shared_ptr<KapEngine::GameObject> _txtNameBis;
        std::shared_ptr<KapEngine::GameObject> _txtCreatorBis;
        std::shared_ptr<KapEngine::GameObject> _imgCampaignBis;
        std::shared_ptr<KapEngine::GameObject> _button1;
        std::shared_ptr<KapEngine::GameObject> _button2;

        int lastValue = 0;
#endif
    };
} // namespace RType

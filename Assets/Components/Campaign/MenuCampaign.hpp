//
// Created by leq on 20/10/22.
//

#ifndef RTYPE_MENUCAMPAIGN_HPP
#define RTYPE_MENUCAMPAIGN_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"
#include "MapScript/MapScript.hpp"

namespace RType {
    class MenuCampaign : public KapEngine::Component {
      public:
        MenuCampaign(std::shared_ptr<KapEngine::GameObject> go, KapEngine::KEngine* engine);
        ~MenuCampaign();

        void onUpdate() override;

        void onAwake() override;

      private:
        KapEngine::KEngine* _engine;

        void getLuaInformation();
        void openFolderLua();

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
    };
} // namespace RType

#endif // RTYPE_MENUCAMPAIGN_HPP

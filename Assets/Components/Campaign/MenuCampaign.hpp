//
// Created by leq on 20/10/22.
//

#ifndef RTYPE_MENUCAMPAIGN_HPP
#define RTYPE_MENUCAMPAIGN_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "Button/Button.hpp"

namespace RType
{
    class MenuCampaign : public KapEngine::Component
    {
      public:
        MenuCampaign(std::shared_ptr<KapEngine::GameObject> go);
        ~MenuCampaign();

        void onUpdate() override;

        void onAwake() override;

      private:
        void foundDate();
        void foundCreator();
        void foundName();
        void foundButton();
        std::vector<std::string> _img;
        std::vector<std::string> _name;
        std::vector<std::string> _date;
        std::vector<std::string> _creator;
        std::shared_ptr<KapEngine::GameObject> _txtDate;
        std::shared_ptr<KapEngine::GameObject> _txtCreator;
        std::shared_ptr<KapEngine::GameObject> _txtName;
        std::shared_ptr<KapEngine::GameObject> _imgCampaign;
        std::shared_ptr<KapEngine::GameObject> _txtDateBis;
        std::shared_ptr<KapEngine::GameObject> _txtNameBis;
        std::shared_ptr<KapEngine::GameObject> _txtCreatorBis;
        std::shared_ptr<KapEngine::GameObject> _imgCampaignBis;
        std::shared_ptr<KapEngine::GameObject> _button1;
        std::shared_ptr<KapEngine::GameObject> _button2;
        int lastValue;
    };
} // namespace RType

#endif // RTYPE_MENUCAMPAIGN_HPP

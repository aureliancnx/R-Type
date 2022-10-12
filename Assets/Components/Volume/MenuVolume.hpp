//
// Created by leq on 12/10/22.
//

#ifndef RTYPE_MENUVOLUME_HPP
#define RTYPE_MENUVOLUME_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {

    class MenuVolume : public KapEngine::Component {
    public:
        MenuVolume(std::shared_ptr<KapEngine::GameObject> go);
        ~MenuVolume();

        void onUpdate() override;
        void onAwake() override;

    protected:
    private:
        void foundText();
        std::vector<std::string> _type;
        std::shared_ptr<KapEngine::GameObject> _txt;
        int lastValue;
    };

}


#endif //RTYPE_MENUVOLUME_HPP

//
// Created by leq on 12/11/22.
//

#ifndef RTYPE_CONVERTENUM_HPP
#define RTYPE_CONVERTENUM_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineEvents.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

using namespace KapEngine;

namespace RType {

    class ConvertEnum : public Component {
      public:
        ConvertEnum(std::shared_ptr<GameObject> go, std::string prefsKey,
                    std::string prefix = "Move Up : ", KapEngine::Events::Key::EKey basicKey = KapEngine::Events::Key::Z);
        ~ConvertEnum();

        static std::string KeyToString(int e);

        void onAwake() override;
        void onUpdate() override;
        void setTextKey();

      protected:
      private:
        std::shared_ptr<KapEngine::GameObject> _buttonKeyBoard;
        std::string _prefix;
        std::string _prefKey;
        KapEngine::Events::Key::EKey _basicKey;
    };

} // namespace RType

#endif // RTYPE_CONVERTENUM_HPP

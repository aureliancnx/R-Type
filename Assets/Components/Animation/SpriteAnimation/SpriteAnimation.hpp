//
// Created by kiwi on 04/10/22.
//

#ifndef RTYPE_SPRITEANIMATION_HPP
#define RTYPE_SPRITEANIMATION_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace KapEngine {
    namespace RType {

        class SpriteAnimation : public Animation {
            public:
                SpriteAnimation(std::shared_ptr<GameObject> gameObject);
                SpriteAnimation(std::shared_ptr<GameObject> gameObject, int nbAnimation, Tools::Rectangle rect, int64_t const& time);
                ~SpriteAnimation() = default;

                void onPlay() override;
                void onUpdateAnim() override;
                void onResetAnim() override;

                void setNbAnimations(int nbAnimations);
                void setRect(Tools::Rectangle rect);

            protected:
            private:
                // Variables
                    int _nbAnimation = 0;
                    Tools::Rectangle _rect;

                // Functions
                void init(std::shared_ptr<GameObject> gameObject);
                UI::Image &getImage();
        };

    } // KapEngine
} // RType

#endif //RTYPE_SPRITEANIMATION_HPP

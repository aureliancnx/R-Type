/*
** EPITECH PROJECT, 2022
** RType
** File description:
** SpriteAnimation
*/

#ifndef SPRITEANIMATION_HPP_
#define SPRITEANIMATION_HPP_

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {
    class SpriteAnimation : public KapEngine::Animation {
        public:
            SpriteAnimation(std::shared_ptr<KapEngine::GameObject> gameObject);
            SpriteAnimation(std::shared_ptr<KapEngine::GameObject> gameObject, int nbAnimation, KapEngine::Tools::Rectangle rect, int64_t const& time);
            ~SpriteAnimation() = default;

            void onPlay() override;
            void onUpdateAnim() override;
            void onResetAnim() override;
            void setNbAnimations(int nbAnimations);
            void setRect(KapEngine::Tools::Rectangle rect);
        protected:
        private:
            // Variables
                int _nbAnimation = 0;
                KapEngine::Tools::Rectangle _rect;
            // Functions
            void init(std::shared_ptr<KapEngine::GameObject> gameObject);
            KapEngine::UI::Image &getImage();
    };
} // RType

#endif /* !SPRITEANIMATION_HPP_ */

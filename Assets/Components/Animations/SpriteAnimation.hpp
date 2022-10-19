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

namespace RType
{
    class SpriteAnimation : public KapEngine::Animation
    {
      public:
        SpriteAnimation(std::shared_ptr<KapEngine::GameObject> gameObject);
        SpriteAnimation(std::shared_ptr<KapEngine::GameObject> gameObject, int nbAnimation, KapEngine::Tools::Rectangle rect,
                        int64_t const &time);
        ~SpriteAnimation() = default;

        void onPlay() override;
        void onUpdateAnim() override;
        void onResetAnim() override;
        void setNbAnimations(int nbAnimations);
        void setRect(KapEngine::Tools::Rectangle rect);

        /**
         * @brief this function must be call after all setter functions
         * it gonne calcul all anims to do
         * @param b
         */
        void bouncingVersion(bool bounce) {
            if (bounce && !_bounce)
                _nbAnimation *= 2;
            if (!bounce && _bounce)
                _nbAnimation /= 2;
            _bounce = bounce;
        }

        void reverseAnim(bool reverse) {
            _reverse = reverse;
        }

      protected:
      private:
        // Variables
        int _nbAnimation = 0;
        bool _bounce = false;
        bool _reverse = false;
        KapEngine::Tools::Rectangle _rect;
        // Functions
        void init(std::shared_ptr<KapEngine::GameObject> gameObject);
        KapEngine::UI::Image &getImage();
    };
} // namespace RType

#endif /* !SPRITEANIMATION_HPP_ */

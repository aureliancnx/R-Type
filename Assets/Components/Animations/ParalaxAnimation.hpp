/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ParalaxAnimation.hpp
*/

#ifndef R_TYPE_PARALAXANIMATION_HPP
#define R_TYPE_PARALAXANIMATION_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {

    class ParalaxAnimation : public KapEngine::Animation {
      public:
        ParalaxAnimation(std::shared_ptr<KapEngine::GameObject> canvas);
        ParalaxAnimation(std::shared_ptr<KapEngine::GameObject> canvas, float speed, int width);
        ~ParalaxAnimation() = default;

        void onPlay() override;
        void onUpdateAnim() override;
        void onResetAnim() override;

        void setSpeed(float speed);
        void setWidth(int width);

      private:
        float _speed;
        int _width;
    };

} // namespace RType

#endif // R_TYPE_PARALAXANIMATION_HPP

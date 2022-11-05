/*
** EPITECH PROJECT, 2022
** RType
** File description:
** HowToPlayAnimation
*/

#ifndef HOWTOPLAYANIMATION_HPP_
#define HOWTOPLAYANIMATION_HPP_

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"
#include "Keys/ChangeKey.hpp"
#include <unordered_map>

namespace RType {
    class HowToPlayAnimation : public KapEngine::Animation {
      public:
        HowToPlayAnimation(std::shared_ptr<KapEngine::GameObject> gameObject);
        ~HowToPlayAnimation() = default;

        void onResetAnim() override;
        void setRect(std::string name, KapEngine::Tools::Rectangle rect);
        KapEngine::Tools::Rectangle getRect(std::string name);

        void onFixedUpdate() override;

      private:
        // Variables
        std::unordered_map<std::string, int> _nbAnimation;
        std::unordered_map<std::string, KapEngine::Tools::Rectangle> _rect;
        std::unordered_map<std::string, std::shared_ptr<KapEngine::GameObject>> _allGameObject;
        std::shared_ptr<KapEngine::GameObject> _gameObject;
        float _speed = 0.1f;
        bool _invert = false;
        // Functions
        void init(std::shared_ptr<KapEngine::GameObject> gameObject);
        KapEngine::UI::Image& getImage(std::string name);
    };
} // namespace RType

#endif /* !HOWTOPLAYANIMATION_HPP_ */
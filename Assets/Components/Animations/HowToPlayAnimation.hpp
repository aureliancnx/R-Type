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
#include "SpriteAnimation.hpp"
#include <unordered_map>

namespace RType {
    class HowToPlayAnimation : public KapEngine::Animation {
      public:
        HowToPlayAnimation(std::string name, std::shared_ptr<KapEngine::GameObject> gameObject);
        ~HowToPlayAnimation() = default;

        void onFixedUpdate() override;
        void onResetAnim() override;
        void setNbAnimations(std::string name, int nb);
        void setResetPosition(std::string name, KapEngine::Tools::Vector3 position);
        void setRect(std::string name, KapEngine::Tools::Rectangle rect);
        KapEngine::Tools::Rectangle getRect(std::string name);
        void addSpriteAnimation(std::string name, std::shared_ptr<KapEngine::GameObject> gameObject);

      private:
        // Variables
        std::unordered_map<std::string, int> _nbAnimation;
        std::unordered_map<std::string, KapEngine::Tools::Rectangle> _rect;
        std::unordered_map<std::string, KapEngine::Tools::Vector3> _allGoResetPosition;
        std::unordered_map<std::string, std::shared_ptr<KapEngine::GameObject>> _allGameObject;
        float _speed = 0.1f;
        bool _boubouleInvert = false;
        bool _bouboule2Invert = false;
        bool _shipInvert = false;
        bool _bulletReset = false;

        int _nbShoot = 0;
        bool _canShoot = true;
        bool _canShoot2 = false;
        int _nbInvert = 0;
        bool _gameOver = false;
        // Functions
        void init(std::shared_ptr<KapEngine::GameObject> gameObject);
        KapEngine::UI::Image& getImage(std::string name);
        SpriteAnimation& getSpriteAnimation(std::string name);
        KapEngine::Tools::Vector3 getResetPosition(std::string name);
        std::shared_ptr<KapEngine::GameObject>& getGameObject(std::string name);

        void moveBouboule();
        void moveBouboule2();
        void moveShip();
        void moveBullet();
    };
} // namespace RType

#endif /* !HOWTOPLAYANIMATION_HPP_ */
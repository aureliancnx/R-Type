//
// Created by kiwi on 03/10/22.
//

#include "Shoot.hpp"

namespace KapEngine {
    namespace RType {

        Shoot::Shoot(std::shared_ptr<GameObject> gameObject) : Component(gameObject, "Shoot") {
            init(gameObject);
        }

        void Shoot::init(std::shared_ptr<GameObject> gameObject) {
            addRequireComponent("Image");

            auto img = std::make_shared<UI::Image>(gameObject);
            img->setPathSprite("Assets/Textures/shoot.png");
            img->setRectangle({0.f, 0.f, 19, 6});

            gameObject->addComponent(img);

            try {
                Transform &tr = (Transform &)gameObject->getTransform();
                tr.setScale({(19 * 4), (6 * 4)});
            } catch (...) {}
        }

        void Shoot::onFixedUpdate() {

            Tools::Vector3 cPos = getTransform().getLocalPosition();

            _pos.setX((_pos.getX() + 0.5f));

            cPos += _pos;

            getTransform().setPosition(cPos);

            if (cPos.getX() >= getGameObject().getEngine().getScreenSize().getX()) {
                getGameObject().destroy();
                return;
            }
        }

        void Shoot::animation() {
            auto gameObject = getGameObject().getScene().getObject(getGameObject().getId());
            auto animator = std::make_shared<Animator>(gameObject);
            gameObject->addComponent(animator);

            Time::ETime duration;
            duration.setSeconds(.1f);

            auto shootAnimation = std::make_shared<SpriteAnimation>(gameObject);
            shootAnimation->setTiming(duration);
            shootAnimation->loop(true);
            shootAnimation->setRect({0, 0, 19, 6});
            shootAnimation->setNbAnimations(2);

            gameObject->addComponent(shootAnimation);

            animator->addAnim(shootAnimation, "Shoot");

            animator->addLink("Shoot", "Shoot", "To shoot");
        }
    } // KapEngine0
} // RType
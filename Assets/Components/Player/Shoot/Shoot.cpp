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
                tr.setScale({(19 * 2), (6 * 2)});
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

            Debug::warning(cPos.to_string() + ", " + getGameObject().getEngine().getScreenSize().to_string());

        }

        void Shoot::animation() {
//            auto animator = std::shared_ptr<Animator>(getGameObject());
        }
    } // KapEngine
} // RType
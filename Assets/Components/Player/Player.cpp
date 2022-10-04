//
// Created by kiwi on 03/10/22.
//

#include "Player.hpp"

namespace KapEngine {
    namespace RType {
        Player::Player(std::shared_ptr<GameObject> gameObject) : Component(gameObject, "Player") {
            init(gameObject);
        }

        Player::Player(std::shared_ptr<GameObject> gameObject, std::string path) : Component(gameObject, "Player") {
            _path = path;
            init(gameObject);
        }

        void Player::init(std::shared_ptr<GameObject> gameObject) {
            addRequireComponent("Image");

            auto ship = std::make_shared<UI::Image>(gameObject);
            ship->setRectangle({0, 0, 33.3125, 36});
            if (!_path.size() == 0)
                ship->setPathSprite(_path);

            try {
                Transform &tr = (Transform &)gameObject->getTransform();
                tr.setScale({33.3125, 36});
                tr.setPosition(_lastPos);
            } catch (...) {}

            gameObject->addComponent(ship);
        }

        void Player::onUpdate() {
            Tools::Vector3 pos;

            pos.setX(getInput().getAxis("Horizontal"));
            pos.setY(getInput().getAxis("Vertical"));

            Tools::Vector3 cPos = getTransform().getLocalPosition();

            cPos += pos;

            if (cPos.getX() == 0 || cPos.getX() == getGameObject().getEngine().getScreenSize().getX() - 33 ||
                cPos.getY() == 0 || cPos.getY() == getGameObject().getEngine().getScreenSize().getY() - 36 )
                return;

            getTransform().setPosition(cPos);

            if (getInput().getKey(Events::Key::SPACE))
                shoot(cPos);
        }

        void Player::onDestroy() {
            DEBUG_LOG("On Destroy!");
        }

        void Player::onGameQuit() {
            DEBUG_LOG("On Game Quit!");
        }

        UI::Image &Player::getImage() {
            try {
                return (UI::Image &)getGameObject().getComponent("Image");
            } catch (...) {
                Debug::error("Failed to get image of button " + getGameObject().getName());
            }
            throw Errors::ComponentError("Failed to get image of button");
        }

        void Player::setPath(const std::string &path) {
            getImage().setPathSprite(path);
        }

    } // KapEngine
} // RType
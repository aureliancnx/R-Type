/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Player.cpp
*/

#include "Player.hpp"

namespace KapEngine {
    namespace RType {
        Player::Player(std::shared_ptr<GameObject> gameObject) : Component(gameObject, "Player") {
            init(gameObject);
        }

        Player::Player(std::shared_ptr<GameObject> gameObject, std::string const &path) : Component(gameObject, "Player") {
            _path = path;
            init(gameObject);
        }

        void Player::init(std::shared_ptr<GameObject> gameObject) {
            addRequireComponent("Image");

            auto ship = std::make_shared<UI::Image>(gameObject);
            ship->setRectangle({0, 0, 26, 21});
            if (!_path.empty())
                ship->setPathSprite(_path);
            else
                ship->setPathSprite("Assets/Textures/Ship/space_ship.png");

            try {
                Transform &transform = getTransform();
                transform.setScale({(26 * 2), (21 * 2)});
                transform.setPosition(_lastPos);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }

            gameObject->addComponent(ship);
        }

        void Player::onUpdate() {
            Tools::Vector3 pos;
            Tools::Vector3 cPos = getTransform().getLocalPosition();

            pos.setX(getInput().getAxis("Horizontal"));
            pos.setY(getInput().getAxis("Vertical"));

            if (pos.getX() != 0 || pos.getY() != 0) {
                pos = pos * 3;
                getTransform().setPosition(cPos + pos);
                _lastPos = getTransform().getLocalPosition();
            } else {
                getTransform().setPosition(_lastPos);
            }
        }

        void Player::setPath(const std::string &path) {
           getImage().setPathSprite(path);
        }

        UI::Image &Player::getImage() {
            try {
                return (UI::Image &)getGameObject().getComponent("Image");
            } catch (...) {
                Debug::error("Failed to get image of button " + getGameObject().getName());
            }
            throw Errors::ComponentError("Failed to get image of button");
        }
    } // KapEngine
} // RType
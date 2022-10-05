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
            playSound("Assets/music/exports/space-asteroids.wav");

            auto ship = std::make_shared<UI::Image>(gameObject);
            ship->setRectangle({0, 0, 26, 21});
            if (!_path.size() == 0)
                ship->setPathSprite(_path);

            try {
                Transform &tr = (Transform &)gameObject->getTransform();
                tr.setScale({(26 * 2), (21 * 2)});
                tr.setPosition(_lastPos);
            } catch (...) {}

            gameObject->addComponent(ship);
        }

        void Player::onUpdate() {
            Tools::Vector3 pos;

            pos.setX(getInput().getAxis("Horizontal"));
            pos.setY(getInput().getAxis("Vertical"));

            Tools::Vector3 cPos = getTransform().getLocalPosition();

            cPos += (pos * 3);

//            if (cPos.getX() == 0 || cPos.getX() == getGameObject().getEngine().getScreenSize().getX() ||
//                cPos.getY() == 0 || cPos.getY() == getGameObject().getEngine().getScreenSize().getY())
//                return;

            getTransform().setPosition(cPos);


            if (_lastPos != pos) {
                auto animator = getGameObject().getComponent<Animator>();

                if (getInput().getKeyDown(Events::Key::UP))
                    animator.setTrigger("Stay to Up");
                else 
                if (getInput().getKeyUp(Events::Key::UP))
                    animator.setTrigger("Up to Stay");

                if (getInput().getKeyDown(Events::Key::DOWN))
                    animator.setTrigger("Stay to Down");
                if (getInput().getKeyUp(Events::Key::DOWN))
                    animator.setTrigger("Down to Stay");
//
//                if (pos.getY() > 0.f) {
//                    animator.setTrigger("Stay to Up");
//                } else if (pos.getY() < 0.f) {
//                    animator.setTrigger("Stay to Down");
//                } else {
//                    if (animator.getAnimNode())
//                        animator.setTrigger("Up to Stay");
//                    animator.setTrigger("Down to Stay");
//                }
            }

            if (getInput().getKeyDown(Events::Key::SPACE))
                shoot(pos);

            _lastPos = pos;


//            if (pos.getY() < 0)
//                getGameObject().getComponent<Animator>().setTrigger("UnPress key up");
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

        void Player::shoot(Tools::Vector3 pos) {
            auto &scene = getGameObject().getScene();
//            scene.getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/SoundFX/shot1.wav");
            playSound("Assets/SoundFX/shot1.wav");
            auto shoot = scene.createGameObject("Shoot");

            auto compShoot = std::make_shared<Shoot>(shoot);
            compShoot->animation();

            shoot->addComponent(compShoot);

            try {
                auto &tr = shoot->getComponent<Transform>();
                tr.setPosition(getTransform().getLocalPosition());
                tr.setParent(getTransform().getParentId());
            } catch (...) {}

            scene.dump();
        }

        void Player::playSound(std::string const &path) {
           getGameObject().getEngine().getGraphicalLibManager()->getCurrentLib()->playSound(path);
        }

    } // KapEngine
} // RType
//
// Created by kiwi on 03/10/22.
//

#include "Shoot.hpp"

namespace KapEngine {
    namespace RType {

        Shoot::Shoot(std::shared_ptr<GameObject> gameObject) : Component(gameObject, "Shoot") {
            init(gameObject);
        }

        Shoot::Shoot(std::shared_ptr<GameObject> gameObject, const std::string &path, const std::string &sound) : Component(gameObject, "Shoot") {
            _path = path;
            _sound = sound;
            init(gameObject);
        }

        void Shoot::init(std::shared_ptr<GameObject> gameObject) {
            addRequireComponent("Image");
            playSound(_sound);

            auto img = std::make_shared<UI::Image>(gameObject);
            if (!_path.size() == 0)
                img->setPathSprite(_path);
            else
                img->setPathSprite("Assets/Textures/shoot.png");

                img->setRectangle({0.f, 0.f, 19, 6});

            gameObject->addComponent(img);

            try {
                Transform &tr = (Transform &)gameObject->getTransform();
                tr.setScale({(19 * 2), (6 * 2)});
            } catch (...) {}
        }

        void Shoot::onFixedUpdate() {

            _pos.setX((_pos.getX() + _direction.getX()));
            _pos.setY((_pos.getY() + _direction.getY()));

            _cPos += _pos;

            getTransform().setPosition(_cPos);

            Tools::Vector2 screenSize = getGameObject().getEngine().getScreenSize();
            if (_cPos.getX() >= screenSize.getX() || _cPos.getY() >= screenSize.getY()) {
                getGameObject().destroy();
                return;
            }
        }

        void Shoot::setDirection(Tools::Vector2 direction) {
            _direction = direction;
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

        void Shoot::setPos(Tools::Vector3 pos) {
            _cPos = pos;
        }

        void Shoot::setPath(std::string const &path) {
            getImage().setPathSprite(path);
        }

        void Shoot::setSound(const std::string &path) {
            _sound = path;
        }

        UI::Image &Shoot::getImage() {
            try {
                return (UI::Image &)getGameObject().getComponent("Image");
            } catch (...) {
                Debug::error("Failed to get image of button " + getGameObject().getName());
            }
            throw Errors::ComponentError("Failed to get image of button");
        }

        void Shoot::playSound(std::string const &string) {
            if (_sound.size())
                getGameObject().getEngine().getGraphicalLibManager()->getCurrentLib()->playSound(_sound);
            else
                getGameObject().getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/SoundFX/shot1.wav");
        }
    } // KapEngine0
} // RType
/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Shoot.cpp
*/

#include "Shoot.hpp"

namespace KapEngine {
    namespace RType {

        Shoot::Shoot(std::shared_ptr<GameObject> gameObject) : Component(gameObject, "Shoot") {
            init(gameObject);
        }

        Shoot::Shoot(std::shared_ptr<GameObject> gameObject, const std::string &path, Tools::Rectangle rect) : Component(gameObject, "Shoot") {
            _path = path;
            _rect = rect;
            init(gameObject);
        }

        void Shoot::init(std::shared_ptr<GameObject> gameObject) {
            addRequireComponent("Image");

            auto shoot = std::make_shared<UI::Image>(gameObject);
            if (!_path.empty())
                shoot->setPathSprite(_path);
            else
                shoot->setPathSprite("Assets/Textures/Shoot/shoot.png");

            if (_rect.getWidth() != 0 && _rect.getHeigth() != 0)
                shoot->setRectangle(_rect);
            else
                shoot->setRectangle({0, 0, 19, 6});

            gameObject->addComponent(shoot);

            try {
                Transform &transform = getTransform();
                transform.setScale({(19 * 2), (6 * 2)});
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void Shoot::onFixedUpdate() {
            _pos.setX((_pos.getX() + _direction.getX()));
            _pos.setY((_pos.getY() + _direction.getY()));

            _cPos += _pos;

            getTransform().setPosition(_cPos);

            Tools::Vector2 screenSize = getGameObject().getEngine().getScreenSize();
            if (_cPos.getX() < 0 || _cPos.getX() > screenSize.getX() || _cPos.getY() < 0 || _cPos.getY() > screenSize.getY())
                getGameObject().destroy();
        }

        void Shoot::setPath(const std::string &path) {
            getImage().setPathSprite(path);
        }

        void Shoot::setRectangle(const Tools::Rectangle &rect) {
            getImage().setRectangle(rect);
        }

        void Shoot::setDirection(const Tools::Vector2 &direction) {
            _direction = direction;
        }

        void Shoot::setPos(const Tools::Vector2 &pos) {
            _pos = pos;
        }

        UI::Image &Shoot::getImage() {
            try {
                return getGameObject().getComponent<UI::Image>("Image");
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
            throw Errors::ComponentError("Failed to get Image component");
        }

        void Shoot::shoot(const Tools::Vector2 &direction, const Tools::Vector2 &pos) {
//            auto &scene = getGameObject().getScene();
//            auto shoot = scene.createGameObject("Shoot");
//            auto compShoot = std::make_shared<Shoot>(shoot);
//            compShoot->setPos({pos.getX() + 50, pos.getY(), pos.getZ()});
//            compShoot->setPath("Assets/Textures/shoot.png");
//            compShoot->setDirection(direction);
//
//            shoot->addComponent(compShoot);
//
//            try {
//                auto &tr = shoot->getComponent<Transform>();
//                tr.setPosition(getTransform().getLocalPosition());
//                tr.setParent(getTransform().getParentId());
//            } catch (...) {}
//
//            scene.dump();
        }

    } // KapEngine
} // RType
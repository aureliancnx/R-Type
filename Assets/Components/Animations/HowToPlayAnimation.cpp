/*
** EPITECH PROJECT, 2022
** Rytpe
** File description:
** HowToPlayAnimation
*/

#include "HowToPlayAnimation.hpp"

using namespace KapEngine;

namespace RType {

    HowToPlayAnimation::HowToPlayAnimation(std::string name, std::shared_ptr<KapEngine::GameObject> gameObject) : Animation(gameObject) {
        init(gameObject);
    }

    void HowToPlayAnimation::init(std::shared_ptr<GameObject> gameObject) { addRequireComponent("Image"); }

    void HowToPlayAnimation::onFixedUpdate() {
        moveShip();
        moveBullet();
        moveBouboule();
        moveBouboule2();
        moveExplosion();
    }

    void HowToPlayAnimation::onResetAnim() {
        onResetStates();
        onResetRect();
        onResetPosition();
        onResetActive();
    }

    void HowToPlayAnimation::onResetStates() {
        _boubouleInvert = false;
        _bouboule2Invert = false;
        _shipInvert = false;
        _explosionInvert = false;
        _explosionInvert2 = false;
        _bulletReset = false;
        _canShoot = true;
        _nbShoot = 0;
    }

    void HowToPlayAnimation::onResetRect() {
        getImage("Ship").setRectangle(getRect("Ship"));
        getImage("Bullet").setRectangle(getRect("Bullet"));
        getImage("Bouboule").setRectangle(getRect("Bouboule"));
        getImage("Bouboule2").setRectangle(getRect("Bouboule2"));
        getImage("Explosion").setRectangle(getRect("Explosion"));
    }

    void HowToPlayAnimation::onResetPosition() {
        {
            auto &transform = getImage("Ship").getTransform();
            transform.setPosition(getResetPosition("Ship"));
        }

        {
            auto &transform = getImage("Bullet").getTransform();
            transform.setPosition(getResetPosition("Bullet"));
        }

        {
            auto &transform = getImage("Bouboule").getTransform();
            transform.setPosition(getResetPosition("Bouboule"));
        }

        {
            auto &transform = getImage("Bouboule2").getTransform();
            transform.setPosition(getResetPosition("Bouboule2"));
        }

        {
            auto &transform = getImage("Explosion").getTransform();
            transform.setPosition(getResetPosition("Explosion"));
        }
    }

    void HowToPlayAnimation::onResetActive() {
        getGameObject("Ship")->setActive(true);
        getGameObject("Bouboule")->setActive(true);
        getGameObject("Bouboule2")->setActive(true);
        getGameObject("Bullet")->setActive(false);
        getGameObject("Explosion")->setActive(false);
    }

    void HowToPlayAnimation::moveBouboule2() {
        if (getGameObject("Bouboule2")->isActive() == false)
            return;

        auto &transform = getImage("Bouboule2").getTransform();
        auto pos_Y = transform.getWorldPosition().getY();
        auto pos_X = transform.getWorldPosition().getX();

        if (_explosionInvert == false && getGameObject("Explosion")->isActive() == true) {
            getGameObject("Bouboule2")->setActive(false);
            return;
        }

        if (_bouboule2Invert) {
            if (pos_X >= 490 && pos_Y > 200)
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(3.5f, -3.5f, 0));
            else
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-3.5f, -3.5f, 0));
        } else {
            if (pos_X >= 490 && pos_Y < 200)
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(3.5f, 3.5f, 0));
            else
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-3.5f, 3.5f, 0));
        }

        if (pos_Y > 300)
            _bouboule2Invert = true;
        else if (pos_Y < 70)
            _bouboule2Invert = false;
    }

    void HowToPlayAnimation::moveBouboule() {
        if (getGameObject("Bouboule")->isActive() == false)
            return;

        auto &transform = getImage("Bouboule").getTransform();
        auto posY = transform.getWorldPosition().getY();
        auto posX = transform.getWorldPosition().getX();

        if (_nbShoot == 2 && _explosionInvert2 == false && getGameObject("Explosion")->isActive() == true) {
            onResetAnim();
            return;
        }

        if (_boubouleInvert) {
            if (posX > 500 && posY > 200)
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-3.24f, -3.24f, 0));
            else
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(3.24f, -3.24f, 0));
        } else {
            if (posX > 500 && posY < 200)
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-3.24f, 3.24f, 0));
            else
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(3.24f, 3.24f, 0));
        }

        if (posY > 300)
            _boubouleInvert = true;
        else if (posY < 70)
            _boubouleInvert = false;
    }

    void HowToPlayAnimation::moveShip() {
        auto &transform = getImage("Ship").getTransform();
        auto posY = transform.getWorldPosition().getY();

        if (_shipInvert)
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, -4.0f, 0));
        else
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, 4.0f, 0));

        if (_shipAnimation == false && posY > 300) {
            _shipInvert = true;
            _shipAnimation = true;
            _allGameObject.at("Ship")->getComponent<KapEngine::Animator>().setTrigger("DownToUp");
        } else if (_shipAnimation == true && posY < 70) {
            _shipInvert = false;
            _shipAnimation = false;
            _allGameObject.at("Ship")->getComponent<KapEngine::Animator>().setTrigger("UpToDown");
        }
    }

    void HowToPlayAnimation::moveBullet() {
        auto &transform = getImage("Bullet").getTransform();
        auto shipPosY = getImage("Ship").getTransform().getWorldPosition().getY();

        if (getGameObject("Bullet")->isActive() == false && shipPosY == 266) {
            if (_nbShoot == 0 && _canShoot && _explosionInvert2 == false) {
                _explosionInvert = true;
                getGameObject("Bullet")->setActive(true);
                transform.setPosition(getResetPosition("Bullet"));
                _nbShoot++;
                _canShoot = false;
            }
        } else if (getGameObject("Bullet")->isActive() == false && shipPosY == 170) {
            if (_nbShoot == 1 && _canShoot && _explosionInvert == false) {
                _explosionInvert = false;
                _explosionInvert2 = true;
                getGameObject("Explosion")->setActive(false);
                getGameObject("Bullet")->setActive(true);
                transform.setPosition(KapEngine::Tools::Vector3(380, 166, 0));
                _nbShoot++;
                _canShoot = false;
            }
        }
        if (getGameObject("Bullet")->isActive() == false)
            return;

        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(6.0f, 0, 0));

        if (!_explosionInvert && transform.getWorldPosition().getX() > 600) {
            getGameObject("Bullet")->setActive(false);
            _explosionInvert = false;
            _canShoot = true;
        } else if (_nbShoot == 2 && !_explosionInvert2 && transform.getWorldPosition().getX() > 530) {
            getGameObject("Bullet")->setActive(false);
        }
    }

    void HowToPlayAnimation::moveExplosion() {
        auto &transform = getImage("Explosion").getTransform();
        if (_explosionInvert && getImage("Bullet").getTransform().getWorldPosition().getX() >= 588.0f) {
            getGameObject("Explosion")->setActive(true);
            transform.setPosition(getResetPosition("Explosion"));
            _explosionInvert = false;
        } else if (_explosionInvert2 && getImage("Bullet").getTransform().getWorldPosition().getX() >= 530.0f) {
            getGameObject("Explosion")->setActive(true);
            transform.setPosition(KapEngine::Tools::Vector3(520.0f, 150.0f, 0));
            _explosionInvert2 = false;
        }
    }

    void HowToPlayAnimation::setNbAnimations(std::string name, int nb) {
        _allGameObject.at(name)->getComponent<SpriteAnimation>().setNbAnimations(nb);
    }

    void HowToPlayAnimation::addSpriteAnimation(std::string name, std::shared_ptr<KapEngine::GameObject> gameObject) {
        _allGameObject.insert(std::make_pair(name, gameObject));
    }

    void HowToPlayAnimation::setRect(std::string name, Tools::Rectangle rect) {
        if (_rect.find(name) == _rect.end())
            _rect.insert(std::make_pair(name, rect));
        else
            _rect.at(name) = rect;
    }

    void HowToPlayAnimation::setResetPosition(std::string name, KapEngine::Tools::Vector3 position) {
        if (_allGoResetPosition.find(name) == _allGoResetPosition.end())
            _allGoResetPosition.insert(std::make_pair(name, position));
        else
            _allGoResetPosition.at(name) = position;
    }

    KapEngine::Tools::Vector3 HowToPlayAnimation::getResetPosition(std::string name) {
        try {
            return (_allGoResetPosition.at(name));
        } catch (...) { Debug::error("Failed to get position of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get position of ");
    }

    KapEngine::Tools::Rectangle HowToPlayAnimation::getRect(std::string name) {
        try {
            return (_rect.at(name));
        } catch (...) { Debug::error("Failed to get rect of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get rect of ");
    }

    UI::Image &HowToPlayAnimation::getImage(std::string name) {
        try {
            return _allGameObject.at(name)->getComponent<UI::Image>();
        } catch (...) { Debug::error("Failed to get image of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get image of ");
    }

    SpriteAnimation &HowToPlayAnimation::getSpriteAnimation(std::string name) {
        try {
            return _allGameObject.at(name)->getComponent<SpriteAnimation>();
        } catch (...) { Debug::error("Failed to get SpriteAnimation of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get SpriteAnimation of ");
    }

    std::shared_ptr<KapEngine::GameObject> &HowToPlayAnimation::getGameObject(std::string name) {
        try {
            return _allGameObject.at(name);
        } catch (...) { Debug::error("Failed to get gameObject of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get gameObject of ");
    }

} // namespace RType
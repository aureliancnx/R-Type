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
        // _nbAnimation.insert(std::make_pair<std::string, int>("Ship", 5));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Bullet", 2));
        // _nbAnimation.insert(std::make_pair<std::string, int>("bouboule", 12));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Explosion", 6));
        // setTiming(3);
    }

    void HowToPlayAnimation::init(std::shared_ptr<GameObject> gameObject) { addRequireComponent("Image"); }

    void HowToPlayAnimation::moveBouboule2() {
        auto& transform = getImage("Bouboule2").getTransform();
        auto pos_Y = transform.getWorldPosition().getY();
        auto pos_X  = transform.getWorldPosition().getX();

        if (_bouboule2Invert) {
            if (pos_X >= 490 && pos_Y > 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, -5.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-5.0f, -5.0f, 0));
            }
        } else {
            if (pos_X >= 490 && pos_Y < 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, 5.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-5.0f, 5.0f, 0)); 
            }              
        }

        if (pos_Y > 350) {
            _bouboule2Invert = true;
        } else if (pos_Y < 50) {
            _bouboule2Invert = false;
        }
    }

    void HowToPlayAnimation::moveBouboule() {
        auto& transform = getImage("Bouboule").getTransform();
        auto pos_Y = transform.getWorldPosition().getY();
        auto pos_X  = transform.getWorldPosition().getX();

        if (_boubouleInvert) {
            if (pos_X > 500 && pos_Y > 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-5.0f, -5.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, -5.0f, 0));
            }
        } else {
            if (pos_X > 500 && pos_Y < 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-5.0f, 5.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, 5.0f, 0)); 
            }              
        }

        if (pos_Y > 350) {
            _boubouleInvert = true;
        } else if (pos_Y < 50) {
            _boubouleInvert = false;
        }
    }

    void HowToPlayAnimation::moveShip() {
        auto& transform = getImage("Ship").getTransform();

        if (_shipInvert) {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, -5.0f, 0));
        } else {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, 5.0f, 0));
        }

        if (transform.getWorldPosition().getY() > 300) {
            _shipInvert = true;
            _allGameObject.at("Ship")->getComponent<KapEngine::Animator>().setTrigger("DownToIdle");
            _allGameObject.at("Ship")->getComponent<KapEngine::Animator>().setTrigger("IdleToUp");
        } else if (transform.getWorldPosition().getY() < 70) {
            _shipInvert = false;
            _allGameObject.at("Ship")->getComponent<KapEngine::Animator>().setTrigger("UpToIdle");
            _allGameObject.at("Ship")->getComponent<KapEngine::Animator>().setTrigger("IdleToDown");
        }
    }

    void HowToPlayAnimation::moveBullet() {
        auto& transform = getImage("Bullet").getTransform();

        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, 0, 0));

        if (transform.getWorldPosition().getX() < 500) {
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("BigBulletToLittleBullet");
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("LittleBulletToLittleBullet");
        } else {
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("LittleBulletToBigBullet");
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("BigBulletToBigBullet");
        }

        if (transform.getWorldPosition().getX() > 600) {
            _bulletReset = true;
        }
    }

    void HowToPlayAnimation::onFixedUpdate() {
        // KAP_DEBUG_WARNING("X : " + std::to_string(getImage("Bullet").getTransform().getWorldPosition().getX()) + " Y : " + std::to_string(getImage("Bullet").getTransform().getWorldPosition().getY()));
        moveBouboule();
        moveBouboule2();
        moveShip();
        //ajouter un temps avant d'afficher le bullet
        if (!_bulletReset) {
            moveBullet();
        } else {
            onResetAnim();
        }
    }

    void HowToPlayAnimation::onResetAnim() {
        // getImage("Ship").setRectangle(getRect("Ship"));
        // getImage("Bullet").setRectangle(getRect("Bullet"));
        // getImage("Bouboule").setRectangle(getRect("Bouboule"));
        // getImage("Bouboule2").setRectangle(getRect("Bouboule2"));
        // getImage("explosion").setRectangle({0, 0, 0, 0});

        auto& transform = getImage("Bullet").getTransform();
        transform.setPosition(getResetPosition("Bullet"));
        _bulletReset = false;
    }

    void HowToPlayAnimation::setNbAnimations(std::string name, int nb) { _allGameObject.at(name)->getComponent<SpriteAnimation>().setNbAnimations(nb); }

    void HowToPlayAnimation::addSpriteAnimation(std::string name, std::shared_ptr<KapEngine::GameObject> gameObject) { _allGameObject.insert(std::make_pair(name, gameObject)); }

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

    UI::Image& HowToPlayAnimation::getImage(std::string name) {
        try {
            return _allGameObject.at(name)->getComponent<UI::Image>();
        } catch (...) { Debug::error("Failed to get image of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get image of ");
    }

   SpriteAnimation& HowToPlayAnimation::getSpriteAnimation(std::string name) {
        try {
            return _allGameObject.at(name)->getComponent<SpriteAnimation>();
        } catch (...) { Debug::error("Failed to get SpriteAnimation of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get SpriteAnimation of ");
    }

} // namespace RType
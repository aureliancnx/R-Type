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
        moveBouboule();
        moveBouboule2();
        moveShip();
        moveBullet();
    }

    void HowToPlayAnimation::onResetAnim() {
        // getImage("Ship").setRectangle(getRect("Ship"));
        // getImage("Bullet").setRectangle(getRect("Bullet"));
        // getImage("Bouboule").setRectangle(getRect("Bouboule"));
        // getImage("Bouboule2").setRectangle(getRect("Bouboule2"));
        // getImage("Explosion").setRectangle(getRect("Explosion"));

        // auto& transform = getImage("Ship").getTransform();
        // transform.setPosition(getResetPosition("Ship"));

        // auto& transform = getImage("Bullet").getTransform();
        // transform.setPosition(getResetPosition("Bullet"));

        // auto& transform = getImage("Bouboule").getTransform();
        // transform.setPosition(getResetPosition("Bouboule"));

        // auto& transform = getImage("Bouboule2").getTransform();
        // transform.setPosition(getResetPosition("Bouboule2"));

        // auto& transform = getImage("Explosion").getTransform();
        // transform.setPosition(getResetPosition("Explosion"));
    }

    void HowToPlayAnimation::moveBouboule2() {
        // if (getGameObject("Bouboule2")->isActive() == false)
        //     return;

        auto& transform = getImage("Bouboule2").getTransform();
        // KAP_DEBUG_WARNING(" BOUBOULE 2 X : " + std::to_string(transform.getWorldPosition().getX()) + " Y : " + std::to_string(transform.getWorldPosition().getY()));
        auto pos_Y = transform.getWorldPosition().getY();
        auto pos_X  = transform.getWorldPosition().getX();

        // if (pos_Y == 266.0f) {
        //     getGameObject("Bouboule2")->setActive(false);
        //     return;
        // }

        if (_bouboule2Invert) {
            if (pos_X >= 490 && pos_Y > 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(4.0f, -4.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-4.0f, -4.0f, 0));
            }
        } else {
            if (pos_X >= 490 && pos_Y < 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(4.0f, 4.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-4.0f, 4.0f, 0)); 
            }              
        }
        if (pos_Y > 300) {
            _bouboule2Invert = true;
            _canShoot2 = true;
        } else if (pos_Y < 70) {
            _bouboule2Invert = false;
        }
    }

    void HowToPlayAnimation::moveBouboule() {
        // if (getGameObject("Bouboule")->isActive() == false)
        //     return;

        auto& transform = getImage("Bouboule").getTransform();
        // KAP_DEBUG_WARNING(" BOUBOULE X : " + std::to_string(transform.getWorldPosition().getX()) + " Y : " + std::to_string(transform.getWorldPosition().getY()));
        auto pos_Y = transform.getWorldPosition().getY();
        auto pos_X  = transform.getWorldPosition().getX();

        // if (pos_Y == 266.0f) {
        //     getGameObject("Bouboule")->setActive(false);
        //     return;
        // }

        if (_boubouleInvert) {
            if (pos_X > 500 && pos_Y > 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-4.0f, -4.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(4.0f, -4.0f, 0));
            }
        } else {
            if (pos_X > 500 && pos_Y < 200) {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-4.0f, 4.0f, 0));
            } else {
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(4.0f, 4.0f, 0)); 
            }              
        }

        if (pos_Y > 300) {
            _boubouleInvert = true;
            _canShoot = true;
        } else if (pos_Y < 70) {
            _boubouleInvert = false;
        }
    }

    void HowToPlayAnimation::moveShip() {    
        // if (getGameObject("Ship")->isActive() == false)
        //     return;
        auto& transform = getImage("Ship").getTransform();
        // KAP_DEBUG_WARNING(" SHIP X : " + std::to_string(transform.getWorldPosition().getX()) + " Y : " + std::to_string(transform.getWorldPosition().getY()));

        // if (transform.getWorldPosition().getY() == 266.0f) {
        //     getGameObject("Ship")->setActive(false);
        //     return;
        // }

        if (_shipInvert) {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, -4.0f, 0));
        } else {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, 4.0f, 0));
        }

        if (transform.getWorldPosition().getY() > 300) {
            // KAP_DEBUG_WARNING("X : " + std::to_string(transform.getWorldPosition().getX()) + " Y : " + std::to_string(transform.getWorldPosition().getY()));
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

        if (getGameObject("Bullet")->isActive() == false && getImage("Ship").getTransform().getWorldPosition().getY() == 266) {
            if (_nbShoot % 2 == 0 && _canShoot) {
                getGameObject("Bullet")->setActive(true);
                transform.setPosition(getResetPosition("Bullet"));
                _nbShoot++;
                _canShoot = false;
            }
            
        } else if (getGameObject("Bullet")->isActive() == false && getImage("Ship").getTransform().getWorldPosition().getY() == 166) {
            if (_nbShoot % 2 != 0 && _canShoot) {
                getGameObject("Bullet")->setActive(true);
                transform.setPosition(KapEngine::Tools::Vector3(400, 166, 0));
                _nbShoot++;
                _canShoot = false;
            }
        }
        if (getGameObject("Bullet")->isActive() == false)
            return;

        transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, 0, 0));

        if (transform.getWorldPosition().getX() < 500) {
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("BigBulletToLittleBullet");
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("LittleBulletToLittleBullet");
        } else {
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("LittleBulletToBigBullet");
            _allGameObject.at("Bullet")->getComponent<KapEngine::Animator>().setTrigger("BigBulletToBigBullet");
        }

        if (transform.getWorldPosition().getX() > 600) {
            getGameObject("Bullet")->setActive(false);
            _canShoot = true;
        }
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

    std::shared_ptr<KapEngine::GameObject>& HowToPlayAnimation::getGameObject(std::string name) {
        try {
            return _allGameObject.at(name);
        } catch (...) { Debug::error("Failed to get gameObject of  " + _allGameObject.at(name)->getName()); }
        throw Errors::ComponentError("Failed to get gameObject of ");
    }

} // namespace RType
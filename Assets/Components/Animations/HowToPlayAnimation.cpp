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
        addSpriteAnimation(name, gameObject);
        setRect(name, gameObject->getComponent<UI::Image>().getRectangle());
        // _nbAnimation.insert(std::make_pair<std::string, int>("Ship", 5));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Bullet", 2));
        // _nbAnimation.insert(std::make_pair<std::string, int>("bubulle", 12));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Explosion", 6));
        // setTiming(3);
    }

    void HowToPlayAnimation::init(std::shared_ptr<GameObject> gameObject) { addRequireComponent("Image"); }

    void HowToPlayAnimation::moveEnemy(std::string name)
    {
        auto& transform = getImage(name).getTransform();
        auto pos_Y = transform.getWorldPosition().getY();
        auto pos_X  = transform.getWorldPosition().getX();

        if (_bubulleInvert) {
            if (pos_X > 500 && pos_Y > 200)
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-5.0f, -5.0f, 0));
            else
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, -5.0f, 0));
        } else {
            if (pos_X > 500 && pos_Y < 200)
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(-5.0f, 5.0f, 0));
            else
                transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(5.0f, 5.0f, 0));                
        }

        if (pos_Y > 350) {
            _bubulleInvert = true;
        } else if (pos_Y < 50) {
            _bubulleInvert = false;
        }
    }

    void HowToPlayAnimation::moveShip()
    {
        auto& transform = getImage("ship").getTransform();

        if (_shipInvert) {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, -5.0f, 0));
        } else {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, 5.0f, 0));
        }

        if (transform.getWorldPosition().getY() > 300) {
            _shipInvert = true;
        } else if (transform.getWorldPosition().getY() < 70) {
            _shipInvert = false;
        }
    }

    void HowToPlayAnimation::onFixedUpdate() {
        moveEnemy("bubulle");
        // moveEnemy("bubulle_2");
        moveShip();
    }

    void HowToPlayAnimation::onResetAnim() {
        getImage("ship").setRectangle(getRect("ship"));
        // getImage("bullet").setRectangle({0, 0, 0, 0});
        getImage("bubulle").setRectangle(getRect("bubulle"));
        // getImage("explosion").setRectangle({0, 0, 0, 0});
    }

    void HowToPlayAnimation::setNbAnimations(std::string name, int nb) { _allGameObject.at(name)->getComponent<SpriteAnimation>().setNbAnimations(nb); }

    void HowToPlayAnimation::addSpriteAnimation(std::string name, std::shared_ptr<KapEngine::GameObject> gameObject) { _allGameObject.insert(std::make_pair(name, gameObject)); }

    void HowToPlayAnimation::setRect(std::string name, Tools::Rectangle rect) {
        if (_rect.find(name) == _rect.end())
            _rect.insert(std::make_pair(name, rect));
        else
            _rect.at(name) = rect; 
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
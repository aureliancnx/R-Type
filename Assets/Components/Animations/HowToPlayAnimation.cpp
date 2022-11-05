/*
** EPITECH PROJECT, 2022
** Rytpe
** File description:
** HowToPlayAnimation
*/

#include "HowToPlayAnimation.hpp"

using namespace KapEngine;

namespace RType {
    //TO DO : set les rect
    HowToPlayAnimation::HowToPlayAnimation(std::shared_ptr<KapEngine::GameObject> shipObject) 
        : Animation(shipObject) 
    {
        // _gameObject = gameObject;
        _shipObject = shipObject;
        init(_shipObject);
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Ship", ));
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Bullet", ));
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Bubulle", ));
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Explosion",));
        _nbAnimation.insert(std::make_pair<std::string, int>("Ship", 5));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Bullet", 2));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Bubulle", 12));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Explosion", 6));
        _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Ship", {0, 0, 0, 0}));
        // _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Bullet", {0, 0, 0 , 0}));
        // _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Bubulle", {0, 0, 0, 0}));
        // _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Explosion", {0, 0, 0, 0}));
        setTiming(.4);
    }

    void HowToPlayAnimation::init(std::shared_ptr<GameObject> gameObject) {
        addRequireComponent("Image");
    }

    void HowToPlayAnimation::onPlay() {
        KAP_DEBUG_WARNING("Je start animation");
        getImage("Ship").setRectangle(_rect.at("Ship"));
        //getImage("Bullet").setRectangle(_rect.at("Bullet"));
        //getImage("Bubulle").setRectangle(_rect.at("Bubulle"));
        //getImage("Explosion").setRectangle(_rect.at("Explosion"));
    }

    void HowToPlayAnimation::onUpdateAnim() {
        KAP_DEBUG_WARNING("Animation onUpdate");
        // KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition();
        // float percent = (_nbAnimation.at("Ship") * _currTime) / _timing.asMicroSecond();
        // float percent = _currTime / _timing.asMicroSecond();

        // if (pos.getY() < 0)
        //     pos.setY(0);
        // pos.setY(pos.getY() - 0.1f);
        // getTransform().setPosition(pos);
        //si percent 50% explosion
        // if (crossProduct > _nbAnimation / 2)
        //     goBouncing = true;

        // Tools::Vector2 pos = _rect.at("Ship").getPos();
        // KAP_DEBUG_LOG("Je passe ici !");
        // if (pos.getY() > 150) {
        //     std::cout << "hello\n";
        //     pos.setY(pos.getY() + (_rect.at("Ship").getSize().getY() * _speed));
        // } 
        // // else {
        // //     pos.setY(pos.getY() + (_rect.getSize().getY() * (_nbAnimation - crossProduct)));
        // // }
        // getImage("Ship").setRectangle({pos, _rect.at("Ship").getSize()});
    }

    //TO DO : mettre les rect initiaux
    void HowToPlayAnimation::onResetAnim() {
        // getImage("Ship").setRectangle({0, 0, 0, 0});
        // getImage("Bullet").setRectangle({0, 0, 0, 0});
        // getImage("Bubulle").setRectangle({0, 0, 0, 0});
        // getImage("Explosion").setRectangle({0, 0, 0, 0});
    }

    void HowToPlayAnimation::setNbAnimations(std::string name, int nbAnimations) {
        _nbAnimation.at(name) = nbAnimations;
    }

    void HowToPlayAnimation::setRect(std::string name, Tools::Rectangle rect) {
        _rect.at(name) = rect;
    }

    KapEngine::Tools::Rectangle HowToPlayAnimation::getRect(std::string name) {
        return (_rect.at(name));
    }

    UI::Image &HowToPlayAnimation::getImage(std::string name) {
        try {
            // return getGameObject().getComponent<UI::Image>();
            // return _gameObject->getComponent<UI::Image>();
            // return _allGameObject.at(name)->getComponent<UI::Image>();
            // return _gameObject->getComponent<UI::Image>(name);
            return _shipObject->getComponent<UI::Image>();
        } catch (...) {
           Debug::error("Failed to get image of how to play " + getGameObject().getName());
        }
        throw Errors::ComponentError("Failed to get image of button");
    }

} //Rtype
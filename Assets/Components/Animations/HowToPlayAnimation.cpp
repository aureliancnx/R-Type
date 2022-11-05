/*
** EPITECH PROJECT, 2022
** Rytpe
** File description:
** HowToPlayAnimation
*/

#include "HowToPlayAnimation.hpp"
#include "SpriteAnimation.hpp"

using namespace KapEngine;

namespace RType {

    HowToPlayAnimation::HowToPlayAnimation(std::shared_ptr<KapEngine::GameObject> gameObject) : Animation(gameObject) {
        _gameObject = gameObject;
        init(gameObject);
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Ship", ));
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Bullet", ));
        _allGameObject.insert(std::make_pair("bubulle", gameObject));
        // _allGameObject.insert(std::make_pair<std::string, std::shared_ptr<KapEngine::GameObject>>("Explosion",));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Ship", 5));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Bullet", 2));
        _nbAnimation.insert(std::make_pair<std::string, int>("bubulle", 12));
        // _nbAnimation.insert(std::make_pair<std::string, int>("Explosion", 6));
        // _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Ship", {0, 0, 0, 0}));
        // _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Bullet", {0, 0, 0, 0}));
        _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("bubulle", {0, 0, 17, 18}));
        // _rect.insert(std::make_pair<std::string, KapEngine::Tools::Rectangle>("Explosion", {0, 0, 0, 0}));
        setTiming(3);
    }

    void HowToPlayAnimation::init(std::shared_ptr<GameObject> gameObject) { addRequireComponent("Image"); }

    void HowToPlayAnimation::onFixedUpdate() {
        auto& transform = getImage("bubulle").getTransform();

        if (_invert) {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, -5.0f, 0));
        } else {
            transform.setPosition(transform.getLocalPosition() + KapEngine::Tools::Vector3(0, 5.0f, 0));
        }

        if (transform.getWorldPosition().getY() > 350) {
            _invert = true;
        } else if (transform.getWorldPosition().getY() < 50) {
            _invert = false;
        }
    }

    void HowToPlayAnimation::onResetAnim() {
        // getImage("Ship").setRectangle({0, 0, 0, 0});
        // getImage("Bullet").setRectangle({0, 0, 0, 0});
        getImage("bubulle").setRectangle({0, 0, 17, 18});
        // getImage("Explosion").setRectangle({0, 0, 0, 0});
    }

    void HowToPlayAnimation::setRect(std::string name, Tools::Rectangle rect) { _rect.at(name) = rect; }

    KapEngine::Tools::Rectangle HowToPlayAnimation::getRect(std::string name) { return (_rect.at(name)); }

    UI::Image& HowToPlayAnimation::getImage(std::string name) {
        try {
            return _allGameObject.at(name)->getComponent<UI::Image>();
        } catch (...) { Debug::error("Failed to get image of button " + getGameObject().getName()); }
        throw Errors::ComponentError("Failed to get image of button");
    }

} // namespace RType
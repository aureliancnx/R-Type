/*
** EPITECH PROJECT, 2022
** RType
** File description:
** SpriteAnimation
*/

#include "SpriteAnimation.hpp"

using namespace KapEngine;

namespace RType {

    SpriteAnimation::SpriteAnimation(std::shared_ptr<GameObject> gameObject) : Animation(gameObject) {
        init(gameObject);
    }

    SpriteAnimation::SpriteAnimation(std::shared_ptr<GameObject> gameObject, int nbAnimation,
                                     Tools::Rectangle rect, int64_t const &time) : Animation(gameObject) {
        _nbAnimation = nbAnimation;
        _rect = rect;
        setTiming(time);
        init(gameObject);
    }

    void SpriteAnimation::init(std::shared_ptr<GameObject> gameObject) {
        addRequireComponent("Image");
    }

    void SpriteAnimation::onPlay() {
        getImage().setRectangle(_rect);
    }

    void SpriteAnimation::onUpdateAnim() {
//            CurrTime current time animation (number of repetition)
//            _currTime
//            Time max to play animation
//            _timing
//            (_nbAnime * _currTime) / _timing(MicroSecond) = current position on sprite to anime
        int crossProduct = (_nbAnimation * _currTime) / _timing.asMicroSecond();
        Tools::Vector2 pos = _rect.getPos();
        pos.setX(pos.getX() + (_rect.getSize().getX() * crossProduct));
        getImage().setRectangle({pos, _rect.getSize()});
    }

    void SpriteAnimation::onResetAnim() {
        getImage().setRectangle(_rect);
    }

    void SpriteAnimation::setNbAnimations(int nbAnimations) {
        _nbAnimation = nbAnimations;
    }

    void SpriteAnimation::setRect(Tools::Rectangle rect) {
        _rect = rect;
    }

    UI::Image &SpriteAnimation::getImage() {
        try {
            return getGameObject().getComponent<UI::Image>();
        } catch (...) {
           Debug::error("Failed to get image of button " + getGameObject().getName());
        }
        throw Errors::ComponentError("Failed to get image of button");
    }

} // RType
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
        bool goBouncing = false;
        int crossProduct = (_nbAnimation * _currTime) / _timing.asMicroSecond();

        if (crossProduct > _nbAnimation / 2 && _bounce)
            goBouncing = true;

        Tools::Vector2 pos = _rect.getPos();
        Tools::Vector2 size = _rect.getSize();
        Tools::Vector2 newPos = pos;
        if (!goBouncing) {
            if (!_reverse) {
                if (_changeWithY) {
                    newPos.setY(pos.getY() + size.getY() * crossProduct);
                } else {
                    newPos.setX(pos.getX() + size.getX() * crossProduct);
                }
            } else {
                if (_changeWithY) {
                    newPos.setY(pos.getY() - size.getY() * crossProduct);
                } else {
                    newPos.setX(pos.getX() - size.getX() * crossProduct);
                }
            }
        } else {
            if (_changeWithY) {
                newPos.setY(pos.getY() + (size.getY() * (_nbAnimation - crossProduct)));
            } else {
                newPos.setX(pos.getX() + (size.getX() * (_nbAnimation - crossProduct)));
            }
        }
        getImage().setRectangle({newPos, size});
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
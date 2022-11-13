/*
** EPITECH PROJECT, 2022
** RType
** File description:
** SpriteAnimation
*/

#include "SpriteAnimation.hpp"

using namespace KapEngine;

namespace RType {

    SpriteAnimation::SpriteAnimation(std::shared_ptr<GameObject> gameObject) : Animation(gameObject) { init(gameObject); }

    SpriteAnimation::SpriteAnimation(std::shared_ptr<GameObject> gameObject, int nbAnimation, Tools::Rectangle rect, int64_t const &time)
        : Animation(gameObject) {
        _nbAnimation = nbAnimation;
        _rect = rect;
        setTiming(time);
        init(gameObject);
    }

    void SpriteAnimation::init(std::shared_ptr<GameObject> gameObject) { addRequireComponent("Image"); }

    void SpriteAnimation::onPlay() { getImage().setRectangle(_rect); }

    void SpriteAnimation::onUpdateAnim() {
        bool goBouncing = false;
        int crossProduct = (_nbAnimation * _currTime) / _timing.asMicroSecond();

        getImage().setRectangle({calculateNewPos(crossProduct), _rect.getSize()});
    }

    void SpriteAnimation::onResetAnim() { getImage().setRectangle(_rect); }

    void SpriteAnimation::setNbAnimations(int nbAnimations, std::size_t xAnims, std::size_t yAnims) {
        _nbAnimation = nbAnimations;
        _nbXTextures = xAnims;
        _nbYTextures = yAnims;
        if (xAnims == 0 && yAnims == 0) {
            _nbXTextures = _nbAnimation;
            _nbYTextures = 1;
        }
    }

    void SpriteAnimation::setRect(Tools::Rectangle rect) { _rect = rect; }

    UI::Image &SpriteAnimation::getImage() {
        try {
            return getGameObject().getComponent<UI::Image>();
        } catch (...) { DEBUG_ERROR("Failed to get image of button " + getGameObject().getName()); }
        throw Errors::ComponentError("Failed to get image of button");
    }

    KapEngine::Tools::Vector2 SpriteAnimation::calculateNewPos(int crossProduct) {
        bool goBouncing = false;
        int nbYPassed = 0;
        while (crossProduct >= _nbXTextures) {
            crossProduct -= _nbXTextures;
            nbYPassed++;
        }
        int nbTotpassed = nbYPassed * _nbXTextures;

        Tools::Vector2 nPos = _rect.getPos();
        if (crossProduct > _nbAnimation / 2 && _bounce)
            goBouncing = true;
        if (goBouncing) {
            if (crossProduct == 0) {
                nbYPassed--;
                crossProduct = _nbXTextures - 1;
            } else {
                crossProduct--;
            }
            nPos.setX(crossProduct * _rect.getSize().getX());
            nPos.setY(nbYPassed * _rect.getSize().getY());
        } else {
            nPos.setX(_rect.getPos().getX() + (_rect.getSize().getX() * crossProduct));
            nPos.setY(_rect.getPos().getY() + (_rect.getSize().getY() * nbYPassed));
        }
        return nPos;
    }

} // namespace RType
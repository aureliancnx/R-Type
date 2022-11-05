/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ParalaxAnimation.cpp
*/

#include "ParalaxAnimation.hpp"

namespace RType {
    ParalaxAnimation::ParalaxAnimation(std::shared_ptr<KapEngine::GameObject> canvas) : Animation(canvas) {
        _speed = 0.1f;
        _width = 271;
    }

    ParalaxAnimation::ParalaxAnimation(std::shared_ptr<KapEngine::GameObject> canvas, float speed, int width) : Animation(canvas) {
        _speed = speed;
        _width = width;
    }

    void ParalaxAnimation::onPlay() {
        // Nothing here
    }

    void ParalaxAnimation::onUpdateAnim() {
        KapEngine::Tools::Vector3 pos = getTransform().getLocalPosition();
        if (pos.getX() < -_width)
            pos.setX(0);
        pos.setX(pos.getX() - _speed);
        getTransform().setPosition(pos);
    }

    void ParalaxAnimation::onResetAnim() { getTransform().setPosition({0, 0, 0}); }

    void ParalaxAnimation::setSpeed(float speed) { _speed = speed; }

    void ParalaxAnimation::setWidth(int width) { _width = width; }

} // namespace RType
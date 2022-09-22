/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibGraphical
*/

#include "RaylibGraphical.hpp"
#include "Vectors.hpp"
#include "Debug.hpp"

KapEngine::Graphical::RaylibGraphical::RaylibGraphical(GraphicalLibManager &manager) : GraphicalLib("raylib", manager) {

    Tools::Vector2 size = manager.getEngine().getScreenSize();

    raylib = std::make_unique<RaylibEncapsulation>(
        size.getX(),
        size.getY(),
        manager.getEngine().getGameName(),
        manager.getEngine().getMaxFps()
    );

}

KapEngine::Graphical::RaylibGraphical::~RaylibGraphical() {
    raylib->closeWindow();
}

void KapEngine::Graphical::RaylibGraphical::clearCache() {

}

void KapEngine::Graphical::RaylibGraphical::stopDisplay() {
    raylib->closeWindow();
}

void KapEngine::Graphical::RaylibGraphical::startDisplay() {
    raylib->openWindow();
    Debug::log("Use " + getName());
}

void KapEngine::Graphical::RaylibGraphical::clear() {
    raylib->startDrawing();
}

void KapEngine::Graphical::RaylibGraphical::display() {
    raylib->stopDrawing();
}

void KapEngine::Graphical::RaylibGraphical::getEvents() {
    if (raylib->windownShouldClose()) {
        manager.getEngine().stop();
        return;
    }
}

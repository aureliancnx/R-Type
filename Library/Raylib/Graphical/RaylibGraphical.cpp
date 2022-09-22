/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibGraphical
*/

#include "RaylibGraphical.hpp"
#include "Vectors.hpp"

KapEngine::Graphical::RaylibGraphical::RaylibGraphical(GraphicalLibManager &manager) : GraphicalLib("raylib", manager) {

    Tools::Vector2 size = manager.getEngine().getScreenSize();

    raylib = std::make_unique<RaylibEncapsulation>(
        size.getX(),
        size.getY(),
        manager.getEngine().getGameName(),
        manager.getEngine().getMaxFps()
    );

}

KapEngine::Graphical::RaylibGraphical::~RaylibGraphical() {}




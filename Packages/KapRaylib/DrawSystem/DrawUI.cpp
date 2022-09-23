/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DrawUI
*/

#include "DrawUI.hpp"
#include "Encapsulation/RaylibEncapsulation.hpp"

void KapEngine::Graphical::Raylib::Draw::DrawSpriteColor::draw() {
    _encap.__drawRectangle(_posX, _posY, _width, _heigth, _color);
}

void KapEngine::Graphical::Raylib::Draw::DrawText::draw() {
    _encap.__drawText(_font, _text, _pos, _size, _spacing, _col);
}

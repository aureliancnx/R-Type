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
    if (fontSet) {
        _encap.__drawText(_font, _text, _pos, _size, _spacing, _col);
    } else {
        _encap.__drawText(_text, _pos, _size, _spacing, _col);
    }
}

void KapEngine::Graphical::Raylib::Draw::DrawSpriteTexture::draw() {
    _encap.__drawTexture(_path, _posX, _posY, _width, _heigth, _rect, _rot, _color);
}

/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DrawUI
*/

#ifndef DRAWUI_HPP_
#define DRAWUI_HPP_

#include "RaylibEncapsulation.hpp"

namespace KapEngine {

    namespace Graphical {

        class DrawUI {
            public:
                virtual ~DrawUI() {}

                virtual void draw() = 0;
                virtual void clear() = 0;

            protected:
            private:
        };

        /**
         * @brief Use to draw rectangle colored without images or specify things
         * 
         */
        class DrawSpriteColor : public DrawUI {
            public:

                DrawSpriteColor() {}
                DrawSpriteColor(float x, float y, float w, float h, Color c) {
                    setPosX(x);
                    setPosY(y);
                    setWidth(w);
                    setHeigth(h);
                    setColor(c);
                }

                void draw() override {
                    RaylibEncapsulation::drawRectangle(_posX, _posY, _width, _heigth, _color);
                }

                //getters

                float getPosX() const {
                    return _posX;
                }

                float getPosY() const {
                    return _posY;
                }

                float getWidth() const {
                    return _width;
                }

                float getHeigth() const {
                    return _heigth;
                }

                Color getColor() const {
                    _color;
                }

                //setters

                void setPosX(float x) {
                    _posX = x;
                }

                void setPosY(float y) {
                    _posY = y;
                }

                void setWidth(float w) {
                    _width = w;
                }

                void setHeigth(float h) {
                    _heigth = h;
                }

                void setColor(Color col) {
                    _color = col;
                }

            private:
                float _posX;
                float _posY;
                float _width;
                float _heigth;
                Color _color;
        };

    }

}

#endif /* !DRAWUI_HPP_ */

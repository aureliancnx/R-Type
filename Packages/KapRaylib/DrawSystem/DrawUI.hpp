/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** DrawUI
*/

#ifndef DRAWUI_HPP_
#define DRAWUI_HPP_

#include "raylib.h"
#include <string>

namespace KapEngine {
    namespace Graphical {

        namespace Raylib {

            class RaylibEncapsulation;

        }
    }
}

namespace KapEngine {

    namespace Graphical {

        namespace Raylib {

            namespace Draw {

                class DrawUI {
                    public:
                        virtual ~DrawUI() {}

                        virtual void draw() = 0;
                        virtual void clear() = 0;

                    protected:
                    private:
                };

                class RaylibDrawing : public DrawUI {

                    public:
                        RaylibDrawing (RaylibEncapsulation &encapsulation) : _encap(encapsulation) {}
                        ~RaylibDrawing () {}

                        virtual void draw() override {}
                        virtual void clear() override {}
                    
                    protected:
                        RaylibEncapsulation &_encap;

                };

                /**
                 * @brief Use to draw rectangle colored without images or specify things
                 *
                 */
                class DrawSpriteColor : public RaylibDrawing {
                    public:

                        DrawSpriteColor(RaylibEncapsulation &e) : RaylibDrawing(e) {}
                        DrawSpriteColor(RaylibEncapsulation &e, float x, float y, float w, float h, Color c) : RaylibDrawing(e) {
                            setPosX(x);
                            setPosY(y);
                            setWidth(w);
                            setHeigth(h);
                            setColor(c);
                        }

                        void draw() override;

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
                            return _color;
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

                class DrawSpriteTexture : public RaylibDrawing {
                    public:
                        DrawSpriteTexture(RaylibEncapsulation &e) : RaylibDrawing(e) {}
                        DrawSpriteTexture(RaylibEncapsulation &e, std::string const& path, float x, float y, float w, float h, Color c) : RaylibDrawing(e) {
                            setPosX(x);
                            setPosY(y);
                            setWidth(w);
                            setHeigth(h);
                            setColor(c);
                        }

                        void draw() override;

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
                            return _color;
                        }

                        std::string getPath() const {
                            return _path;
                        }

                        Rectangle getRectangle() const {
                            return _rect;
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

                        void setPathTexture(std::string const& path) {
                            _path = path;
                        }

                        void setRot(float r) {
                            _rot = r;
                        }

                        void setRectangle(Rectangle rect) {
                            _rect = rect;
                        }

                    private:
                        float _posX = 0.f;
                        float _posY = 0.f;
                        float _width = 1.f;
                        float _heigth = 1.f;
                        float _rot= 0.f;
                        Color _color;
                        std::string _path;
                        Rectangle _rect;
                };

                class DrawText : public RaylibDrawing {
                    public:
                        DrawText(RaylibEncapsulation &e) : RaylibDrawing(e) {}

                        void draw() override;

                        void setText(std::string const& text) {
                            _text = text;
                        }
                        void setPos(Vector2 pos) {
                            _pos = pos;
                        }
                        void setSpacing(float spacing) {
                            _spacing = spacing;
                        }
                        void setSize(float size) {
                            _size = size;
                        }
                        void setColor(Color col) {
                            _col = col;
                        }
                        void setFont(Font font) {
                            _font = font;
                            fontSet = true;
                        }

                    private:
                        bool fontSet = false;
                        std::string _text;
                        Font _font;
                        float _spacing;
                        float _size;
                        Vector2 _pos;
                        Color _col;
                };

            }

        }

    }

}

#endif /* !DRAWUI_HPP_ */

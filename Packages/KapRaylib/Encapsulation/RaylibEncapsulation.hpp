/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibEncapsulation
*/

#ifndef RAYLIBENCAPSULATION_HPP_
#define RAYLIBENCAPSULATION_HPP_

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

#include "DrawSystem/DrawUI.hpp"
#include "Cache/RaylibCache.hpp"

#include "raylib.h"

namespace KapEngine {
    namespace Graphical {

        //raylib draw system

        namespace Draw {
            class RaylibDrawing;
            class DrawSpriteColor;
            class DrawText;
        }
    }

    namespace Events {
        class Key;
    }
}

namespace KapEngine {

    namespace Graphical {

        namespace Raylib {

            class RaylibEncapsulation {
                public:
                    RaylibEncapsulation(int const& windowWidth, int const& windowHeight, std::string const& title, int const& fps) {
                        _widthWindow = windowWidth;
                        _heightWindow = windowHeight;
                        _title = title;
                        _fps = fps;
                        setVisibleFps(true);
                        SetTraceLogLevel(LOG_NONE);
                    }
                    ~RaylibEncapsulation() {
                        closeWindow();
                    }

                    void openWindow() {
                        if (opened)
                            return;
                        InitWindow(_widthWindow, _heightWindow, _title.c_str());
                        SetTargetFPS(_fps);
                        InitAudioDevice();
                        initCam();
                        opened = true;
                    }

                    void closeWindow() {
                        if (!opened)
                            return;
                        // stopAllMsuics();
                        CloseWindow();
                        CloseAudioDevice();
                        stopCam();
                        clearCache();
                        opened = false;
                        std::cout << "Clearing RAYLIB" << std::endl;
                    }

                    bool windownShouldClose() {
                        return WindowShouldClose();
                    }

                    void startDrawing() {
                        if (!opened)
                            return;
                        BeginDrawing();
                        clearWindow();
                        if (!camSet) {
                            drawNoCamText();
                            stopDrawing();
                            canDraw = false;
                            return;
                        }
                        //update music
                        canDraw = true;
                    }

                    void stopDrawing() {
                        if (_firstRun) {
                            _firstRun = false;
                            return;
                        }
                        if (!opened)
                            return;
                        canDraw = false;
                        if (camSet) {
                            BeginMode3D(_camera);
                            //draw 3D elements
                            EndMode3D();

                            for (std::size_t i = 0; i < _drawUi.size(); i++) {
                                _drawUi[i]->draw();
                                _drawUi[i]->clear();
                            }

                            _drawUi.clear();
                        }
                        if (_drawFps) {
                            drawFps();
                        }
                        EndDrawing();
                    }

                    void setVisibleFps(bool b) {
                        _drawFps = b;
                    }

                    void clearWindow() {
                        if (!opened)
                            return;
                        ClearBackground(_background);
                    }

                    void setBackgroundColor(Color background) {
                        _background = background;
                    }

                    void initCam() {
                        if (camSet)
                            return;
                        _camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
                        _camera.target = (Vector3){ 0.0f, 8.0f, 0.0f };
                        _camera.up = (Vector3){ 0.0f, 1.6f, 0.0f };
                        _camera.fovy = 45.0f;
                        _camera.projection = CAMERA_PERSPECTIVE;
                        camSet = true;
                    }

                    void stopCam() {
                        if (!camSet)
                            return;
                        camSet = false;
                    }

                    void updateCam(Vector3 pos, Vector3 target, Vector3 up, float fov) {
                        _camera.position = pos;
                        _camera.target = target;
                        _camera.up = up;
                        _camera.fovy = fov;
                    }

                    void updateCamProjection(int proj) {
                        _camera.projection = proj;
                    }

                    void clearCache();

                    void drawFps() {
                        DrawFPS(10, 10);
                    }

                    /**
                     * @brief unload part
                     * 
                     */

                    void unloadFont(std::string const& fontPath);

                    void unloadAllFonts();

                    void __unloadFont(Font const& font) {
                        UnloadFont(font);
                    }

                    void __unloadImage(Image const& img) {
                        UnloadImage(img);
                    }

                    /**
                     * @brief load part
                     * 
                     */

                    void loadFont(std::string const& fontPath);

                    Font &getFont(std::string const& fontPath, bool alreadyTry = false);

                    Image __loadImage(std::string const& imagePath) {
                        return LoadImage(imagePath.c_str());
                    }

                    Font __loadFont(std::string const& fontPath) {
                        return LoadFont(fontPath.c_str());
                    }

                    /**
                     * @brief Draw part
                     * 
                     */

                    void drawRectangle(float posX, float posY, float width, float heigth, Color color) {
                        auto sprite = std::make_shared<Draw::DrawSpriteColor>(*this, posX, posY, width, heigth, color);
                        _drawUi.push_back(sprite);
                    }

                    void __drawRectangle(float posX, float posY, float width, float hiegth, Color color) {
                        DrawRectangle(posX, posY, width, hiegth, color);
                    }

                    void drawText(std::string const& fontPath, std::string const& text, Vector2 pos, float fontSize, float spacing, Color col) {
                        auto txt = std::make_shared<Draw::DrawText>(*this);
                        
                        txt->setColor(col);
                        txt->setPos(pos);
                        txt->setSize(fontSize);
                        txt->setSpacing(spacing);
                        txt->setText(text);
                        if (fontPath != "")
                            txt->setFont(getFont(fontPath));

                        _drawUi.push_back(txt);
                    }

                    void __drawText(Font font, std::string const& text, Vector2 pos, float fontSize, float spacing, Color col) {
                        DrawTextEx(font, text.c_str(), pos, fontSize, spacing, col);
                    }

                    void __drawText(std::string const& text, Vector2 pos, float fontSize, float spacing, Color col) {
                        DrawText(text.c_str(), pos.x, pos.y, fontSize, col);
                    }

                    void drawTexture(std::string const& path, float posX, float posY, float width, float heigth, Color col) {

                    }

                    void __drawTexture();

                    /**
                     * @brief Input part
                     * 
                     */

                    bool isGamepadConnected(int gpId) {
                        return IsGamepadAvailable(gpId);
                    }

                    int maxJoystickGamepad(int gpId) {
                        if (!isGamepadConnected(gpId))
                            return 0;
                        return GetGamepadAxisCount(gpId);
                    }

                    float getGamepadJoystickValue(int gpId, int joystickId) {
                        if (!isGamepadConnected(gpId))
                            return 0.0f;
                        if (maxJoystickGamepad(gpId) <= joystickId)
                            return 0.0f;
                        return GetGamepadAxisMovement(gpId, joystickId);
                    }

                    int getKeyPressed() {
                        return GetKeyPressed();
                    }

                    bool isKeyReleased(int key) {
                        return IsKeyReleased(key);
                    }

                    bool isMouseButtonReleased(int btn) {
                        return IsMouseButtonReleased(btn);
                    }

                    bool isMouseButtonPressed(int btn) {
                        return IsMouseButtonPressed(btn);
                    }

                    bool isGamepadButtonReleased(int gpId, int btn) {
                        return IsGamepadButtonReleased(gpId, btn);
                    }

                    bool isGamepadButtonPressed(int gpId, int btn) {
                        return IsGamepadButtonPressed(gpId, btn);
                    }

                protected:
                    void drawNoCamText() {
                        DrawText("No camera found !", _widthWindow / 2 - 65.f, _heightWindow / 2 - 20.f, 15.0f, WHITE);
                    }

                private:
                    //cam
                    Camera3D _camera;
                    bool camSet = false;
                    bool opened = false;
                    Color _background;

                    //windown settings
                    int _widthWindow;
                    int _heightWindow;
                    std::string _title;
                    int _fps;

                    //draw settings
                    bool canDraw = false;
                    bool _drawFps = false;
                    bool _debug = false;
                    bool _firstRun = true;

                    //cache
                    std::vector<std::shared_ptr<Cache::RaylibCache>> _cache;

                    std::vector<std::shared_ptr<Draw::RaylibDrawing>> _drawUi;
            };

        }

    }

}

#endif /* !RAYLIBENCAPSULATION_HPP_ */

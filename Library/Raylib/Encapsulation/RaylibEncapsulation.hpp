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

#include "raylib.h"

namespace KapEngine {
    namespace Graphical {

        //raylib draw system
        class DrawUI;
        class DrawSpriteColor;
    }
}

namespace KapEngine {

    namespace Graphical {

        class RaylibEncapsulation {
            public:
                RaylibEncapsulation(int const& windowWidth, int const& windowHeight, std::string const& title, int const& fps) {
                    _widthWindow = windowWidth;
                    _heightWindow = windowHeight;
                    _title = title;
                    _fps = fps;
                    setVisibleFps(true);
                }
                ~RaylibEncapsulation();

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
                        for (std::size_t i = 0; i < _uiToDraw.size(); i++) {
                            _uiToDraw[i]->draw();
                            _uiToDraw[i]->clear();
                        }
                        _uiToDraw.clear();
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

                void clearCache() {
                    unloadAllFonts();
                }

                void drawFps() {
                    DrawFPS(10, 10);
                }

                /**
                 * @brief unload part
                 * 
                 */

                void unloadFont(std::string const& fontPath) {
                    if (_fonts.find(fontPath) == _fonts.end())
                        return;
                    UnloadFont(_fonts[fontPath]);
                }

                void unloadAllFonts() {
                    for (auto it = _fonts.begin(); it != _fonts.end(); ++it) {
                        unloadFont(it->first);
                    }
                    _fonts.clear();
                }

                /**
                 * @brief load part
                 * 
                 */

                void loadFont(std::string const& fontPath) {

                }

                Font &getFont(std::string const& fontPath) {
                    loadFont(fontPath);

                    return _fonts[fontPath];
                }

                /**
                 * @brief Draw part
                 * 
                 */

                void drawrectangle(float posX, float posY, float width, float heigth, Color color) {
                    std::shared_ptr<DrawSpriteColor> spriteColor = std::make_shared<DrawSpriteColor>(posX, posY, width, heigth, color);
                    _uiToDraw.push_back(spriteColor);
                }

                static void __drawRectangle(float posX, float posY, float width, float hiegth, Color color) {
                    DrawRectangle(posX, posY, width, hiegth, color);
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
                std::map<std::string, Font> _fonts;

                std::vector<std::shared_ptr<DrawUI>> _uiToDraw;
        };

    }

}

#endif /* !RAYLIBENCAPSULATION_HPP_ */

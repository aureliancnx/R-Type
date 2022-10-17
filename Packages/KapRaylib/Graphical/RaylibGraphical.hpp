/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibGraphical
*/

#ifndef RAYLIBGRAPHICAL_HPP_
#define RAYLIBGRAPHICAL_HPP_

#include <memory>

#include "Encapsulation/RaylibEncapsulation.hpp"

#include "KapEngine.hpp"
#include "KapEngineEvents.hpp"
#include "KapEngineGraphical.hpp"

namespace KapEngine
{

namespace Graphical
{

namespace Raylib
{

class RaylibGraphical : public GraphicalLib
{
public:
  RaylibGraphical(GraphicalLibManager &manager, bool drawWindow = true);
  ~RaylibGraphical();

  void clearCache() override;
  void stopDisplay() override;
  void startDisplay() override;

  void clear() override;
  void display() override;
  void getEvents() override;

  void playSound(std::string const &soundPath) override;
  void playMusic(std::string const &musicPath, float volume = 1.0f) override;
  void stopMusic() override;
  void pauseMusic() override;
  void resumMusic() override;
  void restartMusic() override;

  float getJoystikValue(int gamepadId, int joystickId) override;

  Tools::Vector2 getMousePosition() const override;
  Tools::Vector2 getScreenSize() override;

  Events::Key::EKey toKey(KeyboardKey _key);
  Events::Key::EKey toKey(MouseButton _key);
  Events::Key::EKey toKey(GamepadButton _key, int id);
  Events::Key::EKey toKey(int _key);

  int toRaylibKey(Events::Key key);
  int toRaylibKey(Events::Key::EKey key);

  bool keyAlreadyInList(Events::Key key);

  bool isGamepadButtonReleasedEngine(Events::Key key);
  bool isGamepadButtonReleasedEngine(Events::Key::EKey key);
  bool isGamepadButtonPressedEngine(Events::Key key);
  bool isGamepadButtonPressedEngine(Events::Key::EKey key);

  Color engineToRaylib(Tools::Color const &color) const;
  Vector2 engineToRaylib(Tools::Vector2 const &vector) const;
  Rectangle engineToRaylib(Tools::Rectangle const &rect);

protected:
private:
  std::unique_ptr<RaylibEncapsulation> raylib;
  bool _drawWindow;

  bool drawable(Tools::Vector2 const &pos, Tools::Vector2 const &scale);
};

} // namespace Raylib

} // namespace Graphical
} // namespace KapEngine

#endif /* !RAYLIBGRAPHICAL_HPP_ */

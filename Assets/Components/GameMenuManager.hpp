/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameMenuManager
*/

#ifndef GAMEMENUMANAGER_HPP_
#define GAMEMENUMANAGER_HPP_

#include "KapEngine.hpp"

using namespace KapEngine;

namespace RType
{

    class GameMenuManager : public Component
    {
      public:
        GameMenuManager(std::shared_ptr<GameObject> go);
        ~GameMenuManager();

        void onAwake() override;

        void displayMainMenu();
        void displayBonusMenu();
        void displayPauseMenu();

      private:
        void initMainMenu();
        void initBonusMenu();
        void initPauseMenu();

        void initBackground(std::shared_ptr<GameObject> parent);
        std::shared_ptr<GameObject> initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text,
                                               std::function<void()> callback, Tools::Color color = Tools::Color::white(),
                                               Tools::Color textColor = Tools::Color::black());
        std::shared_ptr<GameObject> initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text,
                                               std::function<void()> callback, std::string pathSprite, Tools::Rectangle rect,
                                               Tools::Color color = Tools::Color::white(), Tools::Color textColor = Tools::Color::black());

        // variables
      private:
        std::shared_ptr<GameObject> mainMenu;
        std::shared_ptr<GameObject> pauseMenu;
        std::shared_ptr<GameObject> bonusMenu;
    };

} // namespace RType

#endif /* !GAMEMENUMANAGER_HPP_ */

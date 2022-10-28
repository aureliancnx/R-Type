/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameMenuManager
*/

#ifndef GAMEMENUMANAGER_HPP_
#define GAMEMENUMANAGER_HPP_

#include "GameObject.hpp"

namespace RType
{

    class GameMenuManager : public KapEngine::Component
    {
      public:
        GameMenuManager(std::shared_ptr<KapEngine::GameObject> go);
        ~GameMenuManager();

        void onAwake() override;

        void displayMainMenu();

      private:
        void initMainMenu();

        void initBackground(std::shared_ptr<KapEngine::GameObject> parent);
        std::shared_ptr<KapEngine::GameObject> initButton(std::shared_ptr<KapEngine::GameObject> parent, std::string name, std::string text,
                                                          std::function<void()> callback,
                                                          KapEngine::Tools::Color color = KapEngine::Tools::Color::white(),
                                                          KapEngine::Tools::Color textColor = KapEngine::Tools::Color::black());
        std::shared_ptr<KapEngine::GameObject> initButton(std::shared_ptr<KapEngine::GameObject> parent, std::string name, std::string text,
                                                          std::function<void()> callback, std::string pathSprite,
                                                          KapEngine::Tools::Rectangle rect,
                                                          KapEngine::Tools::Color color = KapEngine::Tools::Color::white(),
                                                          KapEngine::Tools::Color textColor = KapEngine::Tools::Color::black());

        void initHeart();
        void addLife();
        void removeLife();

        // variables
      private:
        std::shared_ptr<KapEngine::GameObject> mainMenu;
        std::shared_ptr<KapEngine::GameObject> heart1;
        std::shared_ptr<KapEngine::GameObject> heart2;
        std::shared_ptr<KapEngine::GameObject> heart3;
    };

} // namespace RType

#endif /* !GAMEMENUMANAGER_HPP_ */

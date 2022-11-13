/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameMenuManager
*/

#ifndef GAMEMENUMANAGER_HPP_
#define GAMEMENUMANAGER_HPP_

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"

#include "Animations/SpriteAnimation.hpp"

namespace RType {

    class GameMenuManager : public KapMirror::NetworkComponent {
      public:
        explicit GameMenuManager(std::shared_ptr<KapEngine::GameObject> go);
        ~GameMenuManager() = default;

        void onStart() override;

        void onStartClient() override;

        void displayMainMenu();

        std::shared_ptr<KapEngine::Animator> getMissileAnimator() const { return missileAnimator; }

        void updateHealth(int health);

        void displayEndMenu(bool win);

        void display(bool win);

      private:
        void initMainMenu(bool local = true);

        void initBackground(const std::shared_ptr<KapEngine::GameObject> &parent);
        std::shared_ptr<KapEngine::GameObject> initButton(const std::shared_ptr<KapEngine::GameObject> &parent, const std::string &name,
                                                          std::string text, std::function<void()> callback,
                                                          const KapEngine::Tools::Color &color = KapEngine::Tools::Color::white(),
                                                          const KapEngine::Tools::Color &textColor = KapEngine::Tools::Color::black());
        std::shared_ptr<KapEngine::GameObject> initButton(const std::shared_ptr<KapEngine::GameObject> &parent, const std::string &name,
                                                          std::string text, std::function<void()> callback, const std::string &pathSprite,
                                                          const KapEngine::Tools::Rectangle &rect,
                                                          const KapEngine::Tools::Color &color = KapEngine::Tools::Color::white(),
                                                          const KapEngine::Tools::Color &textColor = KapEngine::Tools::Color::black());

        // variables
      private:
        std::shared_ptr<KapEngine::GameObject> mainMenu;
        std::shared_ptr<KapEngine::Animator> missileAnimator;
    };

} // namespace RType

#endif /* !GAMEMENUMANAGER_HPP_ */

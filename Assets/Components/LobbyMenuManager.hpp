/*
** EPITECH PROJECT, 2022
** RType
** File description:
** LobbyMenuManager.hpp
*/

#ifndef RTYPE_LOBBYMENUMANAGER_HPP
#define RTYPE_LOBBYMENUMANAGER_HPP

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

#include "GameMenuManager.hpp"

namespace RType {

    class LobbyMenuManager : public KapMirror::NetworkComponent {
      public:
        explicit LobbyMenuManager(std::shared_ptr<KapEngine::GameObject> go);
        ~LobbyMenuManager() = default;

        void onStart() override;

        void onStartClient() override;

        void quit();

      private:
        void initLobbyMenu(bool local = true);

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

        void startGame();

        // variables
      private:
        std::shared_ptr<KapEngine::GameObject> lobbyMenu;
        std::shared_ptr<KapEngine::UI::Inputfield> mapField;
    };

} // namespace RType

#endif // RTYPE_LOBBYMENUMANAGER_HPP

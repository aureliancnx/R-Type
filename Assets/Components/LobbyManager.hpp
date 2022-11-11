/*
** EPITECH PROJECT, 2022
** RType
** File description:
** LobbyManager.hpp
*/

#ifndef RTYPE_LOBBYMANAGER_HPP
#define RTYPE_LOBBYMANAGER_HPP

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"
#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

namespace KapEngine {

    class LobbyManager : public KapMirror::NetworkComponent {
      public:
        explicit LobbyManager(std::shared_ptr<KapEngine::GameObject> go);
        ~LobbyManager();

        void onStart() override;

        void onStartClient() override;

      private:
        // Methods
        void initLobby(bool local = true);
        void initBackground(std::shared_ptr<KapEngine::GameObject> parent);

        // Variables
        std::shared_ptr<KapEngine::GameObject> _mainMenu;
        std::shared_ptr<KapEngine::GameObject> _ready;
    };

} // namespace KapEngine

#endif // RTYPE_LOBBYMANAGER_HPP

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

namespace RType {

    class LobbyMenuManager : public KapMirror::NetworkComponent {
      public:
        explicit LobbyMenuManager(std::shared_ptr<KapEngine::GameObject> go);
        ~LobbyMenuManager() = default;

        void onStart() override;

        void onStartClient() override;

      private:
        void initLobbyMenu(bool local = true);

        void initBackground(std::shared_ptr<KapEngine::GameObject> parent);

        // variables
      private:
        std::shared_ptr<KapEngine::GameObject> lobbyMenu;
    };

} // namespace RType

#endif // RTYPE_LOBBYMENUMANAGER_HPP

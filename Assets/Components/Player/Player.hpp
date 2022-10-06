/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Player.hpp
*/

#ifndef R_TYPE_PLAYER_HPP
#define R_TYPE_PLAYER_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace KapEngine {
    namespace RType {

        class Player : Component {
            public:
                Player(std::shared_ptr<GameObject> gameObject);
                Player(std::shared_ptr<GameObject> gameObject, std::string const &path);

                void onUpdate() override;

                void setPath(std::string const &path);

            protected:
            private:
                // Functions
                void init(std::shared_ptr<GameObject> gameObject);
                UI::Image &getImage();

                // Variables
                std::string _path;
                Tools::Vector3 _lastPos;


        };

    } // KapEngine
} // RType

#endif //R_TYPE_PLAYER_HPP

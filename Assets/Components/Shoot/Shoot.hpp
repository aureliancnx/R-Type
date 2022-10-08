/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Shoot.hpp
*/

#ifndef RTYPE_SHOOT_HPP
#define RTYPE_SHOOT_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace KapEngine {
    namespace RType {

        class Shoot : public Component {
            public:
                Shoot(std::shared_ptr<GameObject> gameObject);
                Shoot(std::shared_ptr<GameObject> gameObject, const std::string &path, Tools::Rectangle rect);
                ~Shoot() = default;

                void onFixedUpdate() override;

                void setPath(const std::string &path);
                void setRectangle(const Tools::Rectangle &rect);
                void setDirection(const Tools::Vector2 &direction);
                void setPos(const Tools::Vector2 &pos);

                void shoot(const Tools::Vector2 &direction, const Tools::Vector2 &pos);

            protected:
            private:
                // Variables
                std::string _path;
                Tools::Rectangle _rect;
                Tools::Vector3 _pos;
                Tools::Vector3 _cPos;
                Tools::Vector2 _direction;

                // Functions
                void init(std::shared_ptr<GameObject> gameObject);
                UI::Image &getImage();
        };

    } // KapEngine
} // RType

#endif //RTYPE_SHOOT_HPP

//
// Created by kiwi on 03/10/22.
//

#ifndef RTYPE_SHOOT_HPP
#define RTYPE_SHOOT_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

#include "SpriteAnimation.hpp"

namespace KapEngine {
    namespace RType {

        class Shoot : public Component {
        public:
            explicit Shoot(std::shared_ptr<GameObject> gameObject);
            explicit Shoot(std::shared_ptr<GameObject> gameObject, std::string const &path, const std::string &sound);
            ~Shoot() = default;

            void onFixedUpdate() override;
            void animation();

            void setSound(std::string const &path);
            void setPath(std::string const &path);
            void setPos(Tools::Vector3);
            void setDirection(Tools::Vector2 direction);

        protected:
        private:
            // Variables
            Tools::Vector3 _pos;
            Tools::Vector3 _cPos;
            Tools::Vector2 _direction;
            std::shared_ptr<GameObject> _gameObject;
            std::string _path = "";
            std::string _sound = "";



            // Function
            void init(std::shared_ptr<GameObject> gameObject);
            UI::Image &getImage();
            void playSound(std::string const &string);
        };

    } // KapEngine
} // RType

#endif //RTYPE_SHOOT_HPP

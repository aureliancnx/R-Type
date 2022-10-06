//
// Created by kiwi on 03/10/22.
//

#ifndef RTYPE_PLAYER_HPP
#define RTYPE_PLAYER_HPP

#include <algorithm>

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

#include "Shoot/Shoot.hpp"

namespace KapEngine {
    namespace RType {

        class Player : public Component {
        public:
            explicit Player(std::shared_ptr<GameObject> gameObject);
            explicit Player(std::shared_ptr<GameObject> gameObject, std::string path);
            ~Player() = default;

            void onUpdate() override;
            void onDestroy() override;
            void onGameQuit() override;

            void setPath(std::string const &path);

            void addPerk(std::string const &name);
            void removePerk(std::string const &name);

        protected:
        private:
            // Variables
            Tools::Vector3 _lastPos;
            std::string _path;
            std::vector<std::string> _perks;

            // Functions
            void init(std::shared_ptr<GameObject> gameObject);
            void shoot(Tools::Vector3 pos, Tools::Vector2 direction);
            void test(Tools::Vector3 cPos);
            UI::Image &getImage();
            void playSound(std::string const &path);

        };

    } // KapEngine
} // RType

#endif //RTYPE_PLAYER_HPP

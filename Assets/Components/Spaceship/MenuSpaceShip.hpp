/*
** EPITECH PROJECT, 2022
** RType
** File description:
** MenuSpaceShip
*/

#ifndef MENUSPACESHIP_HPP_
#define MENUSPACESHIP_HPP_

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {

    class MenuSpaceShip : public KapEngine::Component {
        public:
            MenuSpaceShip(std::shared_ptr<KapEngine::GameObject> go);
            ~MenuSpaceShip();

            void onUpdate() override;
            void onAwake() override;

        protected:
        private:
            void foundImage();
            std::shared_ptr<KapEngine::GameObject> _img;
            std::vector<std::string> _pathes;
            int lastId = 0;
    };

}

#endif /* !MENUSPACESHIP_HPP_ */

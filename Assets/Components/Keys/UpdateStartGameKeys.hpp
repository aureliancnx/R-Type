/*
** EPITECH PROJECT, 2022
** RType
** File description:
** UpdateStartGameKeys
*/

#ifndef UPDATESTARTGAMEKEYS_HPP_
#define UPDATESTARTGAMEKEYS_HPP_

#include "KapEngine.hpp"
#include "KapEngineEvents.hpp"

using namespace KapEngine;

namespace RType {

    class UpdateStartGameKeys : public Component {
        public:
            UpdateStartGameKeys(std::shared_ptr<GameObject> go);
            ~UpdateStartGameKeys();

            void checkInputs();

        protected:
        private:
            Events::Input::Axis _baseAxisVert;
            Events::Input::Axis _baseAxisHor;
            Events::Input::Axis _baseAxisShoot;

            bool setValueSaved(std::string const& name, Events::Key &key);
    };

}

#endif /* !UPDATESTARTGAMEKEYS_HPP_ */

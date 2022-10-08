/*
** EPITECH PROJECT, 2022
** RType
** File description:
** KeySelector
*/

#ifndef KEYSELECTOR_HPP_
#define KEYSELECTOR_HPP_

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineEvents.hpp"

using namespace KapEngine;

namespace RType {

    class KeySelector : public Component {
        public:
            KeySelector(std::shared_ptr<GameObject> go);
            ~KeySelector();

            void onUpdate() override;

            bool keySelected(Events::Key &key);

            void selectKey();

        protected:
        private:
            Events::Key _selected;
            bool _check = false;
    };

}

#endif /* !KEYSELECTOR_HPP_ */

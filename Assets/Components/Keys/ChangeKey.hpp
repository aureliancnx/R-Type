/*
** EPITECH PROJECT, 2022
** RType
** File description:
** ChangeKey
*/

#ifndef CHANGEKEY_HPP_
#define CHANGEKEY_HPP_

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineEvents.hpp"

using namespace KapEngine;

namespace RType {

    class ChangeKey : public Component {
      public:
        ChangeKey(std::shared_ptr<GameObject> go);
        ~ChangeKey();

        void onAwake() override;
        void onUpdate() override;

        void setCanvasSettings(std::size_t id) { _idSettings = id; }
        void setCanvasInputSentence(std::size_t id) { _idInput = id; }

        void startSelect(std::string const &prefName);

      protected:
      private:
        std::size_t _idSettings = 0;
        std::size_t _idInput = 0;
        bool _startSelect = false;
        std::string _prefName = "";

        void displayInputs();
        void displaySettings();
    };

} // namespace RType

#endif /* !CHANGEKEY_HPP_ */

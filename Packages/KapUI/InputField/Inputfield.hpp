/*
** EPITECH PROJECT, 2022
** RType2
** File description:
** Inputfield
*/

#ifndef INPUTFIELD_HPP_
#define INPUTFIELD_HPP_

#include "KapEngine.hpp"

namespace KapEngine
{

    namespace UI
    {

        class Inputfield : public Component
        {
          public:
            enum InputType
            {
                TEXT,
                NUMBER,
                PASSWORD,
                IPV4,
                IPV6,
            };

            Inputfield(std::shared_ptr<GameObject> go);
            ~Inputfield();

            void onFixedUpdate() override;

            void onMouseEnter() override;
            void onMouseStay() override;
            void onMouseExit() override;

            void setPlaceholderText(std::string const &text);

            void setInputType(InputType type) { _type = type; }

          protected:
          private:
            bool __stringIsNumber(std::string const &str)
            {
                for (std::size_t i = 0; i < str.size(); i++)
                {
                    if (str[i] < '0' || str[i] > '9')
                        return false;
                }
                return true;
            }

            std::string __getInput();
            void __init(std::shared_ptr<GameObject> go);
            void __updateTexts();
            std::string __getFormatedText() const;

            bool _hovered = false;
            bool _clicked = false;

            InputType _type = InputType::TEXT;

            std::string _content = "";
        };

    } // namespace UI

} // namespace KapEngine

#endif /* !INPUTFIELD_HPP_ */

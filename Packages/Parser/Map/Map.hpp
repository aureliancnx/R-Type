/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Map.hpp
*/

#ifndef RTYPE_MAP_HPP
#define RTYPE_MAP_HPP

#include "../Summon/Summon.hpp"

namespace RType {
    namespace Parser {

        class Map {
            public:
                Map(const std::string& path);
                ~Map();

            private:
                // Variables
                std::string _name;
                std::vector<std::string> _author;
                std::string _date;
                int _difficulty;
                std::string _description;
                std::string _background;

                std::vector<Summon> _summons;

                // Methods
                void parse(const std::string& path);

        };

    } // RType
} // Parser

#endif //RTYPE_MAP_HPP

/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Map.hpp
*/

#ifndef RTYPE_MAP_HPP
#define RTYPE_MAP_HPP

#include <sstream>
#include "../Summon/Summon.hpp"

namespace RType {
    namespace Parser {

        class Map {
          public:
            Map(const std::string &path);
            ~Map();

            void display();

          private:
            // Variables
            std::ifstream map;
            std::string _name;
            std::vector<std::string> _author;
            std::string _date;
            int _difficulty;
            std::string _description;
            std::string _background;

            std::vector<Summon> _summons;

            // Methods
            void parse();
            void parseHeader(const std::string &line);
            void parseSummons(const std::string &line);
            void openMap(const std::string &path);
            void closeMap();

            std::vector<std::string> split(const std::string &str, const std::string &delim);
        };

    } // namespace Parser
} // namespace RType

#endif // RTYPE_MAP_HPP

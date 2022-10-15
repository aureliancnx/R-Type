/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Map.cpp
*/

#include "Map.hpp"

namespace RType {
    namespace Parser {
        Map::Map(const std::string &path) {
            openMap(path);
            parse();
            closeMap();
        }

        Map::~Map() = default;

        void Map::parse() {
            std::string line;

            while (std::getline(map, line)) {
                if (line[0] == '#')
                    parseHeader(line);
                else if (line.empty())
                    continue;
                else
                    parseSummons(line);
            }
        }

        void Map::parseHeader(const std::string &line) {
            std::string headerElement[6] = {"Name", "Authors", "Date", "Difficulty", "Description", "Background"};

            for (auto elem: headerElement) {
                if (line.find(elem) != std::string::npos) {
                    if (elem == "Name")
                        _name = line.substr(line.find(elem) + elem.size() + 2);
                    else if (elem == "Authors")
                        _author.push_back(line.substr(line.find(elem) + elem.size() + 2));
                    else if (elem == "Date")
                        _date = line.substr(line.find(elem) + elem.size() + 2);
                    else if (elem == "Difficulty")
                        _difficulty = std::stoi(line.substr(line.find(elem) + elem.size() + 2));
                    else if (elem == "Description")
                        _description = line.substr(line.find(elem) + elem.size() + 2);
                    else if (elem == "Background")
                        _background = line.substr(line.find(elem) + elem.size() + 2);
                }
            }
        }

        void Map::openMap(const std::string &path) {
            map.open(path);
            if (!map.is_open()) {
                std::cerr << "Error: Can't open map file" << std::endl;
                closeMap();
                exit(84);
            }
        }

        void Map::closeMap() {
            map.close();
        }

        void Map::display() {
            std::cout << "Name: " << _name << std::endl;
            std::cout << "Authors: ";
            for (auto author: _author)
                std::cout << author << " ";
            std::cout << std::endl;
            std::cout << "Date: " << _date << std::endl;
            std::cout << "Difficulty: " << 0 << std::endl;
            std::cout << "Description: " << _description << std::endl;
            std::cout << "Background: " << _background << std::endl;
        }

        std::vector<std::string> Map::split(const std::string &str, const std::string &delim) {
            std::stringstream ss(str);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, delim[0]))
                tokens.push_back(token);
            return tokens;
        }

    } // RType
} // Parser
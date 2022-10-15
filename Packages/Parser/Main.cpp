/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Main.cpp
*/

#include "Parser.hpp"
#include "Map/Map.hpp"

int main() {
    RType::Parser::Parser parser;
    parser.setPath("../../Maps/");
    parser.run();

    auto path = parser.getFilesPath()[0];

    auto map = RType::Parser::Map(path);
    map.display();

    return 0;
}
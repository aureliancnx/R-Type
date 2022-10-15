/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Parser.hpp
*/

#ifndef RTYPE_PARSER_HPP
#define RTYPE_PARSER_HPP

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

namespace RType {
    namespace Parser {

        class Parser {
            public:
                Parser();
                ~Parser();

                void run();

                bool hasError() const;
                std::vector<std::string> getFilesError() const;
                std::vector<std::string> getFilesPath() const;

            private:
                // Variables
                bool _hasError;
                int _nbFiles;
                std::vector<std::string> _filesPath;
                std::vector<std::string> _filesError;

                // Methods
                bool directoryExist();
                void getFiles();
        };

    } // RType
} // Parser

#endif //RTYPE_PARSER_HPP

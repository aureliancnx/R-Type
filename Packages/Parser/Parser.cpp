/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

#include <iomanip>

namespace RType {
    namespace Parser {

        Parser::Parser() {
            _hasError = false;
            _nbFiles = 0;
        }

        Parser::~Parser() = default;

        void Parser::run() {
            if (!directoryExist())
                return;
            getFiles();
            std::cout << "Number of file: " << _nbFiles << std::endl;
            std::cout << "Paths files: " << std::endl;
            for (auto &file : _filesPath) {
                std::cout << file << std::endl;
            }
        }

        void Parser::getFiles() {
            for (const auto &entry : std::filesystem::directory_iterator("Maps/")) {
                if (entry.path().extension() == ".rtype") {
                    _filesPath.push_back(entry.path());
                    _nbFiles++;
                }
            }
        }

        bool Parser::directoryExist() {
            return std::filesystem::is_directory("Maps/");
        }

        bool Parser::hasError() const {
            return _hasError;
        }

        std::vector<std::string> Parser::getFilesError() const {
            return _filesError;
        }

        std::vector<std::string> Parser::getFilesPath() const {
            return _filesPath;
        }

    } // RType
} // Parser
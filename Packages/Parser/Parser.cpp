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
            getHeaderFile();
        }

        void Parser::getFiles() {
            for (const auto &entry : std::filesystem::directory_iterator("Maps/")) {
                if (entry.path().extension() == ".rtype") {
                    _filesPath.push_back(entry.path());
                    _nbFiles++;
                }
            }
        }

        void Parser::getHeaderFile() {
            for (std::string file: _filesPath) {
                std::ifstream fileStream(file);
                if (!fileStream.is_open()) {
                    _hasError = true;
                    _filesError.push_back(file);
                    continue;
                }
                std::vector<std::string> lines;
                std::string line;

                try {
                    while (std::getline(fileStream, line)) {
                        if (line.at(0) == '#')
                            lines.push_back(line);
                    }
                } catch (std::exception &e) {
                    _hasError = true;
                    _filesError.push_back(file);
                }

                if (!checkHeaderFile(lines)) {
                    _hasError = true;
                    _filesError.push_back(file);
                    std::cout << "Error in file: " << file << std::endl;
                }
                fileStream.close();
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
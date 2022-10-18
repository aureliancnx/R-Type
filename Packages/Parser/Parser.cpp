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

        Parser::Parser(const std::string& path) {
            _path = path;
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

        void Parser::setPath(const std::string &path) {
            _path = path;
        }

        void Parser::getFiles() {
            for (const auto &entry : std::filesystem::directory_iterator(_path)) {
                if (entry.path().extension() == ".rtype") {
                    _filesPath.push_back(entry.path().string());
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
                    fileStream.close();
                    continue;
                }
                std::vector<std::string> lines;
                lines.push_back(file);
                std::string line;

                try {
                    while (std::getline(fileStream, line)) {
                        if (line[0] != '#')
                            break;
                        lines.push_back(line);
                    }
                } catch (std::exception &e) {
                    _hasError = true;
                    _filesError.push_back(file);
                    _errorsInFiles[file] = e.what();
                    continue;
                }

                if (!checkHeaderFile(lines)) {
                    _hasError = true;
                    _filesError.push_back(file);
                }
                fileStream.close();
            }
        }

        bool Parser::checkHeaderFile(std::vector<std::string> header) {
            std::string mandatory[5] = {"RType", "Name:", "Authors:", "Date:", "Difficulty:"};
            int nbMandatory = 0;
            for (std::string line: header) {
                for (std::string mandatoryLine: mandatory) {
                    if (line.find(mandatoryLine) != std::string::npos) {
                        nbMandatory++;
                        break;
                    }
                }
            }
            if (nbMandatory != 5) {
                _errorsInFiles[header.at(0)] = "missing mandatory line";
                return false;
            }
            return true;
        }

        bool Parser::directoryExist() {
            return std::filesystem::is_directory(_path);
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

        std::map<std::string, std::string> Parser::getErrorsInFiles() const {
            return _errorsInFiles;
        }

    } // RType
} // Parser

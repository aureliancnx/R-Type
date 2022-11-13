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
#include <fstream>
#include <map>

namespace RType {
    namespace Parser {

        class Parser {
          public:
            Parser(const std::string &path = "Maps/");
            ~Parser();

            void run();

            void setPath(const std::string &path);

            bool hasError() const;
            std::vector<std::string> getFilesError() const;
            std::vector<std::string> getFilesPath() const;
            std::map<std::string, std::string> getErrorsInFiles() const;

          private:
            // Variables
            std::string _path;
            bool _hasError;
            int _nbFiles;
            std::vector<std::string> _filesPath;
            std::vector<std::string> _filesError;
            std::map<std::string, std::string> _errorsInFiles;

            // Methods
            bool directoryExist();
            void getFiles();
            void getHeaderFile();
            bool checkHeaderFile(std::vector<std::string> header);
            void hasMandatory();
        };

    } // namespace Parser
} // namespace RType

#endif // RTYPE_PARSER_HPP

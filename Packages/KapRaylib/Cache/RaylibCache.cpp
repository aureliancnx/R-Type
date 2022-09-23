/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibCache
*/

#include "RaylibCache.hpp"
#include "Encapsulation/RaylibEncapsulation.hpp"
#include <iostream>

void KapEngine::Graphical::Raylib::Cache::ImageCache::init(std::string const& imagePath) {
    pathImage = imagePath;
    img = encap.__loadImage(pathImage);
        std::cout << "                            Load new image" << std::endl;
}

void KapEngine::Graphical::Raylib::Cache::ImageCache::clear() {
    if (pathImage == "")
        return;
    encap.__unloadImage(img);
    pathImage = "";
}

KapEngine::Graphical::Raylib::Cache::FontCache::FontCache(RaylibEncapsulation &e, std::string const& path) : RaylibCache(e), _path(path) {
    if (_path != "") {
        _font = encap.__loadFont(_path);
        std::cout << "                            Load new font" << std::endl;
    }
}

void KapEngine::Graphical::Raylib::Cache::FontCache::clear() {
    if (_path == "")
        return;
    _path = "";
    encap.__unloadFont(_font);
}

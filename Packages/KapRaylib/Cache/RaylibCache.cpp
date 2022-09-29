/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibCache
*/

#include "RaylibCache.hpp"
#include "Encapsulation/RaylibEncapsulation.hpp"
#include <iostream>
#include "Debug.hpp"

void KapEngine::Graphical::Raylib::Cache::ImageCache::init(std::string const& imagePath) {
    pathImage = imagePath;
    if (pathImage != "") {
        img = encap.__loadImage(pathImage);
        Debug::log("[RAYLIB CACHE] Load new image");
    }
}

void KapEngine::Graphical::Raylib::Cache::ImageCache::clear() {
    if (pathImage == "")
        return;
    encap.__unloadImage(img);
    Debug::log("[RAYLIB CACHE] Clear image : " + pathImage);
    pathImage = "";
}

KapEngine::Graphical::Raylib::Cache::FontCache::FontCache(RaylibEncapsulation &e, std::string const& path) : RaylibCache(e), _path(path) {
    if (_path != "") {
        _font = encap.__loadFont(_path);
        Debug::log("[RAYLIB CACHE] Load new font");
    }
}

void KapEngine::Graphical::Raylib::Cache::FontCache::clear() {
    if (_path == "")
        return;
    Debug::log("[RAYLIB CACHE] Clear font : " + _path);
    _path = "";
    encap.__unloadFont(_font);
}

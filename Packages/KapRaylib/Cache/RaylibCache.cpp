/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibCache
*/

#include "RaylibCache.hpp"
#include "Encapsulation/RaylibEncapsulation.hpp"
#include <iostream>
#include "KapEngineDebug.hpp"

void KapEngine::Graphical::Raylib::Cache::ImageCache::init(std::string const& imagePath) {
    pathImage = imagePath;
    if (pathImage != "") {
        img = encap.__loadImage(pathImage);
        DEBUG_LOG("[RAYLIB CACHE] Load new image");
    }
}

void KapEngine::Graphical::Raylib::Cache::ImageCache::clear() {
    if (pathImage == "")
        return;
    encap.__unloadImage(img);
    DEBUG_LOG("[RAYLIB CACHE] Clear image : " + pathImage);
    pathImage = "";
}

KapEngine::Graphical::Raylib::Cache::FontCache::FontCache(RaylibEncapsulation &e, std::string const& path) : RaylibCache(e), _path(path) {
    if (_path != "") {
        _font = encap.__loadFont(_path);
        DEBUG_LOG("[RAYLIB CACHE] Load new font");
    }
}

void KapEngine::Graphical::Raylib::Cache::FontCache::clear() {
    if (_path == "")
        return;
    DEBUG_LOG("[RAYLIB CACHE] Clear font : " + _path);
    _path = "";
    encap.__unloadFont(_font);
}

KapEngine::Graphical::Raylib::Cache::MusicCache::MusicCache(RaylibEncapsulation &e, std::string const& path) : RaylibCache(e), _path(path) {
    if (_path != "") {
        _music = encap.__loadMusic(_path);
        DEBUG_LOG("[RAYLIB CACHE] Load new music");
    }
}

void KapEngine::Graphical::Raylib::Cache::MusicCache::clear() {
    if (_path == "")
        return;
    DEBUG_LOG("[RAYLIB CACHE] Clear music : " + _path);
    _path = "";
    encap.__unloadMusic(_music);
}

KapEngine::Graphical::Raylib::Cache::SoundCache::SoundCache(RaylibEncapsulation &e, std::string const& path) : RaylibCache(e), _path(path) {
    if (_path != "") {
        _sound = encap.__loadSound(_path);
        DEBUG_LOG("[RAYLIB CACHE] Load new sound");
    }
}

void KapEngine::Graphical::Raylib::Cache::SoundCache::clear() {
    if (_path == "")
        return;
    DEBUG_LOG("[RAYLIB CACHE] Clear sound : " + _path);
    _path = "";
    encap.__unloadSound(_sound);
}

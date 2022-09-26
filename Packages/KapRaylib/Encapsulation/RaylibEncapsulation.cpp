/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibEncapsulation
*/

#include "RaylibEncapsulation.hpp"
#include "Errors.hpp"
#include "Debug.hpp"
#include <iostream>

void KapEngine::Graphical::Raylib::RaylibEncapsulation::unloadFont(std::string const& path) {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i]->getName() == "Font") {
            auto _fcache = (Cache::FontCache *)_cache[i].get();
            if (_fcache->getpath() == path) {
                _cache[i]->clear();
                _cache.erase(_cache.begin() + i);
                return;
            }
        }
    }
}

void KapEngine::Graphical::Raylib::RaylibEncapsulation::unloadAllFonts() {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i]->getName() == "Font") {
            _cache[i]->clear();
            _cache.erase(_cache.begin() + i);
            i--;
        }
    }
}

void KapEngine::Graphical::Raylib::RaylibEncapsulation::loadFont(std::string const& path) {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i]->getName() == "Font") {
            auto fcache = (Cache::FontCache *)_cache[i].get();
            if (fcache->getpath() == path) {
                //font already exists
                return;
            }
        }
    }
    //create new font
    auto nFont = std::make_shared<Cache::FontCache>(*this, path);
    _cache.push_back(nFont);
}

Font &KapEngine::Graphical::Raylib::RaylibEncapsulation::getFont(std::string const& path, bool alreadyTry) {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i]->getName() == "Font") {
            auto fcache = (Cache::FontCache &)*_cache[i];
            if (fcache.getpath() == path) {
                //font found
                return fcache.getFont();
            }
        }
    }
    //font does not found
    if (alreadyTry) {
        throw Errors::GraphicalSystemError("No font found: " + path);
    } else {
        loadFont(path);
        return getFont(path, true);
    }
}

void KapEngine::Graphical::Raylib::RaylibEncapsulation::clearCache() {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        _cache[i]->clear();
    }
    _cache.clear();
    std::cout << "Cache cleared !" << std::endl;
}

void KapEngine::Graphical::Raylib::RaylibEncapsulation::__drawTexture(std::string const& imagePath, float posX, float posY, float width, float heigth, Rectangle rect, float rot, Color col) {
    Image img;
    try {
        img = getImage(imagePath);
    } catch(...) {
        return;
    }
    __imageCrop(&img, rect);
    __setImageSize(&img, {width, heigth});
    Texture2D texture = __getTextureFromImage(img);
    _cacheTexture.push_back(texture);
    DrawTextureV(texture, {posX, posY}, col);
    Debug::log("Draw image: {" + std::to_string(posX) + "; " + std::to_string(posY) + "}, size: {" + std::to_string(width) + "; " + std::to_string(heigth) + "}");
}

void KapEngine::Graphical::Raylib::RaylibEncapsulation::loadImage(std::string const& imagePath) {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i]->getName() == "Image") {
            auto img = (Cache::ImageCache *)_cache[i].get();
            Debug::warning("[RAYLIB] image->[" + img->getPath() + "]");
            if (img->getPath() == imagePath)
                return;
        }
    }
    Debug::warning("[RAYLIB] create image: " + imagePath);
    auto nImg = std::make_shared<Cache::ImageCache>(*this);
    nImg->init(imagePath);
    _cache.push_back(nImg);
}

Image &KapEngine::Graphical::Raylib::RaylibEncapsulation::getImage(std::string const& imagePath, bool alreadyTry) {
    for (std::size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i]->getName() == "Image") {
            auto img = (Cache::ImageCache *)_cache[i].get();
            if (img->getPath() == imagePath)
                return img->getImage();
        }
    }

    if (alreadyTry) {
        Debug::error("[RAYLIB] : no image found: " + imagePath);
        throw Errors::GraphicalSystemError("No image found: " + imagePath);
    }
    loadImage(imagePath);
    return getImage(imagePath, true);
}

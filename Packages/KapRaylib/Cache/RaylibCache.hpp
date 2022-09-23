/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RaylibCache
*/

#ifndef RAYLIBCACHE_HPP_
#define RAYLIBCACHE_HPP_

#include "raylib.h"
#include <string>

namespace KapEngine {
    namespace Graphical {

        namespace Raylib {

            class RaylibEncapsulation;

        }
    }
}

namespace KapEngine {
    namespace Graphical {

        namespace Raylib {

            namespace Cache {

                class IRaylibCache {
                    public:
                        virtual ~IRaylibCache() {}

                        virtual void clear() = 0;

                    protected:
                    private:
                };

                class RaylibCache : public IRaylibCache {
                    public:
                        RaylibCache(RaylibEncapsulation &e) : encap(e) {}
                        ~RaylibCache() {}

                        virtual void clear() {}
                        virtual std::string getName() const { return ""; }
                    protected:
                        RaylibEncapsulation &encap;
                };

                class ImageCache : public RaylibCache {
                    public:
                        ImageCache(RaylibEncapsulation &e) : RaylibCache(e) {}
                        ~ImageCache() {}

                        bool operator==(ImageCache const& c) {
                            return (pathImage == c.pathImage);
                        }

                        std::string getName() const override {
                            return "Image";
                        }

                        void init(std::string const& imagePath);

                        Image getImage() const {
                            return img;
                        }

                        void clear() override;

                    private:
                        std::string pathImage;
                        Image img;
                };

                class FontCache : public RaylibCache {
                    public:
                        FontCache(RaylibEncapsulation &e, std::string const& path);
                        ~FontCache() {}

                        bool operator==(FontCache const& font) {
                            return (_path == font._path);
                        }

                        std::string getName() const override {
                            return "Font";
                        }

                        std::string getpath() const {
                            return _path;
                        }

                        Font &getFont() {
                            return _font;
                        }

                        void clear() override;

                    private:
                        std::string _path;
                        Font _font;
                
                };

            }

        }

    }
}

#endif /* !RAYLIBCACHE_HPP_ */

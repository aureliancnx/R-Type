#pragma once

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace RType {
    class Shoot : public KapEngine::Component {
        private:
        std::string _path;
        KapEngine::Tools::Rectangle _rect;
        KapEngine::Tools::Vector3 _pos;
        KapEngine::Tools::Vector3 _cPos;
        KapEngine::Tools::Vector2 _direction;

        public:
        Shoot(std::shared_ptr<KapEngine::GameObject> gameObject);
        Shoot(std::shared_ptr<KapEngine::GameObject> gameObject, const std::string &path, KapEngine::Tools::Rectangle rect);
        ~Shoot() = default;

        void onFixedUpdate() override;

        void setPath(const std::string &path);
        void setRectangle(const KapEngine::Tools::Rectangle &rect);
        void setDirection(const KapEngine::Tools::Vector2 &direction);
        void setPos(const KapEngine::Tools::Vector2 &pos);

        void shoot(const KapEngine::Tools::Vector2 &direction, const KapEngine::Tools::Vector2 &pos);

        private:
        void init(std::shared_ptr<KapEngine::GameObject> gameObject);
        KapEngine::UI::Image &getImage();
    };
}

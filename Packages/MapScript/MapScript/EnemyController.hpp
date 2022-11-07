#pragma once

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {
    class EnemyController : public KapMirror::NetworkComponent {
      private:
        int hp = 20;

      public:
        explicit EnemyController(std::shared_ptr<KapEngine::GameObject> _gameObject);
        ~EnemyController() = default;

        void setHp(int _hp);
    };
} // namespace RType

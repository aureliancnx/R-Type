#include "EnemyController.hpp"

using namespace RType;

EnemyController::EnemyController(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::NetworkComponent(_gameObject, "Enemy") {
    addRequireComponent("Image");
}

void EnemyController::setHp(int _hp) { hp = _hp; }

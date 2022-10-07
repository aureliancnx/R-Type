#include "Player.hpp"

using namespace RType;

Player::Player(std::shared_ptr<KapEngine::GameObject> _gameObject) : KapMirror::Experimental::NetworkComponent(_gameObject, "Player") {
}

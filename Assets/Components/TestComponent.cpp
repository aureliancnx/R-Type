/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TestComponent
*/

#include "TestComponent.hpp"

#include "Key.hpp"
#include "Debug.hpp"
#include "Vectors.hpp"

RType::Component::TestComponent::TestComponent(std::shared_ptr<KapEngine::GameObject> go) : Component(go, "Test", 2) {}

RType::Component::TestComponent::~TestComponent() {}

void RType::Component::TestComponent::onUpdate() {
    KapEngine::Tools::Vector2 vec;

    vec.setX(getInput().getAxis("Horizontal"));
    vec.setY(getInput().getAxis("Vertical"));

    if (vec == _lastInputs)
        return;
    _lastInputs = vec;
    KapEngine::Debug::log("Player: H=" + std::to_string(vec.getX()) + ", V=" + std::to_string(vec.getY()));
}

/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TestComponent
*/

#include "TestComponent.hpp"

#include "Key.hpp"
#include "Debug.hpp"

RType::Component::TestComponent::TestComponent(std::shared_ptr<KapEngine::GameObject> go) : Component(go, "Test") {}

RType::Component::TestComponent::~TestComponent() {}

void RType::Component::TestComponent::onUpdate() {
    if (getInput().getKeyDown(KapEngine::Events::Key::UP))
        KapEngine::Debug::log("ARROW UP");
    if (getInput().getKeyDown(KapEngine::Events::Key::DOWN))
        KapEngine::Debug::log("ARROW DOWN");
    if (getInput().getKeyDown(KapEngine::Events::Key::LEFT))
        KapEngine::Debug::log("ARROW LEFT");
    if (getInput().getKeyDown(KapEngine::Events::Key::RIGHT))
        KapEngine::Debug::log("ARROW RIGTH");
}

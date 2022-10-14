/*
** EPITECH PROJECT, 2022
** RType
** File description:
** ParalaxPrefabs.cpp
*/

#include "ParalaxPrefabs.hpp"

using namespace RType;

void ParalaxPrefabs::registerGalaxyParalaxPrefab(KapEngine::KEngine& engine) {
    engine.getPrefabManager()->createPrefab("ParalaxGalaxy", [](KapEngine::SceneManagement::Scene& scene) {
        auto paralax = scene.createGameObject("Paralax");
        auto paralaxCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "ParalaxCanvas");

        try {
            auto &tr = paralax->getComponent<KapEngine::Transform>();
            tr.setParent(paralaxCanvas);
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to get Transform of parent");
        }

        auto galaxy1 = KapEngine::UI::UiFactory::createImage(scene, "galaxy1");
        auto galaxy2 = KapEngine::UI::UiFactory::createImage(scene, "galaxy2");

        auto &canvas = paralaxCanvas->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        canvas.setScreenCompare({272, 160});

        try {
            auto &img = galaxy1->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-back.png");

            auto &transform = galaxy1->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
        } catch (...) {}

        try {
            auto &img = galaxy2->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-back.png");

            auto &transform = galaxy2->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
            transform.setPosition({271 * 1, 0, 0});
        } catch (...) {}

        // Animation
        auto paralaxAnimation = std::make_shared<RType::ParalaxAnimation>(paralaxCanvas, .05, 272);
        paralax->addComponent(paralaxAnimation);

        auto animator = std::make_shared<KapEngine::Animator>(paralax);
        paralax->addComponent(animator);
        animator->addAnim(paralaxAnimation, "idle");
        animator->addLink("idle", "idle");

        return paralax;
    });
}

void ParalaxPrefabs::registerStarsParalaxPrefab(KapEngine::KEngine &engine) {
    engine.getPrefabManager()->createPrefab("ParalaxStars", [](KapEngine::SceneManagement::Scene& scene) {
        auto paralax = scene.createGameObject("Paralax");
        auto paralaxCanvas = KapEngine::UI::UiFactory::createCanvas(scene, "ParalaxCanvas");

        try {
            auto &tr = paralax->getComponent<KapEngine::Transform>();
            tr.setParent(paralaxCanvas);
        } catch(...) {
            KAP_DEBUG_ERROR("Failed to get Transform of parent");
        }

        auto  stars1 = KapEngine::UI::UiFactory::createImage(scene, "stars1");
        auto stars2 = KapEngine::UI::UiFactory::createImage(scene, "stars2");

        auto &canvas = paralaxCanvas->getComponent<KapEngine::UI::Canvas>();
        canvas.setResizeType(KapEngine::UI::Canvas::RESIZE_WITH_SCREEN);
        canvas.setScreenCompare({272, 160});

        try {
            auto &img = stars1->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-stars.png");

            auto &transform = stars1->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
        } catch (...) {}

        try {
            auto &img = stars2->getComponent<KapEngine::UI::Image>();
            img.setRectangle({0, 0, 272, 160});
            img.setPathSprite("Assets/Textures/Background/bg-stars.png");

            auto &transform = stars2->getComponent<KapEngine::Transform>();
            transform.setParent(paralax);
            transform.setScale({271, 160, 0});
            transform.setPosition({271 * 1, 0, 0});
        } catch (...) {}

        // Animation
        auto paralaxAnimation = std::make_shared<RType::ParalaxAnimation>(paralaxCanvas, .5, 272);
        paralax->addComponent(paralaxAnimation);

        auto animator = std::make_shared<KapEngine::Animator>(paralax);
        paralax->addComponent(animator);
        animator->addAnim(paralaxAnimation, "idle");
        animator->addLink("idle", "idle");

        return paralax;
    });
}
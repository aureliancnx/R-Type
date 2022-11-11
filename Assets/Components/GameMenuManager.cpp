/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameMenuManager
*/

#include "GameMenuManager.hpp"

#include "Animations/SpriteAnimation.hpp"

#include "KapEngineUi.hpp"
#include "KapUI/KapUI.hpp"

using namespace KapEngine;

RType::GameMenuManager::GameMenuManager(std::shared_ptr<GameObject> go) : KapMirror::NetworkComponent(go, "GameMenuManager") {
    addRequireComponent("Canvas");
    auto screenSize = getGameObject().getEngine().getScreenSize();

    float sizeY = 90;
    getTransform().setScale({screenSize.getX(), sizeY, 0});
    getTransform().setPosition({0, screenSize.getY() - sizeY, 0});
    if (!getGameObject().hasComponent<UI::Canvas>()) {
        auto canvas = std::make_shared<UI::Canvas>(getGameObject().getScene().getGameObject(getGameObject().getId()));
        getGameObject().addComponent(canvas);
        canvas->setResizeType(UI::Canvas::ResizyngType::RESIZE_WITH_SCREEN);
    }
    go->setName("MenuManager");
}

void RType::GameMenuManager::onStart() { initMainMenu(); }

void RType::GameMenuManager::displayMainMenu() {
    if (mainMenu.use_count() != 0) {
        mainMenu->setActive(true);
    } else {
        initMainMenu();
    }
}

void RType::GameMenuManager::initMainMenu(bool local) {
    // menu set
    mainMenu = getGameObject().getScene().createGameObject("MainMenu");
    mainMenu->getComponent<Transform>().setParent(getGameObject().getId());

    Tools::Vector3 btnSize = {80.f / getGameObject().getEngine().getScreenSize().getX(), 80.f / 90.f, 0};
    Tools::Vector3 btnBasePos = {10, 5, 0};

    KAP_DEBUG_LOG("Button size: " + btnSize.to_string());

    initBackground(mainMenu);

    auto& scene = getGameObject().getScene();

    // create quit button
    {
        std::shared_ptr<GameObject> btn;

        if (local) {
            btn = initButton(mainMenu, "QuitBtn", "", [this]() { getGameObject().getEngine().getSceneManager()->loadScene(1); },
                             "Assets/Textures/Icons/logout.png", {0, 0, 512, 512});
        } else if (isClient()) {
            btn = initButton(mainMenu, "QuitBtn", "",
                             [this]() {
                                 getClient()->disconnect();
                                 getGameObject().getEngine().getSceneManager()->loadScene(1);
                             },
                             "Assets/Textures/Icons/logout.png", {0, 0, 512, 512});
        }

        auto& tr = btn->getComponent<Transform>();

        tr.setScale(btnSize);
        tr.setPosition(btnBasePos);
    }

    // create hearts
    for (std::size_t i = 0; i < 3; i++) {
        std::string goName = "Heart" + std::to_string(i);
        Tools::Vector3 calculatedPos = btnBasePos;
        calculatedPos.setX(calculatedPos.getX() + 80.0f * i * 1.05f);
        calculatedPos.setX(calculatedPos.getX() + 80.0f * 1.5f);

        auto heart = UI::UiFactory::createImage(scene, goName, "Assets/Textures/heart.png", {0, 0, 512, 512});

        Time::ETime duration;
        duration.setSeconds(0.5f);

        auto heartOn = std::make_shared<SpriteAnimation>(heart);
        heartOn->setTiming(duration);
        heartOn->setRect({0 * 512, 0, 512, 512});
        heartOn->setNbAnimations(1);
        heart->addComponent(heartOn);

        auto heartOff = std::make_shared<SpriteAnimation>(heart);
        heartOff->setTiming(duration);
        heartOff->setRect({10 * 512, 0, 512, 512});
        heartOff->setNbAnimations(1);
        heart->addComponent(heartOff);

        auto heartAnimationOn = std::make_shared<SpriteAnimation>(heart);
        heartAnimationOn->setTiming(duration);
        heartAnimationOn->setRect({0 * 512, 0, 512, 512});
        heartAnimationOn->setNbAnimations(10);
        heart->addComponent(heartAnimationOn);

        auto heartAnimationOff = std::make_shared<SpriteAnimation>(heart);
        heartAnimationOff->setTiming(duration);
        heartAnimationOff->setRect({0 * 512, 0, 512, 512});
        heartAnimationOff->setNbAnimations(10);
        heartAnimationOff->reverseAnim(true);
        heart->addComponent(heartAnimationOff);

        auto animator = std::make_shared<Animator>(heart);
        animator->addAnim(heartOn, "On");
        animator->addAnim(heartOff, "Off");
        animator->addAnim(heartAnimationOn, "AnimationOn");
        animator->addAnim(heartAnimationOn, "AnimationOff");

        animator->addLink("On", "AnimationOn", "OFF");
        animator->addLink("AnimationOn", "Off");
        animator->addLink("Off", "AnimationOff", "ON");
        animator->addLink("AnimationOff", "On");

        try {
            auto& tr = heart->getComponent<Transform>();
            tr.setParent(mainMenu->getId());
            tr.setPosition(calculatedPos);
            tr.setScale(btnSize);
        } catch (const std::exception& e) { DEBUG_ERROR("Error: " + std::string(e.what())); }
    }

    // create weapon intel
    {
        auto weaponIntel = UI::UiFactory::createImage(scene, "WeaponIntel", "Assets/Textures/Weapons/Empty.png", {0, 0, 32, 32});
        auto& tr = weaponIntel->getComponent<Transform>();
        tr.setParent(mainMenu->getId());
        Tools::Vector3 calculatedPos;
        calculatedPos.setX(getGameObject().getEngine().getScreenSize().getX() - 80.0f - 10);
        calculatedPos.setY(5);
        tr.setPosition(calculatedPos);
        tr.setScale(btnSize);
    }

    // create load missile
    {
        auto weaponIntel = UI::UiFactory::createImage(scene, "WeaponIntel", "Assets/Textures/Weapons/LoadingMissile.png", {0, 0, 31, 31});
        auto& tr = weaponIntel->getComponent<Transform>();
        tr.setParent(mainMenu->getId());
        Tools::Vector3 calculatedPos;
        calculatedPos.setX(getGameObject().getEngine().getScreenSize().getX() - 160.0f - 20);
        calculatedPos.setY(5);
        tr.setPosition(calculatedPos);
        tr.setRotation({90, 0, 0});
        tr.setScale(btnSize);

        missileAnimator = std::make_shared<Animator>(weaponIntel);
        weaponIntel->addComponent(missileAnimator);

        // idle animation missile
        {
            Time::ETime timeAnim;
            timeAnim.setSeconds(1.f);
            auto anim = std::make_shared<SpriteAnimation>(weaponIntel);
            weaponIntel->addComponent(anim);
            anim->setChangeWithY(true);
            anim->setNbAnimations(1);
            anim->setRect({0, 0, 31, 31});
            anim->setTiming(timeAnim);
            anim->loop(true);
            missileAnimator->addAnim(anim, "Idle");
        }

        // loading animation missile
        {
            float totalTimeAnim = 4.5f;
            Time::ETime timeAnim;
            timeAnim.setSeconds(totalTimeAnim / 8.f);
            auto anim = std::make_shared<SpriteAnimation>(weaponIntel);
            weaponIntel->addComponent(anim);
            anim->setNbAnimations(8, 1, 8);
            anim->setRect({0, 0, 31, 31});
            anim->setTiming(timeAnim);
            missileAnimator->addAnim(anim, "Loading");
        }

        // ready to fire misssile
        {
            Time::ETime timeAnim;
            timeAnim.setSeconds(1.f);
            auto anim = std::make_shared<SpriteAnimation>(weaponIntel);
            weaponIntel->addComponent(anim);
            anim->setChangeWithY(true);
            anim->setNbAnimations(1);
            anim->setRect({0, 7 * 31, 31, 31});
            anim->setTiming(timeAnim);
            anim->loop(true);
            missileAnimator->addAnim(anim, "Ready");
        }

        missileAnimator->addLink("Idle", "Loading", "Load");
        missileAnimator->addLink("Loading", "Ready");
        missileAnimator->addLink("Loading", "Idle", "Unload");
        missileAnimator->addLink("Ready", "Idle", "Unload");
    }
}

void RType::GameMenuManager::initBackground(std::shared_ptr<GameObject> parent) {
    auto background = parent->getScene().createGameObject("Background");
    background->getComponent<Transform>().setParent(parent->getId());
    background->getComponent<Transform>().setPosition({0, 0, 0});

    auto backgroundImage = std::make_shared<UI::Image>(background);
    Tools::Color color = Tools::Color::grey();
    color.setA(126);
    backgroundImage->setColor(color);
    background->addComponent(backgroundImage);
}

std::shared_ptr<GameObject> RType::GameMenuManager::initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text,
                                                               std::function<void()> callback, Tools::Color color, Tools::Color textColor) {
    std::shared_ptr<GameObject> button = parent->getScene().createGameObject(name);

#if IS_MAX_KAPUI_VERSION(0, 101)
    auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text);
    btnComp->setTextColor(textColor);
    btnComp->setNormalColor(color);
    btnComp->getOnClick().registerAction(callback);
#else
    KapEngine::UI::KapUiFactory::createButton(button, text, callback, color, textColor);
#endif

    try {
        button->getComponent<Transform>().setParent(parent->getId());
    } catch (...) { KAP_DEBUG_ERROR("Failled to set button " + name + " parent"); }
    return button;
}

std::shared_ptr<GameObject> RType::GameMenuManager::initButton(std::shared_ptr<GameObject> parent, std::string name, std::string text,
                                                               std::function<void()> callback, std::string pathSprite,
                                                               Tools::Rectangle rect, Tools::Color color, Tools::Color textColor) {
    std::shared_ptr<GameObject> button = parent->getScene().createGameObject(name);

#if IS_MAX_KAPUI_VERSION(0, 101)
    auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text);
    btnComp->setTextColor(textColor);
    btnComp->setNormalColor(color);
    btnComp->getOnClick().registerAction(callback);
    btnComp->setBackground(pathSprite, rect);
#else
    auto btnComp = KapEngine::UI::KapUiFactory::createButton(button, text, callback, color, textColor);
    btnComp->setBackground(pathSprite, rect);
#endif

    try {
        button->getComponent<Transform>().setParent(parent->getId());
    } catch (...) { KAP_DEBUG_ERROR("Failled to set button " + name + " parent"); }
    return button;
}

void RType::GameMenuManager::initHeart() {
#if IS_MIN_KAPENGINE_VERSION(1, 215)
    heart1 =
        KapEngine::UI::UiFactory::createImage(getGameObject().getScene(), "Heart1", "Assets/Textures/Icons/heart.png", {0, 0, 512, 512});
    heart2 =
        KapEngine::UI::UiFactory::createImage(getGameObject().getScene(), "Heart2", "Assets/Textures/Icons/heart.png", {0, 0, 512, 512});
    heart3 =
        KapEngine::UI::UiFactory::createImage(getGameObject().getScene(), "Heart3", "Assets/Textures/Icons/heart.png", {0, 0, 512, 512});
#else
    heart1 = KapEngine::UI::UiFactory::createImage(getGameObject().getScene(), "Heart1", "Assets/Textures/Icons/heart.png");
    {
        auto& img = heart1->getComponent<KapEngine::UI::Image>();
        img.setRectangle({0, 0, 512, 512});
    }

    heart2 = KapEngine::UI::UiFactory::createImage(getGameObject().getScene(), "Heart2", "Assets/Textures/Icons/heart.png");
    {
        auto& img = heart2->getComponent<KapEngine::UI::Image>();
        img.setRectangle({0, 0, 512, 512});
    }

    heart3 = KapEngine::UI::UiFactory::createImage(getGameObject().getScene(), "Heart3", "Assets/Textures/Icons/heart.png");
    {
        auto& img = heart3->getComponent<KapEngine::UI::Image>();
        img.setRectangle({0, 0, 512, 512});
    }
#endif
}

void RType::GameMenuManager::onStartClient() { initMainMenu(false); }

void RType::GameMenuManager::addLife() {
    if (_life >= 3)
        return;
    _life++;
    switch (_life) {
        case 1:
            heart1->getComponent<Animator>().setTrigger("On");
            break;
        case 2:
            heart2->getComponent<Animator>().setTrigger("On");
            break;
        case 3:
            heart3->getComponent<Animator>().setTrigger("On");
            break;
        default:
            break;
    }
}

void RType::GameMenuManager::removeLife() {
    if (_life <= 0)
        return;
    _life--;
}
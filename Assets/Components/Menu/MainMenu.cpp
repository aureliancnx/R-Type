#include "MainMenu.hpp"

using namespace RType;

MainMenu::MainMenu(KapEngine::SceneManagement::Scene& _scene) : Menu(_scene) {}

void MainMenu::init() {
    {
        auto background = KapEngine::UI::UiFactory::createImage(scene, "Background");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(background);
        imageComp->setPathSprite("Assets/Textures/background_1.png");
        imageComp->setRectangle(KapEngine::Tools::Rectangle(0, 0, 755, 448));
        background->addComponent(imageComp);

        auto& transform = background->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(0, 0, 0));
        transform.setScale(KapEngine::Tools::Vector3(720, 480, 0));
        transform.setParent(canvas);
    }

    {
        auto title = KapEngine::UI::UiFactory::createImage(scene, "Title");
        auto imageComp = std::make_shared<KapEngine::UI::Image>(title);
        imageComp->setPathSprite("Assets/Textures/R-Type.png");
        imageComp->setRectangle(KapEngine::Tools::Rectangle(0,0,762, 225));
        title->addComponent(imageComp);

        auto& transform = title->getComponent<KapEngine::Transform>();
        transform.setPosition(KapEngine::Tools::Vector3(90, 20, 0));
        transform.setScale(KapEngine::Tools::Vector3(550, 180, 0));
        transform.setParent(canvas);
    }
}

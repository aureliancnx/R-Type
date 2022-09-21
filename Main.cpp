#include "KapEngine.hpp"
#include "GameObject.hpp"
#include "ComponentTest.hpp"
#include "Factory.hpp"
#include "Entity.hpp"

int main(int ac, char **av) {
    KapEngine::KapEngine engine(false);

    try {
        KapEngine::SceneManagement::Scene &scene = engine.getSceneManager()->getCurrentScene();

        std::shared_ptr<KapEngine::GameObject> obj = KapEngine::Factory::createEmptyGameObject(scene, "ObjThreaded");

        std::shared_ptr<MyGame::ComponentTest> comp1 = std::make_shared<MyGame::ComponentTest>(obj, 2);
        std::shared_ptr<MyGame::ComponentTest> comp2 = std::make_shared<MyGame::ComponentTest>(obj, 2);
        std::shared_ptr<MyGame::ComponentTest> comp3 = std::make_shared<MyGame::ComponentTest>(obj, 4);

        obj->addComponent(comp1);
        obj->addComponent(comp2);
        obj->addComponent(comp3);
    } catch(...) {}


    // engine.run();
}

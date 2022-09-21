#include "ComponentTest.hpp"
#include "AsyncOperation.hpp"
#include "Debug.hpp"

MyGame::ComponentTest::ComponentTest(std::shared_ptr<KapEngine::GameObject> &go, int threadId) : KapEngine::Component(go, "TextComp", threadId) {
    _thread = threadId;
}

MyGame::ComponentTest::~ComponentTest() {
}

void MyGame::ComponentTest::onStart() {
    std::any comp = this;
    KapEngine::Operation::AsyncOperation async(comp);

    async.setOperationFunction([this](std::any an){
        std::cout << this->getName() << std::endl;
    });
    async.startAsync();
}

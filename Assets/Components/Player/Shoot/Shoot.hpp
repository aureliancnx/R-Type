//
// Created by kiwi on 03/10/22.
//

#ifndef RTYPE_SHOOT_HPP
#define RTYPE_SHOOT_HPP

#include "KapEngine.hpp"
#include "KapEngineDebug.hpp"
#include "KapEngineUi.hpp"

namespace KapEngine {
    namespace RType {

        class Shoot : public Component {
        public:
            explicit Shoot(std::shared_ptr<GameObject> gameObject);
            ~Shoot() = default;

            void onFixedUpdate() override;
            void animation();

        protected:
        private:
            // Variables
            Tools::Vector3 _pos;

            // Function
            void init(std::shared_ptr<GameObject> gameObject);
        };

    } // KapEngine
} // RType

#endif //RTYPE_SHOOT_HPP

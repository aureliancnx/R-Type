/*
** EPITECH PROJECT, 2022
** RType2
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include <memory>

#include "KapEngine.hpp"
#include "KapMirror/KapMirror.hpp"

namespace RType {

    class Bullet : public KapMirror::Experimental::NetworkComponent {
        public:
            Bullet(std::shared_ptr<KapEngine::GameObject> go);
            ~Bullet();
            void onStart() override;
            void onUpdate() override;

        protected:

        private:
            float speed = 2.0;
    };

}

#endif /* !BULLET_HPP_ */

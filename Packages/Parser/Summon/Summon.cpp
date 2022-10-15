/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Summon.cpp
*/

#include "Summon.hpp"

namespace RType {
    namespace Parser {

        Summon::Summon(KapEngine::Time::ETime time, int pos, std::string enemy, int health) {
            _time = time;
            _pos = pos;
            _enemy = enemy;
            _health = health;
            _hasBonus = false;
        }

        Summon::Summon(KapEngine::Time::ETime time, int pos, std::string enemy, int health, std::string bonus, int bonusPourcent) {
            _time = time;
            _pos = pos;
            _enemy = enemy;
            _health = health;
            _bonus = bonus;
            _bonusPourcent = bonusPourcent;
            _hasBonus = true;
        }

        KapEngine::Time::ETime Summon::getTime() const {
            return _time;
        }

        int Summon::getPos() const {
            return _pos;
        }

        std::string Summon::getEnemy() const {
            return _enemy;
        }

        int Summon::getHealth() const {
            return _health;
        }

        std::string Summon::getBonus() const {
            return _bonus;
        }

        int Summon::getBonusPourcent() const {
            return _bonusPourcent;
        }

        bool Summon::hasBonus() const {
            return _hasBonus;
        }
    } // RType
} // Parser
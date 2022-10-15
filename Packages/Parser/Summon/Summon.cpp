/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Summon.cpp
*/

#include "Summon.hpp"

namespace RType {
    namespace Parser {

        Summon::Summon(float time, int pos, std::string enemy, int health) {
            _time = time;
            _pos = pos;
            _enemy = enemy;
            _health = health;
            _hasBonus = false;
        }

        Summon::Summon(float time, int pos, std::string enemy, int health, std::string bonus, int bonusPourcent) {
            _time = time;
            _pos = pos;
            _enemy = enemy;
            _health = health;
            _bonus = bonus;
            _bonusPourcent = bonusPourcent;
            _hasBonus = true;
        }

        float Summon::getTime() const {
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

        std::ostream &operator<<(std::ostream &os, const RType::Parser::Summon &summon) {
            os << "\tTime: " << summon._time << std::endl;
            os << "\tPos: " << summon._pos << std::endl;
            os << "\tEnemy: " << summon._enemy << std::endl;
            os << "\tHealth: " << summon._health << std::endl;
            if (summon._hasBonus) {
                os << "\tBonus: " << summon._bonus << std::endl;
                os << "\tBonusPourcent: " << summon._bonusPourcent << std::endl;
            }
            return os;
        }
    } // RType
} // Parser
/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Summon.hpp
*/

#ifndef RTYPE_SUMMON_HPP
#define RTYPE_SUMMON_HPP

#include "KapEngine.hpp"

namespace RType {
    namespace Parser {

        class Summon {
            public:
                Summon(KapEngine::Time::ETime time, int pos, std::string enemy, int health);
                Summon(KapEngine::Time::ETime time, int pos, std::string enemy, int health, std::string bonus, int bonusPourcent);
                ~Summon() = default;

                KapEngine::Time::ETime getTime() const;
                int getPos() const;
                std::string getEnemy() const;
                int getHealth() const;
                std::string getBonus() const;
                int getBonusPourcent() const;

                bool hasBonus() const;

            private:
                KapEngine::Time::ETime _time;
                int _pos;
                std::string _enemy;
                int _health;
                std::string _bonus;
                int _bonusPourcent;

                bool _hasBonus;

        };

    } // RType
} // Parser

#endif //RTYPE_SUMMON_HPP

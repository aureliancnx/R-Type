/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Summon.hpp
*/

#ifndef RTYPE_SUMMON_HPP
#define RTYPE_SUMMON_HPP

//#include "KapEngine.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>

namespace RType {
    namespace Parser {

        class Summon {
          public:
            Summon(float time, int pos, std::string enemy, int health);
            Summon(float time, int pos, std::string enemy, int health, std::string bonus, int bonusPourcent);
            ~Summon() = default;

            float getTime() const;
            int getPos() const;
            std::string getEnemy() const;
            int getHealth() const;
            std::string getBonus() const;
            int getBonusPourcent() const;

            bool hasBonus() const;

            friend std::ostream &operator<<(std::ostream &os, const Summon &summon);

          private:
            float _time;
            int _pos;
            std::string _enemy;
            int _health;
            std::string _bonus;
            int _bonusPourcent;

            bool _hasBonus;
        };

    } // namespace Parser
} // namespace RType

#endif // RTYPE_SUMMON_HPP

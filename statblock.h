//
// Created by natha on 12/10/2023.
//

#pragma once
#include <cstdint>

typedef std::uint16_t stattype;

class StatBlock {
    stattype Strength; //0xFF
    stattype Intellect; //0xFF
    stattype Agility; //0xFF
    stattype Armor; //0xFF
    stattype ElementResistance; //0xFF


public:
    explicit StatBlock(stattype s  = 1, stattype i = 1, stattype a = 1, stattype arm = (stattype) 0, stattype elres = 0) {
        Strength = s;
        Intellect = i;
        Agility = a;
        Armor = arm;
        ElementResistance = elres;

    };

    stattype getStrength(){return Strength;}
    stattype getIntellect(){return Intellect;}
    stattype getAgility(){return Agility;}
    stattype getArmor(){return Armor;}
    stattype getElementRes(){return ElementResistance;}

    stattype setStrength(stattype statIncrease){
        return Strength + statIncrease;
    }
    stattype setIntellect(stattype statIncrease){
        return Intellect + statIncrease;
    }
    stattype setAgility(stattype statIncrease){
        return Agility + statIncrease;
    }
    stattype setArmor(stattype statIncrease){
        return Armor + statIncrease;
    }
    stattype setElementRes(stattype statIncrease){
        return ElementResistance + statIncrease;
    }

protected:
    void increaseStats(stattype s = 0, stattype i = 0, stattype a = 0, stattype arm = 0, stattype elres = 0){
        Strength += s;
        Intellect += i;
        Agility += a;
        Armor += arm;
        ElementResistance += elres;
    }
};
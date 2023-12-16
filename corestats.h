//
// Created by natha on 12/12/2023.
//

#pragma once
#include "types.h"

struct CoreStats{
    stattype Strength = 0;
    stattype Intellect= 0;
    stattype Agility= 0;
    stattype Armor= 0;
    stattype ElementResistance= 0;

    CoreStats(){
        Strength = 0;
        Intellect= 0;
        Agility= 0;
        Armor= 0;
        ElementResistance= 0;
    }

    CoreStats(stattype s, stattype i, stattype ag, stattype arm, stattype eres)
        : Strength(s), Intellect(i), Agility(ag), Armor(arm), ElementResistance(eres){
    }

    CoreStats& operator+=(const CoreStats& rhs){
        this->Strength += rhs.Strength;
        this->Intellect += rhs.Intellect;
        this->Agility += rhs.Agility;
        this->Armor += rhs.Armor;
        this->ElementResistance += rhs.ElementResistance;
        return *this;
    };

    CoreStats& operator-=(const CoreStats& rhs){
        CoreStats tmp = *this;
        this->Strength -= rhs.Strength;
        this->Intellect -= rhs.Intellect;
        this->Agility -= rhs.Agility;
        this->Armor -= rhs.Armor;
        this->ElementResistance -= rhs.ElementResistance;
        if(this->Strength > tmp.Strength){
            this->Strength = 0u;
        }
        if(this->Intellect > tmp.Intellect){
            this->Intellect = 0u;
        }
        if(this->Agility > tmp.Agility){
            this->Agility = 0u;
        }
        if(this->Armor > tmp.Armor){
            this->Armor = 0u;
        }
        if(this->ElementResistance > tmp.ElementResistance){
            this->ElementResistance = 0u;
        }
        return *this;
    };

    CoreStats& operator=(const stattype& rhs){
        this->Strength = rhs;
        this->Intellect = rhs;
        this->Agility = rhs;
        this->Armor = rhs;
        this->ElementResistance = rhs;
        return *this;
    }
};

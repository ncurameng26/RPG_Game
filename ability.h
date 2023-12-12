//
// Created by natha on 12/11/2023.
//

#pragma once
#include <cstdint>
#include <string>
enum class ABILITYTARGET {SELF, ALLY, ENEMY};
enum class ABILITYSCALER { NONE, STR, AGI, INT};

struct Ability{
    Ability(std::string name, uint32_t cost, uint32_t cd, ABILITYTARGET t, uint32_t hpe, ABILITYSCALER s) :
    Name(name), Cost(cost), Cooldown(cd), Target(t), Hpeffect(hpe), Scaler(s){}
    std::string Name = "unnamed";
    uint32_t  Cost = 0; //assume mp
    uint32_t  Cooldown = 1;//
    ABILITYTARGET Target = ABILITYTARGET::SELF;
    uint32_t  Hpeffect = 1;
    ABILITYSCALER Scaler = ABILITYSCALER::NONE;
};

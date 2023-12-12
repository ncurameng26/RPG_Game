//
// Created by natha on 12/10/2023.
//

#pragma once
#include <cstdint>
#include "statblock.h"
#include "ability.h"
#include "pointwell.h"
#include <string>
#include <memory>
#include<vector>

typedef std::uint64_t exptype;
typedef std::uint16_t leveltype;

class PlayerCharacterDelegate : public StatBlock {
public:
    static const exptype LEVELONE = 100u;

    PlayerCharacterDelegate() : StatBlock(0u, 0u) {
        CurrentLevel = (leveltype)1u;
        CurrentEXP = (exptype) 0u;
        EXPToNextLevel = LEVELONE;
        HP = std::make_unique<PointWell>();
    }

    void gainEXP(exptype gained_exp) {
        CurrentEXP += gained_exp;
        while (check_if_level()) {}
    }

    leveltype getLevel() {
        return CurrentLevel;
    }

    exptype getCurrentEXP() {
        return CurrentEXP;
    }

    exptype getEXPToNextLevel() {
        return EXPToNextLevel;
    }

    virtual void LevelUp() = 0;

    virtual std::string getClassName() = 0;

    std::unique_ptr<PointWell> HP;
    std::unique_ptr<PointWell> MP;



    std::vector<Ability> Abilities;

protected:
    leveltype CurrentLevel;
    exptype CurrentEXP;
    exptype EXPToNextLevel;

    bool check_if_level() {
        static const leveltype LEVELSCALE = 2u;
        if (CurrentEXP >= EXPToNextLevel) {
            CurrentLevel++;
            LevelUp();
            EXPToNextLevel *= LEVELSCALE;
            return true;
        }
        return false;
    }
};

#define PCCONSTRUCT\
    HP->setMax(BASEHP);\
    HP->increaseCurrent(BASEHP); \
    if(MP){        \
    MP->setMax(BASEMP);\
    MP->increaseCurrent(BASEMP); \
        }           \
    increaseStats(BASESTR, BASEINT, BASEAGI);

#define LEVELUP\
HP->setMax((welltype) (BASEHP/2.f) + HP->getMaxWell());\
HP->increaseCurrent((welltype)(BASEHP/2.f));           \
if(MP) {       \
MP->setMax((welltype) (BASEMP/2.f) + MP->getMaxWell());\
MP->increaseCurrent((welltype)(BASEHP/2.f)); \
}         \
increaseStats((stattype) (BASESTR/2.f), ((stattype) (BASESTR/2.f)));



class Cleric : public PlayerCharacterDelegate {
public:
    static const welltype BASEHP = (welltype)14u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)5u;
    static const stattype BASEAGI = (stattype)1u;
    static const welltype BASEMP = (welltype)10u;
    std::string getClassName() override { return std::string("Cleric"); }

    Cleric() : PlayerCharacterDelegate(){
        MP = std::make_unique<PointWell>();
        PCCONSTRUCT
        Abilities.emplace_back("heal", 2u, 1, ABILITYTARGET::ALLY, 2u, ABILITYSCALER::INT );
    }

private:
    void LevelUp() override{
        LEVELUP
        MP.setMax((welltype)(( BASEMP / 2.f) + MP->getMaxWell()));
        MP.increaseCurrent((welltype)(BASEMP / 2.f));

        if (CurrentLevel == 2){

        }

    }
};

class PlayerCharacter{
private:
    PlayerCharacterDelegate* pcclass;

public:
    PlayerCharacter() = delete;
    PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {}
    ~PlayerCharacter() {delete pcclass; pcclass = nullptr; }

    std::string getClassName(){ return pcclass->getClassName(); }
    leveltype getLevel(){ return pcclass->getLevel(); }
    exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
    exptype getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
    welltype getCurrentHP() { return pcclass->HP->getCurrentFullness(); }
    welltype getMaxHP() { return pcclass->HP->getMaxWell(); }
    welltype getCurrentMP() { return pcclass->MP->getCurrentFullness(); }
    welltype getMaxMP() { return pcclass->MP->getMaxWell(); }
    stattype getStrength() { return pcclass->getStrength(); }
    stattype getIntellect() { return pcclass->getIntellect(); }
    stattype getAgility() { return pcclass->getAgility(); }
    stattype getElementResist() { return pcclass->getElementRes(); }

    std::vector<Ability> getAbilityList() {return pcclass->Abilities; }

    void gainEXP(exptype amt) {pcclass->gainEXP(amt); }
    void takeDamage(welltype amt) {pcclass->HP->reduceCurrent(amt); }
    void heal(welltype amt) {pcclass->HP->increaseCurrent(amt); }
};

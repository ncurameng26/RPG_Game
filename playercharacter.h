//
// Created by natha on 12/10/2023.
//

#pragma once
#include "types.h"
#include "statblock.h"
#include "pointwell.h"
#include "ability.h"
#include "item.h"
#include <string>
#include <memory>
#include <vector>


#define PCCONSTRUCT \
HP->setMax(BASEHP);\
HP->increaseCurrent(BASEHP); \
if(MP){ \
MP->setMax(BASEMP);\
MP->increaseCurrent(BASEMP); \
} \
increaseStats(BASESTR, BASEINT, BASEAGI, BASEARMOR);

#define LEVELUP \
HP->setMax((welltype) ((BASEHP/2.f) + HP->getMaxWell()));\
HP->increaseCurrent((welltype)(BASEHP/2.f)); \
if(MP) { \
MP->setMax((welltype) ((BASEMP/2.f) + MP->getMaxWell()));\
MP->increaseCurrent((welltype)(BASEMP/2.f)); \
} \
increaseStats((stattype) (BASESTR/2.f), ((stattype) (BASESTR/2.f)));


class PlayerCharacterDelegate : public StatBlock {
public:
    static const exptype LEVEL2AT = 100u;

    PlayerCharacterDelegate() : StatBlock(0u, 0u) {
        CurrentLevel = (leveltype)1u;
        CurrentEXP = (exptype) 0u;
        EXPToNextLevel = LEVEL2AT;
        HP = std::make_unique<PointWell>(1u, 1u);
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

    void applyBuff(Buff b){
        addNewBuff(b);
    }

    std::vector<Buff> getBuffList() {
        return Buffs;
    }

    virtual void LevelUp() = 0;

    virtual std::string getClassName() = 0;

    std::unique_ptr<PointWell> HP;
    std::unique_ptr<PointWell> MP;

    std::vector<Ability> Abilities;
    std::vector<Item*> Backpack;

protected:
    leveltype CurrentLevel;
    exptype CurrentEXP;
    exptype EXPToNextLevel;

    bool check_if_level() {
        static const leveltype LEVELSCALAR = 2u;
        if (CurrentEXP >= EXPToNextLevel) {
            CurrentLevel++;
            LevelUp();
            EXPToNextLevel *= LEVELSCALAR;
            return true;
        }
        return false;
    }
};

class Cleric : public PlayerCharacterDelegate {
public:
    static const welltype BASEHP = (welltype)14u;
    static const welltype BASEMP = (welltype)10u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)5u;
    static const stattype BASEAGI = (stattype)1u;
    static const stattype BASEARMOR = (stattype)4u;

    std::string getClassName() override { return std::string("Cleric"); }
    Cleric() : PlayerCharacterDelegate(){
        MP = std::make_unique<PointWell>( 10u, 10u);
        PCCONSTRUCT
        Abilities.emplace_back("Heal", 2u, 1, ABILITYTARGET::ENEMY, 2u, ABILITYSCALER::INT );
    }
private:
    void LevelUp() override{
        LEVELUP
        if (CurrentLevel == 2){
            Abilities.emplace_back("Smite", 2u, 1, ABILITYTARGET::ALLY, 2u, ABILITYSCALER::INT );
        }
    }
};

class Wizard : public PlayerCharacterDelegate {
public:
    static const welltype BASEHP = (welltype)10u;
    static const welltype BASEMP = (welltype)14u;
    static const stattype BASESTR = (stattype)1u;
    static const stattype BASEINT = (stattype)8u;
    static const stattype BASEAGI = (stattype)2u;
    static const stattype BASEARMOR = (stattype)2u;

    std::string getClassName() override { return std::string("Wizard"); }
    Wizard() : PlayerCharacterDelegate(){
        MP = std::make_unique<PointWell>( 15u, 15u);
        PCCONSTRUCT
        Abilities.emplace_back("Fireball", 2u, 1, ABILITYTARGET::ENEMY, 3u, ABILITYSCALER::INT);
    }
private:
    void LevelUp() override{
        LEVELUP
        if (CurrentLevel == 2){
            Abilities.emplace_back("Magic Pissile", 2u, 1, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
        MP->setMax(1u + MP->getMaxWell());
        MP->increaseCurrent(1u);
        increaseStats(0,1,0,1,0);
        }
    }
};

class Rogue : public PlayerCharacterDelegate {
public:
    static const welltype BASEHP = (welltype)10u;
    static const welltype BASEMP = (welltype)14u;
    static const stattype BASESTR = (stattype)1u;
    static const stattype BASEINT = (stattype)8u;
    static const stattype BASEAGI = (stattype)2u;
    static const stattype BASEARMOR = (stattype)2u;

    std::string getClassName() override { return std::string("Rogue"); }
    Rogue() : PlayerCharacterDelegate(){
        MP = std::make_unique<PointWell>( 15u, 15u);
        PCCONSTRUCT
        Abilities.emplace_back("Stab", 2u, 1, ABILITYTARGET::ENEMY, 3u, ABILITYSCALER::INT);
    }
private:
    void LevelUp() override{
        LEVELUP
        if (CurrentLevel == 2){
            Abilities.emplace_back("Kill", 2u, 1, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
            MP->setMax(1u + MP->getMaxWell());
            MP->increaseCurrent(1u);
            increaseStats(0,1,0,1,0);
        }
    }
};

class Warrior : public PlayerCharacterDelegate {
public:
    static const welltype BASEHP = (welltype)20u;
    static const welltype BASEMP = (welltype)14u;
    static const stattype BASESTR = (stattype)1u;
    static const stattype BASEINT = (stattype)4u;
    static const stattype BASEAGI = (stattype)2u;
    static const stattype BASEARMOR = (stattype)2u;

    std::string getClassName() override { return std::string("Warrior"); }
    Warrior() : PlayerCharacterDelegate(){
        MP = std::make_unique<PointWell>( 0u, 0u);
        PCCONSTRUCT
        Abilities.emplace_back("Swing", 2u, 1, ABILITYTARGET::ENEMY, 3u, ABILITYSCALER::INT);
    }
private:
    void LevelUp() override{
        LEVELUP
        if (CurrentLevel == 2){
            Abilities.emplace_back("Behead", 2u, 1, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
//            increaseStats(10,10,10,10,10);


        }
    }
};

class PlayerCharacter{
private:
    PlayerCharacterDelegate* pcclass;
    Item* EquippedArmor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
    Item* EquippedWeapon[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
    friend class ItemManager;
public:
    PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {
        auto i = 0;
        for(i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            EquippedArmor[i] = nullptr;
        }
        for(i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++){
            EquippedWeapon[i] = nullptr;
        }
    }

    ~PlayerCharacter() {
        delete pcclass;
        pcclass = nullptr;
        auto i = 0;
        for(i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            if(EquippedArmor[i]){
                delete EquippedArmor[i];
                EquippedArmor[i] = nullptr;
            }
        }
        for(i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++){
            if(EquippedWeapon[i]){
                delete EquippedWeapon[i];
                EquippedWeapon[i] = nullptr;
            }
        }
    }

    //Getters
    std::string getClassName(){ return pcclass->getClassName(); }
    leveltype getLevel(){ return pcclass->getLevel(); }
    exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
    exptype getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
    welltype getCurrentHP() { return pcclass->HP->getCurrentFullness(); }
    welltype getMaxHP() { return pcclass->HP->getMaxWell(); }
    welltype getCurrentMP() {
        if(pcclass->MP)
            return pcclass->MP->getCurrentFullness();
        else
            return 0;
    }
    welltype getMaxMP() {
        if(pcclass->MP)
            return pcclass->MP->getMaxWell();
        else
            return 0;
    }

    stattype getBaseStrength() { return pcclass->getBaseStrength(); }
    stattype getBaseIntellect() { return pcclass->getBaseIntellect(); }
    stattype getBaseAgility() { return pcclass->getBaseAgility(); }
    stattype getBaseArmor() { return pcclass->getBaseArmor(); }
    stattype getBaseElementResist() { return pcclass->getBaseElementResistance(); }
    stattype getTotalStrength() {
        stattype str_from_armor = 0;
        for(auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            if(EquippedArmor[i]){
                str_from_armor += EquippedArmor[i]->Stats.Strength;
            }
        }
        return pcclass->getTotalStrength() + str_from_armor;
    }
    stattype getTotalIntellect() {
        stattype int_from_armor = 0;
        for(auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            if(EquippedArmor[i]){
                int_from_armor += EquippedArmor[i]->Stats.Intellect;
            }
        }
        return pcclass->getTotalIntellect() + int_from_armor;
    }
    stattype getTotalAgility() {
        stattype agi_from_armor = 0;
        for(auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            if(EquippedArmor[i]){
                agi_from_armor += EquippedArmor[i]->Stats.Agility;
            }
        }
        return pcclass->getTotalAgility() + agi_from_armor;
    }
    stattype getTotalArmor(){
        stattype armor_from_armor = 0;
        for(auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            if(EquippedArmor[i]){
                armor_from_armor += EquippedArmor[i]->Stats.Armor;
            }
        }
        return pcclass->getTotalArmor() + armor_from_armor;
    }
    stattype getTotalElementResist() {
        stattype elres_from_armor = 0;
        for(auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++){
            if(EquippedArmor[i]){
                elres_from_armor += EquippedArmor[i]->Stats.ElementResistance;
            }
        }
        return pcclass->getTotalElementResistance() + elres_from_armor;
    }

    std::vector<Ability> getAbilityList() {return pcclass->Abilities; }
    std::vector<Buff> getBuffList() { return pcclass->getBuffList(); }

    Item* getEquippedArmor(unsigned long long i){
        return (dynamic_cast<Armor*>(EquippedArmor[i]));
    }
    Item* getEquippedWeapons(unsigned long long i){
        return (dynamic_cast<Weapon*>(EquippedWeapon[i]));
    }

    //Setters
    void gainEXP(exptype amt) {pcclass->gainEXP(amt); }
    void takeDamage(welltype amt) {pcclass->HP->reduceCurrent(amt); }
    void heal(welltype amt) {pcclass->HP->increaseCurrent(amt); }
    void applyBuff(Buff buff){pcclass->applyBuff(buff);}



    //Deleted Constructors
    PlayerCharacter() = delete;
    PlayerCharacter(const PlayerCharacter&) = delete;
    PlayerCharacter(const PlayerCharacter&&) = delete;

};

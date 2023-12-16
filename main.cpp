#include <iostream>
#include "playercharacter.h"
#include "itemmanager.h"

int main() {

    // just test code for now, replace 'Warrior' with your class to test
    PlayerCharacter p1(new Warrior());

    {
        CoreStats plate_armor_stats;
        plate_armor_stats.Armor = 15;
        plate_armor_stats.ElementResistance = 30;
        plate_armor_stats.Strength = 30;
        plate_armor_stats.Agility = 30;
        plate_armor_stats.Intellect = 30;
        Item* FullPlateMail = ItemManager::CreateArmor("Shiny Plate Armor", plate_armor_stats, ARMORSLOT::CHEST);
        if(p1.equip(FullPlateMail)){
            std::cout << "equip success! \n";
        }
        else{
            std::cout << "equip failed!";
        }
    }

    {
        CoreStats leather_helm_armor_stats;
        leather_helm_armor_stats.Armor = 2;
        leather_helm_armor_stats.ElementResistance = 2;
        Item* LeatherHelm = ItemManager::CreateArmor("Leather Helm", leather_helm_armor_stats, ARMORSLOT::HELMET);
        if(p1.equip(LeatherHelm)){
            std::cout << "equip success! \n";
        }
        else{
            std::cout << "equip failed!";
        }
    }

    {
        Item* LongSword = ItemManager::CreateWeapon("Long Sword", CoreStats(), WEAPONSLOT::MELEE, 3, 9);
        if(p1.equip(LongSword)){
            std::cout << "equip success! \n";
        }
        else{
            std::cout << "equip failed!";
        }
    }







    for (int i = 0; i < 2; i++) {
        std::cout
                << p1.getClassName()
                << " Level " << p1.getLevel() << '\n'
                << "-EXP: " << p1.getCurrentEXP() << '/' << p1.getEXPToNextLevel() << '\n'
                << "-HP: " << p1.getCurrentHP() << '/' << p1.getMaxHP() << '\n'
                << "-MP: " << p1.getCurrentMP() << '/' << p1.getMaxMP() << '\n'
                << "-Strength: " << p1.getTotalStrength() << '\n'
                << "-Intellect: " << p1.getTotalIntellect() << '\n'
                << "-Agility: " << p1.getTotalAgility() << '\n'
                << "-Armor: " << p1.getTotalArmor() << '\n'
                << "-Resist: " << p1.getTotalElementResist() << '\n';

        auto AllAbilities= p1.getAbilityList();


        std::cout << "-Armor:\n";
        for (int i = 0; i < (int)ARMORSLOT::NUM_SLOTS; i++) {
            const Armor* tmp = dynamic_cast<Armor*>(p1.getEquippedArmor(i));
            if(tmp){
                std::cout<< "" << tmp->Name << ", A:(" << tmp->Stats.Armor <<  ") R:(" << tmp->Stats.ElementResistance << ")" << '\n';

            }
        }
        std::cout << "-Abilities:\n";
        for (auto& abil : AllAbilities) {
            std::cout << "  -" << abil.Name << '\n';
        }



        auto AllBuffs = p1.getBuffList();
        std::cout << "-Buffs:\n";
        for (auto& buff : AllBuffs) {
            std::cout << "  -" << buff.Name << '\n';
        }



        std::cout << "-Weapons:\n";
        for (int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {
            const Weapon* tmp = dynamic_cast<Weapon*>(p1.getEquippedWeapons(i));
            if(tmp){
                std::cout<< "" << tmp->Name << ", D:(" << tmp->MinDamage <<  "-" << tmp->MaxDamage << ")" << '\n';

            }
        }

        if (i < 1) {
            p1.gainEXP(100u);
            Buff arm_buff("Stone Shield", 10, 3, 3, 3, 3);
            p1.applyBuff(arm_buff);
        }
    }

    std::cout <<"Health Before Damage: " << p1.getCurrentHP() << "\n";

    p1.takeDamage(1);

    std::cout <<"Health After Damage: " << p1.getCurrentHP() << "\n";


    Item* HealPotion = ItemManager::CreatePotion("Minor Heal Potion", 3u, 3u);

    std::cout <<"Health Before Pot: " << p1.getCurrentHP() << "\n";

    p1.use(HealPotion);

    std::cout <<"Health After Pot: " << p1.getCurrentHP() << "\n";


    return 0;
}
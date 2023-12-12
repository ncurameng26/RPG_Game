#include <iostream>
#include "playercharacter.h"
//Allows for user input and program output



int main() {

//    PlayerCharacter p1(new Cleric());
    PlayerCharacter p1( new Warrior());


    for (int i =0; i < 2; i++){
        std::cout
            << "~" << p1.getClassName() << "~ \n"
            <<  "Level: " <<p1.getLevel() << "\n"
            << "EXP: " <<p1.getCurrentEXP() << "/" << p1.getEXPToNextLevel() << '\n'
            << "HP: " << p1.getCurrentHP() << "/" <<  p1.getMaxHP() << '\n'
            << "MP: " << p1.getCurrentMP() << "/" <<  p1.getMaxMP() << '\n'
            << "Armor: " <<p1.getArmor() << "\n"
            << "Strength: " << p1.getStrength() << "\n"
            << "Intellect: " <<p1.getIntellect() << "\n"
            << "Agility: " <<p1.getAgility() << "\n"
            << "Element Resistance: " <<p1.getElementResist() << "\n";

        auto AllAbilities = p1.getAbilityList();
        std::cout << "Abilities: \n";

        for(auto& abil : AllAbilities){
            std::cout << "  -" << abil.Name <<'\n';
        }

        if(i<1)
            p1.gainEXP(100u);
    }

    return 0; //Returning 0 means that the program ran correctly
}
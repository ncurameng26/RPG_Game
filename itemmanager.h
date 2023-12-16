//
// Created by natha on 12/15/2023.
//
#pragma once
#include "item.h"
#include <string>

class ItemManager{
public:
    static Item* CreateArmor(std::string name, CoreStats cstats, ARMORSLOT slot){
        Item* temp_item = new Item(new Armor(name, cstats, slot));
        return temp_item;
    }

    static Item* CreateWeapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false){
        Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
        return temp_item;
    }

    //makes at least 1 potion
    static Item* CreatePotion(std::string name, welltype heal = 1u, itemcount quant = 1u, Buff* buff = nullptr){
        Item* temp_item = new Item(new Potion(name, heal, (quant == 0) ? 1 : quant, buff));
        return temp_item;
    }

    static bool Equip(Item* item_to_equip, PlayerCharacter* p_char) {
        if(!item_to_equip || !item_to_equip->GetData() || p_char){
            return false;
        }

        Armor *armor = dynamic_cast<Armor*>(item_to_equip->_data);
        if (armor) {
            unsigned long long slot_num = (unsigned long long) armor->Slot;
            if (p_char->EquippedArmor[slot_num]) {
                MoveToBackpack(p_char->EquippedArmor[slot_num], p_char);
                p_char->EquippedArmor[slot_num] = item_to_equip;
            } else {
                p_char->EquippedArmor[slot_num] = item_to_equip;
            }
            return true;
        }

        Weapon *weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
        if (weapon) {
            unsigned long long slot_num = (unsigned long long) weapon->Slot;
            if (p_char->EquippedWeapon[slot_num]) {
                MoveToBackpack(p_char->EquippedWeapon[slot_num], p_char);
                p_char->EquippedWeapon[slot_num] = item_to_equip;
            } else {
                p_char->EquippedWeapon[slot_num] = item_to_equip;
            }
            return true;
        }
        return false;
    }

    static bool Use(Item* item_to_use, PlayerCharacter* p_char){
        if(!item_to_use || !item_to_use->GetData() || !p_char){
            return false;
        }
        Potion* potion = dynamic_cast<Potion*>(item_to_use->_data);
        if(potion){
            //apply buff if it has a buff
            if(potion->buff) {
                p_char->applyBuff(*potion-> buff);
            }
            //if max and try to heal, dont use it!
            if(p_char->pcclass->HP->isFull() && !potion->buff){
                return false;
            }
            //increase hp by heal amount
            p_char->pcclass->HP->increaseCurrent(potion -> HealAmount);
            //use potion and reduce num potions
            potion->Quantity--;
            if(potion->Quantity == 0){
                potion->MarkForDeletion();
            }
            return true;
        }
        return false;
    }

    static bool MoveToBackpack(Item* item_to_move, PlayerCharacter* p_char){

        if(!item_to_move->GetData() || !item_to_move || !p_char ){
            return false;
        }
        p_char->pcclass->Backpack.push_back(item_to_move);
        return true;
    }

};
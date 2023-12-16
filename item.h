//
// Created by natha on 12/12/2023.
//

#pragma once
#include "corestats.h"
#include "buff.h"
#include <string>
#include <typeinfo>

class ItemDelegate{
public:
    std::string Name;
    virtual const char* GetType() = 0;
    void MarkForDeletion(){marked_for_deletion = true;}
protected:
    bool marked_for_deletion = false;
    ItemDelegate(std::string name) : Name(name){}
};

#define GETTYPE const char* GetType() override { return typeid(*this).name(); }

class Potion final: public ItemDelegate{
public:
    Buff* buff;
    welltype HealAmount;
    itemcount Quantity;

    ~Potion(){
        if(buff){
            delete buff;
            buff = nullptr;
        }
    }

    GETTYPE
private:
    Potion(std::string name, welltype hp_heal = 1u, itemcount quant = 1u, Buff* buf = nullptr )
    : ItemDelegate(name), HealAmount(hp_heal), Quantity(quant), buff(buf){}
    friend class ItemManager;

};

class Item{
public:
    const ItemDelegate* GetData() { return _data; }
    ~Item(){
        if(_data){
            delete _data;
            _data = nullptr;
        }

    }
private:
    ItemDelegate* _data;
    Item(ItemDelegate* item) : _data(item){}
    friend class ItemManager;
    friend class PlayerCharacter;
};


class Item : public ItemDelegate{
public:
    const std::uint32_t UniqueId;
    CoreStats Stats;
protected:
    Item(std::string name, CoreStats cstats);
private:

};

enum class ARMORSLOT{ HELMET, CHEST, LEGS, BOOTS, RING1, GLOVE, NUM_SLOTS };
class Armor final : public Item {
public:
    ARMORSLOT Slot;


    GETTYPE


private:
    Armor(std::string name, CoreStats cstats, ARMORSLOT slot) : Item(name, cstats), Slot(slot){}
    Armor() = delete;
    Armor(const Armor&) = delete;
    Armor(const Armor&&) = delete;

    friend class ItemManager;


};

enum class WEAPONSLOT{ MELEE, RANGED, NUM_SLOTS };
class Weapon final : public Item{
public:
    WEAPONSLOT Slot;
    damagetype MinDamage;
    damagetype MaxDamage;
    bool is2Hand;

    GETTYPE

private:
    Weapon(std::string name, CoreStats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false)
            : Item(name, cstats), Slot(slot), MinDamage(min), MaxDamage(max), is2Hand(twohanded){
    }
    Weapon() = delete;
    Weapon(const Weapon&) = delete;
    Weapon(const Weapon&&) = delete;

    friend class ItemManager;

};


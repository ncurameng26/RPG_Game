//
// Created by natha on 12/14/2023.
//

#include "item.h"

static std::uint32_t  EQUIPMENTUNIQUEID = 0u;

Item::Item(std::string name, CoreStats cstats)
: ItemDelegate(name), Stats(cstats), UniqueId(++EQUIPMENTUNIQUEID){
};
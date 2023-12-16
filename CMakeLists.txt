cmake_minimum_required(VERSION 3.27)
project(RPGGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(RPGGame main.cpp
        pointwell.cpp
        pointwell.h
        statblock.h
        da.h
        playercharacter.h
        ability.h
        buff.h
        types.h
        corestats.h
        item.h
        item.cpp
        itemmanager.h
)

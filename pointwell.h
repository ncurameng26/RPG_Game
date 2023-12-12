//
// Created by natha on 12/10/2023.
//

#include <cstdint>
#pragma once

typedef std::uint16_t welltype;

class PointWell {
public:
    //returns true if set successfully
    bool setMax(welltype new_max){
        if(new_max < 1)
            return false;
        MaxWell = new_max;
        if(CurrentFullness > MaxWell)
            CurrentFullness = MaxWell;
        return true;
    }

    welltype getMaxWell(){
        return MaxWell;
    }

    welltype getCurrentFullness(){
        return CurrentFullness;
    }



    void reduceCurrent(welltype amount){
        if(amount > CurrentFullness){
            CurrentFullness = 0;
            return;
        }
        CurrentFullness -= amount;
    }

    void increaseCurrent(welltype amount){
        if(amount + CurrentFullness > MaxWell){
            CurrentFullness = MaxWell;
            return;
        }
        CurrentFullness += amount;
    }

    PointWell(){ //simple constructor
        CurrentFullness = 1;
        MaxWell = 1;
    }

    PointWell(welltype wellSize){ //simple constructor
        CurrentFullness = wellSize;
        MaxWell = wellSize;
    }

    PointWell(welltype c, welltype m){
        CurrentFullness = c;
        MaxWell = m;
        if(CurrentFullness > MaxWell)
            CurrentFullness = MaxWell;
    }

private:
    welltype CurrentFullness;
    welltype MaxWell;
};

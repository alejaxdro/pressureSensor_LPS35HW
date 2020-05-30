#include <iostream>
#include "PressConverter.h"

PressConverter::PressConverter()
{
    //ctor
}

float PressConverter::convertUnit2Unit(float val, int unitfrom, int unitto){
    SetPres(val, unitfrom);
    return GetPres(unitto);
}

void PressConverter::SetPres(float val, int unit){
    switch(unit)
    {
    case PressConverter::pa:
        this->presPa   = val;
        this->presAtm  = val / 101325.0;
        this->presPsi  = val / 6895.0;
        this->presmmHg = val / 133.0;
        break;
    default:
        std::cout << "Incorrect Unit Entered: All values set to Sea Level Press (1atm)" << std::endl;
        SetPres(SEA_LEVEL_ATM, PressConverter::atm);
    }
}


float PressConverter::GetPres(int unit){
    switch(unit)
    {
    case PressConverter::pa:
        return this->presPa;
        break;
    case PressConverter::psi:
        return this->presPsi;
        break;
    case PressConverter::atm:
        return this->atm;
        break;
    case PressConverter::mmhg:
        return this->mmhg;
    default:
        std::cout << "Incorrect Unit Entered: Returning default of 1atm" << std::endl;
        return 1.0;
    }
}

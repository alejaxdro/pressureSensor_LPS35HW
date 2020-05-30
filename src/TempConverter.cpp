#include <iostream>
#include "TempConverter.h"


TempConverter::TempConverter()
{
    std::cout << "Thank you for using TempConverter 1.0" << std::endl;
}

float TempConverter::TempF2C(float val)
{
    return (val - 32) * 5 / 9;
}

float TempConverter::TempC2F(float val)
{
    return (val * 9 / 5) + 32;
}

float TempConverter::TempK2C(float val)
{
    return (val - KELVIN_CELSIUS_DIFF);
}

float TempConverter::TempK2F(float val)
{
    return ((val - KELVIN_CELSIUS_DIFF) * 9 / 5) + 32;
}

void TempConverter::SetTempArr(uint8_t *arr)
{

}

// Takes F, C or K, runs conversions and fills member variables
void TempConverter::SetTemp(float val, char unit)
{
    switch(unit)
    {
    case 'F':
    case 'f':
        this->tempF = val;
        this->tempC = TempF2C(val);
        //this.tempK = TempF2K(val);
        break;
    case 'C':
    case 'c':
        this->tempC = val;
        this->tempF = TempC2F(val);
        //this.tempK = TempC
        break;
    case 'K':
    case 'k':
        this->tempK = val;
        this->tempC = TempK2C(val);
        this->tempF = TempK2F(val);
        break;
    default:
        std::cout << "Incorrect Unit Entered: All values set to Room Temp (20C/68F)" << std::endl;
        SetTemp(20, 'C');
    }
}

float TempConverter::GetF()
{
    return this->tempF;
}

float TempConverter::GetC()
{
    return this->tempC;
}

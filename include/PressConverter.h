#ifndef PRESSCONVERTER_H
#define PRESSCONVERTER_H

#include <stdint.h>

#define SEA_LEVEL_ATM 1.0

class PressConverter
{
public:
    enum pressunits
    {
        pa = 0,
        psi,
        atm,
        mmhg,
    };

    PressConverter();
    float convertUnit2Unit(float val, int unitfrom, int unitto);
    void SetPresArr(uint8_t *arr);
    void SetPres(float val, int unit);
    float GetPres(int unit);
private:
    const float presDefault = SEA_LEVEL_ATM;
    float presPa = 0;
    float presPsi = 0;
    float presAtm = 0;
    float presmmHg = 0;
};

#endif // PRESSCONVERTER_H

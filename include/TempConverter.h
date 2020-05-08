#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H
#include <stdint.h>

#define ROOM_TEMP_C         20
#define KELVIN_CELSIUS_DIFF 273.15

class TempConverter
{
    public:
        TempConverter();
        float TempF2C(float val);
        float TempC2F(float val);
        float TempK2C(float val);
        float TempK2F(float val);
        void SetTempArr(uint8_t *arr);
        void SetTemp(float val, char unit);
        float GetF();
        float GetC();
    private:
        const float tempDefault = 20;
        float tempF = 0;
        float tempC = 0;
        int tempK = 0;
};

#endif // TEMPCONVERTER_H

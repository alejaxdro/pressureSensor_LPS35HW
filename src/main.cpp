// @file main.cpp
// i2c test program

#include <iostream>
#include <stdint.h>
#include <string.h>
#include <errno.h>
//#include <wiringPiI2C.h>
#include "LPS35HW.h"
#include "TempConverter.h"
#include "PressConverter.h"

using namespace std;

int main()
{
    float pressure = 0;
    TempConverter tempLPS35HW;
    PressConverter presLPS35HW;
    LPS35HW pressSensor;

    if(pressSensor.begin_I2C(LPS35HW_I2CADDR_DEFAULT) == false)
    {
        cout << "Error. Initialization failed." << endl;
        return 1;
    }

    float startingPressure = pressSensor.readPsi();
    float lastPressure = startingPressure;
    cout << "Starting Pressure (psi):" << startingPressure << endl;

    for(int i = 0; i < 10; i++)
    {
        pressure = pressSensor.readPsi();
        //if(pressure > (lastPressure + 0.001) || pressure < (lastPressure - 0.001)){
        cout << "Pressure (psi):" << pressure << endl;
        lastPressure = pressure;
        //}
        tempLPS35HW.SetTemp(pressSensor.readTemp(), 'C');
        cout << "Temperature (F):" << tempLPS35HW.GetF() << endl;
    }

    return 0;
}

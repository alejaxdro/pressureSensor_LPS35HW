// @file main.cpp
// i2c test program

#include <iostream>
#include <stdint.h>
#include <string.h>
#include <errno.h>
//#include <wiringPiI2C.h>
#include "LPS35HW.h"

using namespace std;

int main()
{
    float pressure = 0;
    float temperature = 0;

    LPS35HW pressSensor;

    if(pressSensor.begin_I2C(LPS35HW_I2CADDR_DEFAULT) == false){
        cout << "Error. Initialization failed." << endl;
        return 1;
    }

    float startingPressure = pressSensor.readPressure();
    float lastPressure = startingPressure;
    cout << "Starting Pressure (hPa):" << startingPressure << endl;

    for(int i = 0; i < 100; i++){
        pressure = pressSensor.readPressure();
        if(pressure > (lastPressure + 0.001) || pressure < (lastPressure - 0.001)){
            cout << "Pressure (hPa):" << pressure << endl;
            lastPressure = pressure;
        }
        //temperature = pressSensor.readTemperature();
        //cout << "Temperature (C):" << temperature << endl;
    }

    return 0;
}

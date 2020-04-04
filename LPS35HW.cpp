/*!
 *  @file LPS35HW.cpp
 *
 *  @mainpage Adafruit LPS35HW I2C water resistant barometric pressure sensor
 *
 *  @section intro_sec Introduction
 *
 * 	Linux I2C Driver for the LPS35HW I2C water resistant barometric pressure
 * sensor
 *
 * 	This is a library for the Adafruit LPS35HW breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing most of this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section author Author
 *
 *  Bryan Siepert for Adafruit Industries
 *  Alejandro Lepervanche for Open Source education
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "LPS35HW.h"


/*!
 *    @brief  Instantiates a new LPS35HW class
 */
LPS35HW::LPS35HW(void) {}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
bool LPS35HW::begin_I2C(uint8_t i2c_address) {
  fd = wiringPiI2CSetup(i2c_address);

  return init();
}

bool LPS35HW::init(void) {
  // make sure we're talking to the right chip
    int result = wiringPiI2CReadReg8(fd, LPS35HW_WHO_AM_I);
    if(result == -1){
        cout << "Error. Errno is: " << errno << endl;
        return false;
    }else if (result == 0xb1){
        // 0xb1/177 is the chip id from ST datasheet
        cout << "Pressure Sensor LPS35HW connected" << endl;
    }else{
        cout << "Error. Result is: " << result << endl;
        return false;
    }

  int Config1 = wiringPiI2CReadReg8(fd, LPS35HW_CTRL_REG1);
  int Config2 = wiringPiI2CReadReg8(fd, LPS35HW_CTRL_REG2);
  int Config3 = wiringPiI2CReadReg8(fd, LPS35HW_CTRL_REG3);
  int InterruptCfg = wiringPiI2CReadReg8(fd, LPS35HW_INTERRUPT_CFG);
  int InterruptStatus = wiringPiI2CReadReg8(fd, LPS35HW_INT_SOURCE);
  cout << "Config1: " << hex << Config1 << " Config2: " << Config2 << " Config3: " << Config3 << " IntCfg: " << InterruptCfg << " IntStatus: " << InterruptStatus << endl;

  reset();

  setDataRate(LPS35HW_RATE_10_HZ);

  return true;
}

/**************************************************************************/
/*!
    @brief Sets Block Reads.
*/
/**************************************************************************/
void LPS35HW::setBlockReads(void){
    // setup block reads
    int Config1 = wiringPiI2CReadReg8(fd, LPS35HW_CTRL_REG1);
    wiringPiI2CWriteReg8(fd, LPS35HW_CTRL_REG1, ((uint8_t)Config1 | 0x02));
}

/**************************************************************************/
/*!
    @brief Resets the hardware. All configuration registers are set to
            default values, the same as a power-on reset.
*/
/**************************************************************************/
void LPS35HW::reset(void) {
    int regval;
    regval = wiringPiI2CReadReg8(fd, LPS35HW_CTRL_REG2);
    //cout << "Ctrl Reg 2: " << hex << regval << endl;
    wiringPiI2CWriteReg8(fd, LPS35HW_CTRL_REG2, regval | 0x04);
    //cout << "Ctrl Reg 2: " << hex << (regval | 0x04) << endl;
}

/**************************************************************************/
/*!
    @brief Reads and scales the current value of the temperature register.
    @return The current temperature in degrees C
*/
/**************************************************************************/
float LPS35HW::readTemperature(void) {
    // Grab temp data - 2 reg reads
    int low = wiringPiI2CReadReg8(fd, LPS35HW_TEMP_OUT_L);
    int temperatureOut = low;
    int high = wiringPiI2CReadReg8(fd, LPS35HW_TEMP_OUT_H);
    temperatureOut |= high << 8;
    //cout << "Temperature Reading: " << (double)temperatureOut / 100.0 << hex << " low: " << low << " high: " << high << endl;
    return (double)temperatureOut / 100.0;
}
/**************************************************************************/
/*!
    @brief Reads and scales the value of the pressure register.
    @return The current pressure in hPa, relative to the reference temperature
*/
/**************************************************************************/
float LPS35HW::readPressure(void) {
    int low = wiringPiI2CReadReg8(fd, LPS35HW_PRESS_OUT_XL);
    int raw_pressure = low;
    int mid = wiringPiI2CReadReg8(fd, LPS35HW_PRESS_OUT_L);
    raw_pressure |= mid << 8;
    int high = wiringPiI2CReadReg8(fd, LPS35HW_PRESS_OUT_H);
    raw_pressure |= high << 16;
    // perform sign extension for 24 bit number if needed
    if (raw_pressure & 0x800000) {
        raw_pressure = (0xff000000 | raw_pressure);
    }
    //cout << "Pressure Reading: " << pressureOut << hex << " low: " << low << " mid: " << mid << " high: " << high << endl;
    return (float) raw_pressure / 4096;  // perform sign extension for 24 bit number if needed
}

/**************************************************************************/
/*!
    @brief Takes a new measurement while in one shot mode.
*/
/**************************************************************************/
void LPS35HW::takeMeasurement(void) {
//  Adafruit_BusIO_RegisterBits one_shot =
//      Adafruit_BusIO_RegisterBits(Config2, 1, 0);
//  one_shot.write(1);
//  while (one_shot.read() == true) {
//    delay(1);
//  };
}

/**************************************************************************/
/*!
    @brief Sets the reference temperature to the current temperature. Future
            pressure readings will be relative to it until `resetPressure` is
            called.
*/
/**************************************************************************/
void LPS35HW::zeroPressure(void) {
//  Adafruit_BusIO_RegisterBits zero_pressure =
//      Adafruit_BusIO_RegisterBits(InterruptCfg, 1, 5);
//  zero_pressure.write(1);
//  while (zero_pressure.read() == true) {
//    delay(1);
//  };
}

/**************************************************************************/
/*!
    @brief Resets the reference pressure to zero so calls to `getPressure`
            are reported as the absolute value.
*/
/**************************************************************************/
void LPS35HW::resetPressure(void) {
//  Adafruit_BusIO_RegisterBits pressure_reset =
//      Adafruit_BusIO_RegisterBits(InterruptCfg, 1, 4);
//  pressure_reset.write(1);
}

/**************************************************************************/
/*!
    @brief Sets the pressure threshold used by the high and low pressure
   thresholds
    @param threshold_pressure
            The threshold pressure in hPa, measured from zero
*/
/**************************************************************************/
void LPS35HW::setThresholdPressure(float threshold_pressure) {
//  Adafruit_BusIO_Register threshold = Adafruit_BusIO_Register(
//      i2c_dev, spi_dev, ADDRBIT8_HIGH_TOREAD, LPS35HW_THS_P_L, 2);
//  threshold.write(threshold_pressure * 16);
}
/**************************************************************************/
/*!
    @brief Enables high pressure threshold interrupts.
*/
/**************************************************************************/
void LPS35HW::enableHighThreshold(void) {
//  Adafruit_BusIO_RegisterBits high_thresh =
//      Adafruit_BusIO_RegisterBits(InterruptCfg, 1, 0);
//  high_thresh.write(0x1);
//  Adafruit_BusIO_RegisterBits high_int_pin =
//      Adafruit_BusIO_RegisterBits(Config3, 1, 0);
//  high_int_pin.write(0x1);
}
/**************************************************************************/
/*!
    @brief Disables low pressure threshold interrupts.
*/
/**************************************************************************/
void LPS35HW::enableLowThreshold(void) {
//  Adafruit_BusIO_RegisterBits low_thresh =
//      Adafruit_BusIO_RegisterBits(InterruptCfg, 1, 1);
//  low_thresh.write(0x1);
//  Adafruit_BusIO_RegisterBits low_int_pin =
//      Adafruit_BusIO_RegisterBits(Config3, 1, 1);
//  low_int_pin.write(0x1);
}
/**************************************************************************/
/*!
    @brief Enables pressure threshold interrupts. High and low thresholds
          need to be enabled individually with `enableLowThreshold` and
          `enableHighThreshold`.
    @param active_low Polarity of interrupt pin, true for active low.
    @param open_drain
          Set to `true` to have the INT pin be open drain when active.
*/
/**************************************************************************/
void LPS35HW::enableInterrupts(bool active_low, bool open_drain) {
//  Adafruit_BusIO_RegisterBits pin_mode =
//      Adafruit_BusIO_RegisterBits(Config3, 2, 6);
//  pin_mode.write((active_low << 1) | open_drain);
//
//  Adafruit_BusIO_RegisterBits latch_enabled =
//      Adafruit_BusIO_RegisterBits(InterruptCfg, 2, 2);
//  latch_enabled.write(0x3);
}
/**************************************************************************/
/*!
    @brief Disables pressure threshold interrupts.
*/
/**************************************************************************/
void LPS35HW::disableInterrupts(void) {
//  Adafruit_BusIO_RegisterBits enabled =
//      Adafruit_BusIO_RegisterBits(InterruptCfg, 2, 2);
//  enabled.write(0x0);
}
/**************************************************************************/
/*!
    @brief Enables the low pass filter with ODR/9 bandwidth
    @param extra_low_bandwidth
            Set to `true` to scale the bandwidth to ODR/20
*/
/**************************************************************************/
void LPS35HW::enableLowPass(bool extra_low_bandwidth) {
//  Adafruit_BusIO_RegisterBits filter_config =
//      Adafruit_BusIO_RegisterBits(Config1, 2, 2);
//  filter_config.write(0x2 | (extra_low_bandwidth == true));
}

/**************************************************************************/
/*!
    @brief Returns the current state of the high pressure threshold interrupt.
    @return `true` if the high pressure threshold has been triggered since
          last checked.
*/
/**************************************************************************/
bool LPS35HW::highThresholdExceeded(void) {
  //return (InterruptStatus->read() == 0b101);
}
/**************************************************************************/
/*!
    @brief Returns the current state of the low pressure threshold interrupt.
    @return `true` if the low pressure threshold has been triggered since
          last checked.
*/
/**************************************************************************/
bool LPS35HW::lowThresholdExceeded(void) {
  //return (InterruptStatus->read() == 0b110);
}
/**************************************************************************/
/*!
    @brief Sets a new measurement rate
    @param new_rate
          The new output data rate to be set (ODR)
*/
/**************************************************************************/
void LPS35HW::setDataRate(LPS35HW_DataRate new_rate) {
    wiringPiI2CWriteReg8(fd, LPS35HW_CTRL_REG1, (new_rate<<4));
    //cout << "Ctrl Reg 1 ODR write: " << hex << (new_rate<<4) << endl;
}

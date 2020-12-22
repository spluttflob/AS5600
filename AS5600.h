/** @file AS5600.h
 *    This is a library for interacting with the AS5600 magnetic angle sensor.
 *    It has been forked from the original by Kane C. Stoboi and modified so
 *    that it can be used to communicate wtih more than one AS5600. 
 *  @author Created by Kane C. Stoboi, 22 August, 2018, and released into the 
 *          public domain.
 *  @author Forked by JR Ridgely
 *  @date   2020-Dec-21 Forked by JRR
 *  @copyright Additions by JRR are copyright (c) 2020 by JR Ridgely and
 *             released under the Lesser GNU Public License, version 3.0. 
 */

#ifndef AS5600_h
#define AS5600_h

#include "Arduino.h"
#include <Wire.h>


/** @brief   Class which operates an AS5600 magnetic angle sensor.
 */
class AS5600
{
public:
    AS5600 (TwoWire* p_i2c_bus, uint8_t i2c_address);
    long getPosition (void);
    int getAngle (void);
    int getStatus (void);
    int getGain (void);
    int getMagnitude (void);
    void setZero (void);
    void setI2CAddress (uint8_t new_address);

protected: 
    const uint8_t _ZMCOAddress = 0x00;
    const uint8_t _ZPOSAddressMSB = 0x01;
    const uint8_t _ZPOSAddressLSB = 0x02;
    const uint8_t _MPOSAddressMSB = 0x03;
    const uint8_t _MPOSAddressLSB = 0x04;
    const uint8_t _MANGAddressMSB = 0x05;
    const uint8_t _MANGAddressLSB = 0x06;
    const uint8_t _CONFAddressMSB = 0x07;
    const uint8_t _CONFAddressLSB = 0x08;
    const uint8_t _RAWANGLEAddressMSB = 0x0C;
    const uint8_t _RAWANGLEAddressLSB = 0x0D;
    const uint8_t _ANGLEAddressMSB = 0x0E;
    const uint8_t _ANGLEAddressLSB = 0x0F;
    const uint8_t _STATUSAddress = 0x0B;
    const uint8_t _AGCAddress = 0x1A;
    const uint8_t _MAGNITUDEAddressMSB = 0x1B;
    const uint8_t _MAGNITUDEAddressLSB = 0x1C;
    const uint8_t _BURNAddress = 0xFF;

    long _msb;
    long _lsb;
    long _msbMask = 0b00001111;

    /// A pointer to the I2C driver which will be used for communication
    TwoWire* _pI2C;

    /// The I2C address of this particular sensor
    uint8_t _i2c_addr;

    long _getRegisters2 (uint8_t registerMSB, uint8_t registerLSB);
    int _getRegister (uint8_t register1);
};

#endif // AS5600_h


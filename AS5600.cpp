/** @file AS5600.cpp
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

#include "AS5600.h"


/** @brief   Construct a driver for one AS5600 sensor.
 *  @details This constructor sets up a driver for an AS5600. 
 *  @param   p_i2c_bus A pointer to the I2C driver (such as @c Wire) being used
 *  @param   i2c_address The address of this AS5600 on its I2C bus
 */
AS5600::AS5600 (TwoWire* p_i2c_bus, uint8_t i2c_address)
{
    _p_I2C = p_i2c_bus;
    _i2c_addr = i2c_address;
}


long AS5600::getPosition (void)
{
    return _getRegisters2 (_RAWANGLEAddressMSB, _RAWANGLEAddressLSB);  
}


int AS5600::getAngle (void)
{
    return _getRegisters2 (_ANGLEAddressMSB, _ANGLEAddressLSB);  
}


int AS5600::getStatus (void)
{
    return _getRegister (_STATUSAddress) & 0b00111000;
}


int AS5600::getGain (void)
{
    return _getRegister (_AGCAddress);
}

int AS5600::getMagnitude (void)
{
    return _getRegisters2 (_MAGNITUDEAddressMSB, _MAGNITUDEAddressLSB);
}


int AS5600::_getRegister (uint8_t register1)
{
    _p_I2C->beginTransmission (_i2c_addr);
    _p_I2C->write (register1);
    _p_I2C->endTransmission ();

    _p_I2C->requestFrom (_i2c_addr, 1);

    if (_p_I2C->available () <= 1)
    {
        _msb = _p_I2C->read ();
    }

    return _msb;
}


long AS5600::_getRegisters2 (byte registerMSB, byte registerLSB)
{
    _lsb = 0;
    _msb = 0;

    _p_I2C->beginTransmission (_i2c_addr);
    _p_I2C->write (registerMSB);
    _p_I2C->endTransmission ();
    // #ifdef FreeRTOS
    //     vTaskDelay (10);
    // #else
    //     delay (10);                                   //////////////////////////////////
    // #endif

    _p_I2C->requestFrom (_i2c_addr, 1);

    if (_p_I2C->available () <= 1) 
    {
        _msb = _p_I2C->read ();
    }

    _p_I2C->requestFrom (_i2c_addr, 1);

    _p_I2C->beginTransmission (_i2c_addr);
    _p_I2C->write (registerLSB);
    _p_I2C->endTransmission ();

    if (_p_I2C->available () <= 1) 
    {
        _lsb = _p_I2C->read ();
    }

    return (_lsb) + (_msb & _msbMask) * 256;
}


void setI2CAddress (uint8_t new_address)
{

}

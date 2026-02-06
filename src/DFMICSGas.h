/*
 * This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2026 Sam Groveman
 * 
 * External libraries needed:
 * DFRobot_MICS: https://github.com/DFRobot/DFRobot_MICS/
 * 
 * https://www.dfrobot.com/product-2417.html
 * 
 * Contributors: Sam Groveman
 * 
 * I2C address from dip switches
 * | A0 | A1 |
 * | 0  | 0  |    0x75 default I2C address  
 * | 1  | 0  |    0x76
 * | 0  | 1  |    0x77
 * | 1  | 1  |    0x78 
 * 
 */

#pragma once
#include <Sensor.h>
#include <Wire.h>
#include <DFRobot_MICS.h>

/// @brief Device for interfacing with the DF Robot I2C environmental sensor
class DFMICSGas : public Sensor {
	public:
		DFMICSGas(String Name, TwoWire* I2C_bus = &Wire, uint8_t address = MICS_ADDRESS_0);
		DFMICSGas(String Name, int sda, int scl, TwoWire* I2C_bus = &Wire, uint8_t address = MICS_ADDRESS_0);
		bool begin();
		bool takeMeasurement();
		
	protected:
		/// @brief I2C bus in use
		TwoWire* i2c_bus;

		/// @brief SCL pin in use
		int scl_pin = -1;

		/// @brief SDA pin in use
		int sda_pin = -1;

		/// @brief Checks to see if the sensor has warmed up
		bool warmedUp = false;

		/// @brief Sensor object
		DFRobot_MICS_I2C mics_sensor;
};
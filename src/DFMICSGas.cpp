#include "DFMICSGas.h"

/// @brief Creates a new MICS sensor object
/// @param Name The device name
/// @param I2C_bus The I2C bus attached to the sensor
/// @param address Address of the sensor
DFMICSGas::DFMICSGas(String Name, TwoWire* I2C_bus, uint8_t address) : mics_sensor(I2C_bus, address), Sensor(Name) {
	i2c_bus = I2C_bus;
}

/// @brief Creates a new MICS sensor object
/// @param Name The device name
/// @param sda SDA pin to use for I2C bus
/// @param scl SCL pin to use for I2C bus
/// @param I2C_bus The I2C bus attached to the sensor
/// @param address Address of the sensor
DFMICSGas::DFMICSGas(String Name, int sda, int scl, TwoWire* I2C_bus, uint8_t address) : mics_sensor(I2C_bus, address), Sensor(Name) {
	i2c_bus = I2C_bus;
	scl_pin = scl;
	sda_pin = sda;
}

/// @brief Starts the MICS sensor
/// @return True on success
bool DFMICSGas::begin() {
	Description.parameterQuantity = 6;
	Description.type = "Multi Environment Sensor";
	Description.parameters = {"CO", "NO2", "C2H5OH", "NH3", "H2", "CH4"};
	Description.units = {"ppm", "ppm", "ppm", "ppm", "ppm", "ppm"};
	values.resize(Description.parameterQuantity);

	// Start I2C bus if not started
	if (scl_pin > -1 && sda_pin > -1) {
		if (!i2c_bus->begin(sda_pin, scl_pin)) {
			return false;
		}
	} else {
		if (!i2c_bus->begin()) {
			return false;
		}
	}
	if(mics_sensor.getPowerState() == SLEEP_MODE) {
		mics_sensor.wakeUpMode();
	}
	return true;
}

/// @brief Takes a measurement
/// @return True on success
bool DFMICSGas::takeMeasurement() {
	// Check if sensor is warmed up
	if (!warmedUp) {
		if (!mics_sensor.warmUpTime(3)) {
			Logger.println("Sensor still warming up. Wait 3 minutes from device boot and try again.");
			return false;
		}
		warmedUp = true;
	}

	values[0] = mics_sensor.getGasData(CO);
	values[1] = mics_sensor.getGasData(NO2);
	values[2] = mics_sensor.getGasData(C2H5OH);
	values[3] = mics_sensor.getGasData(NH3);
	values[4] = mics_sensor.getGasData(H2);
	values[5] = mics_sensor.getGasData(CH4);
	return true;
}
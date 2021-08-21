//
//  Sensors.h
//  Robotics Systems
//
//  Created by Robbie Woolterton on 01/03/2021.
//
//  Custom class which inherits from the Sensor_Stream class given to us.
// The methods and variables in this class allow all necessary data collection, conversion, scaling, and fusing for the sensors
//

#ifndef Sensors_h
#define Sensors_h

//#include <stdio.h>
#include <math.h>
#include "Sensor_Stream.h"

class Sensors
{
private:
	Sensor_Stream *pSensor1;
	Sensor_Stream *pSensor2;
	Sensor_Stream *pSensor3;
	
	enum Sensor_Stream::flagState_t state1 = Sensor_Stream::FLAG_DATA_GOOD;
	enum Sensor_Stream::flagState_t state2 = Sensor_Stream::FLAG_DATA_GOOD;
	enum Sensor_Stream::flagState_t state3 = Sensor_Stream::FLAG_DATA_GOOD;
	
	/**
	 * Structure for storing sensor values
	 *
	 * value if for storing the current value of the sensor
	 * previous_value is used for sensor 2 only
	 * temporary_value is also only used by sensor2, and is used in the calculation
	 */
	struct values_t // stores the values of each sensors
	{
		float value;
		float previous_value = -1;
		float temporary_value = 0;
	};
	
	// create instances of the struct for all three sensors
	values_t Sensor1;
	values_t Sensor2;
	values_t Sensor3;
	
public:
	
	/**
	 * Constructor for the Sensors class
	 *
	 * @param pSensor1Inject pointer to the instance of the Sensor_Stream class used for sensor1
	 * @param pSensor2Inject pointer to the instance of the Sensor_Stream class used for sensor2
	 * @param pSensor3Inject pointer to the instance of the Sensor_Stream class used for sensor3
	 */
	Sensors(Sensor_Stream *pSensor1Inject, Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject);
	
	/**
	 * Gets the data from all three of the sensor streams, and stores them in the values_t struct as value
	 */
	void fetch_data(); // gets the data from the 3 streams
	
	/**
	 * Runs the data conversion equations on all three sensor values (sensor 3 doesn't change)
	 *
	 * Changes the value variable in the values_t struct for all three sensors
	 */
	void convert_data(); // converts the data using the given formulae
	
	/**
	 * Runs the data scaling equations on all three sensor values
	 *
	 * Changes the value variable in the values_t struct for all three sensors
	 */
	void scale_data(); // scales the data using the given formulae
	
	/**
	 * Returns the current value of the sensor
	 * Needed because the sensor values are private so that they can't accidentally be changed
	 *
	 * @param sensor_id is the sensor you want to get the value from, using the sensorId_t enum declared in the Sensor_Stream class
	 * @returns the value of the sensor (value in the values_t struct)
	 */
	float return_value(Sensor_Stream::sensorId_t sensor_id); // returns the value of the inputted sensor
	
	/**
	 * Runs the sensor fusion equation on the sensor data and outputs the result of this equation
	 *
	 * @returns the output of the sensor fusion equation
	 */
	float fuse_data(); // runs the sensor fusion formula and outputs this value
	
	/**
	 * Uses pointers to get the states of all three sensor streams (pointers are used because a function can only return one value in C++)
	 * These are private variables to stop them being changed by accident
	 *
	 * @param pState1In pointer to the variable storing the state of the sensor 1 stream
	 * @param pState2In pointer to the variable storing the state of the sensor 2 stream
	 * @param pState3In pointer to the variable storing the state of the sensor 3 stream
	 *
	 */
	void get_states(Sensor_Stream::flagState_t *pState1In, Sensor_Stream::flagState_t *pState2In, Sensor_Stream::flagState_t *pState3In);
	
};

#endif /* Sensors_hpp */ // stops errors if you include it twice by accident





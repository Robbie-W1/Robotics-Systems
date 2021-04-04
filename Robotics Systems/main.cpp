//
//  main.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 17/02/2021.
//

#include <iostream> // used for outputting to the console

#include "Sensor_Stream.h" // lets us use the code from the other files
#include "Logger.h"
#include "Control_Output.h"
#include "Sensors.h"
#include "Loggers.h"


 
int main(int argc, const char * argv[])
{
	// gives us access to all of the sensor data by creating an instance of the class for each sensor
	Sensor_Stream Sensor1_Stream(Sensor_Stream::SENSOR_1);
	Sensor_Stream Sensor2_Stream(Sensor_Stream::SENSOR_2);
	Sensor_Stream Sensor3_Stream(Sensor_Stream::SENSOR_3);

	std::string save_location = "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs";  // folder where all the log files are saved

	// create all of the logs
	Logger log_point_A(Logger::LOG_POINT_A, save_location);
	Logger log_point_B(Logger::LOG_POINT_B, save_location);
	Logger log_point_C(Logger::LOG_POINT_C, save_location);
	Logger log_point_D(Logger::LOG_POINT_D, save_location);
	Logger log_point_E(Logger::LOG_POINT_E, save_location);
	Logger log_point_F(Logger::LOG_POINT_F, save_location);
	Control_Output motor_output(save_location);

	// create variables for storing the state of each sensor stream
	enum Sensor_Stream::flagState_t sensorState1 = Sensor_Stream::FLAG_DATA_GOOD;
	enum Sensor_Stream::flagState_t sensorState2 = Sensor_Stream::FLAG_DATA_GOOD;
	enum Sensor_Stream::flagState_t sensorState3 = Sensor_Stream::FLAG_DATA_GOOD;

	float fused_value;
	float motorA;
	float motorB;
	
	bool running = true; // for managing the loop
	// create instances of the Sensors and Loggers class to handle all the sensor data and logs
	Sensors Sensors(&Sensor1_Stream, &Sensor2_Stream, &Sensor3_Stream);
	Loggers Loggers(&log_point_A, &log_point_B, &log_point_C, &log_point_D, &log_point_E, &log_point_F, &motor_output);
	
	// we use running to check if everything has worked properly, and stop the loop if something went wrong
	while (running)
	{
		
		Sensors.fetch_data(); // get all of the data
		Sensors.get_states(&sensorState1, & sensorState2, &sensorState3); // see what the sensor stream states are
		
		// ANDing running with itself and another boolean means we don't set running to be true
		// if something else has already made it false
		// we do this for all the checks
		
		running = running && (sensorState1 == 0 && sensorState2 == 0 && sensorState3 == 0);
		if (!running) break; // stops us logging the final row, which is nan
		
		// convert the values from the sensors and log them to points A & B
		Sensors.convert_data();
		running = running && Loggers.log(Sensors.return_value(Sensor_Stream::SENSOR_1), Logger::LOG_POINT_A);
		running = running && Loggers.log(Sensors.return_value(Sensor_Stream::SENSOR_2), Logger::LOG_POINT_B);

		// scale all of the sensor data and log it to points C, D, & E
		Sensors.scale_data();
		running = running && Loggers.log(Sensors.return_value(Sensor_Stream::SENSOR_1), Logger::LOG_POINT_C);
		running = running && Loggers.log(Sensors.return_value(Sensor_Stream::SENSOR_2), Logger::LOG_POINT_D);
		running = running && Loggers.log(Sensors.return_value(Sensor_Stream::SENSOR_3), Logger::LOG_POINT_E);

		// fuse all of the sensor data and log it to point F
		fused_value = Sensors.fuse_data();
		running = running && Loggers.log(fused_value, Logger::LOG_POINT_F);

		motorA = fused_value;

		// constrain the value of motorA to be between 1 & -1
		if (motorA > 1) motorA = 1;
		else if (motorA < -1) motorA = -1;


		motorB = -1 * motorA; // motorB is the inverse of motorA
		
		running = running && Loggers.log(motorA, motorB);
	}
	return 0;
}

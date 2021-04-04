//
//  Loggers.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 31/03/2021.
//

#include "Loggers.h"


Loggers::Loggers(Logger *pLogAInject, Logger *pLogBInject, Logger *pLogCInject, Logger *pLogDInject, Logger *pLogEInject, Logger *pLogFInject, Control_Output *pMotorOutputInject)
{
	plogPointA = pLogAInject;
	plogPointB = pLogBInject;
	plogPointC = pLogCInject;
	plogPointD = pLogDInject;
	plogPointE = pLogEInject;
	plogPointF = pLogFInject;
	
	pMotorOutput = pMotorOutputInject;
}

bool Loggers::log(float dataIn, Logger::logType_t log_id)
{
	switch (log_id)
	{
		case Logger::LOG_POINT_A:
			success = plogPointA->log_value(dataIn);
			break;
		case Logger::LOG_POINT_B:
			success = plogPointB->log_value(dataIn);
			break;
		case Logger::LOG_POINT_C:
			success = plogPointC->log_value(dataIn);
			break;
		case Logger::LOG_POINT_D:
			success = plogPointD->log_value(dataIn);
			break;
		case Logger::LOG_POINT_E:
			success = plogPointE->log_value(dataIn);
			break;
		case Logger::LOG_POINT_F:
			success = plogPointF->log_value(dataIn);
			break;
		default:
			success = false;
			break;
	}
	
	if (!success) std::cout << "Error logging to " << logEnumToString(log_id) << "\n"; // if there was an error logging
	return success;
}

bool Loggers::log(float dataIn1, float dataIn2)
{
	success = pMotorOutput->set_output(dataIn1, dataIn2);
	
	if (!success) std::cout << "Error logging to control output \n";
	return success;
}

std::string Loggers::logEnumToString(Logger::logType_t input)
{
	switch (input) {
		case Logger::LOG_POINT_A:
			return "log A";
		case Logger::LOG_POINT_B:
			return "log B";
		case Logger::LOG_POINT_C:
			return "log C";
		case Logger::LOG_POINT_D:
			return "log D";
		case Logger::LOG_POINT_E:
			return "log E";
		case Logger::LOG_POINT_F:
			return "log F";
		case Logger::USER_DEFINED_1:
			return "log user defined 1";
		case Logger::USER_DEFINED_2:
			return "log user defined 2";
		default:
			return "Unknown log";
	}
}

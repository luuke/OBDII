/*
 * ObdScanner.cpp
 *
 *  Created on: Jun 22, 2014
 *      Author: luuke
 */

#ifndef OBDSCANNER_CPP_
#define OBDSCANNER_CPP_

#include "ObdScanner.h"

using namespace ObdScannerHandler;

void ObdScanner::SendMessage(string message)
{
	_serialPort.Write(message + '\r');
}

void ObdScanner::Restart()
{
	SendMessage(RESET_ALL);
}

void ObdScanner::TurnOffEcho()
{
	SendMessage(ECHO_OFF);
}

void ObdScanner::TurnOnEcho()
{
	SendMessage(ECHO_ON);
}

void ObdScanner::TurnOffHeaders()
{
	SendMessage(HEADERS_OFF);
}

void ObdScanner::TurnOnHeaders()
{
	SendMessage(HEADERS_ON);
}

void ObdScanner::TurnOffLinefeeds()
{
	SendMessage(LINEFEEDS_OFF);
}

void ObdScanner::TurnOnLinefeeds()
{
	SendMessage(LINEFEEDS_ON);
}

void ObdScanner::ReadVoltage()
{
	SendMessage(READ_VOLTAGE);
}
#endif /* OBDSCANNER_CPP_ */

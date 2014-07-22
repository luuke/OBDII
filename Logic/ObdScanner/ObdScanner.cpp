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

int ObdScanner::Speed = 0;
int ObdScanner::Revolution = 0;
float ObdScanner::Voltage = 0;

ObdScanner::ObdScanner()
{
	_isReady = false;
	_isResponseForLastCommand = false;
	_lastCommandType = AT;
	_serialPort.Open();
	_serialPort.Configure();
}

ObdScanner::~ObdScanner()
{
	_serialPort.Close();
}

void ObdScanner::Reset()
{

}

void ObdScanner::ReadVehicleParameters()
{
	ReadVehicleSpeed();
	ReadVehicleRevolution();
	ReadVehicleVoltage();
}

void ObdScanner::ReadVehicleSpeed()
{
	//ObdScanner::Speed = 120;
	GetObdData(SHOW_CURRENT_DATA + VEHICLE_SPEED);
	ObdScanner::Speed = _responseData;
}

void ObdScanner::ReadVehicleRevolution()
{
	//ObdScanner::Revolution = 2400;
	GetObdData(SHOW_CURRENT_DATA + ENGINE_RPM);
	ObdScanner::Revolution = _responseData / 4;
}

void ObdScanner::ReadVehicleVoltage()
{
	ObdScanner::Voltage = 14.5;
}

void ObdScanner::PrintDeviceId()
{
	GetData(PRINT_ID);
}

void ObdScanner::GetObdData(string command)
{
	_command = command;
	_commandType = CommandType::OBD;
	SendCommand(command);
	ReadResponse();
	ParseObdResponse();
}

void ObdScanner::ParseObdResponse()
{
	if (IsCorrectObdResponse())
	{
		string data = _response.substr(0,4);
		unsigned int decValue;
		stringstream ss;
		ss << std::hex << data;
		ss >> _responseData;
	}
}

bool ObdScanner::IsCorrectObdResponse()
{
	_obdResponseHeader = _command;
	_obdResponseHeader[0] = '4';

	_isCorrectReponse = _response.compare(0,4,_obdResponseHeader) ==  0 ? true : false;
	return _isCorrectReponse;
}

void ObdScanner::GetData(string command)
{
	SendATCommand(command);
	ReadResponse();
	ParseResponse();
}

void ObdScanner::SendCommand(string command)
{
	_lastCommand = command;
	_serialPort.Write(command + '\r');
}

void ObdScanner::SendATCommand(string command)
{
	_lastCommandType = AT;
	SendCommand(command);
}

void ObdScanner::SendOBDCommand(string command)
{
	_lastCommandType = OBD;
	SendCommand(command);
}

void ObdScanner::ReadResponse()
{
	bool continueReading = true;
	string singleMessage;

	_commandResponse.clear();
	while(continueReading)
	{
		singleMessage = _serialPort.Read();
		_commandResponse += singleMessage;
		cout << singleMessage << endl;
		if(singleMessage.find_first_of('>') != string::npos)
		{
			_isReady = true;
			continueReading = false;
		}
	}

	cout << "Command response: " << _commandResponse << endl;
}

void ObdScanner::ParseResponse()
{
	_isResponseForLastCommand = _commandResponse.find(_lastCommand) != string::npos ? true : false;
//	if(_commandResponse.find('?') != string::npos)
//	{
//		throw ("OBD scanner returned > ? <");
//	}

	if(_isResponseForLastCommand)
	{
		switch(_lastCommandType)
		{
		case AT:
			ParseATCommandResponse();
			break;
		case OBD:
			ParseOBDCommandResponse();
			break;
		default:
			throw ("Case not implemented");
		}
	}
	_isReady = _commandResponse.find('>') != string::npos ? true : false;
}

void ObdScanner::ParseATCommandResponse()
{
	string tmp;

	tmp = _commandResponse.substr((_commandResponse.find('\n')+1),string::npos);
	tmp = tmp.substr(0, tmp.find('\r'));

	_responseData = tmp;

	cout << "Data: " << _responseData << endl;
}

void ObdScanner::ParseOBDCommandResponse()
{
	string expectedResponseForLastCommand = _lastCommand;
	expectedResponseForLastCommand[0] = '4';

	throw ("Not implemented");
}

#endif /* OBDSCANNER_CPP_ */
s

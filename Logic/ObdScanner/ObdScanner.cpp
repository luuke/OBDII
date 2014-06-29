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

void ObdScanner::PrintDeviceId()
{
	GetData(PRINT_ID);
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

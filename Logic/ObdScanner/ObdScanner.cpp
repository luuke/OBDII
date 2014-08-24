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
	_isCorrectReponse = false;
	_commandType = AT;
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
	cout << "ReadVehicleParameters" << endl;
	cout << ObdScanner::Speed << endl;
	cout << ObdScanner::Revolution << endl;
}

void ObdScanner::ReadVehicleSpeed()
{
	//ObdScanner::Speed = 120;
	string cmd;
	cmd.append(SHOW_CURRENT_DATA);
	cmd.append(VEHICLE_SPEED);
	GetObdData(cmd);
	ObdScanner::Speed = _responseData;
}

void ObdScanner::ReadVehicleRevolution()
{
	//ObdScanner::Revolution = 2400;
	string cmd;
	cmd.append(SHOW_CURRENT_DATA);
	cmd.append(ENGINE_RPM);
	GetObdData(cmd);
	ObdScanner::Revolution = _responseData / 4;
}

void ObdScanner::ReadVehicleVoltage()
{
	ObdScanner::Voltage = 14.5;
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
	//if (IsCorrectObdResponse())
	//{
		string data = _response.substr(10,4);
		stringstream ss;
		ss << hex << data;
		ss >> _responseData;
	//}
	_isReady = _response.find('>') != string::npos ? true : false;
}

bool ObdScanner::IsCorrectObdResponse()
{
	_obdResponseHeader = _command;
	_obdResponseHeader[0] = '4';

	_isCorrectReponse = _response.compare(0,4,_obdResponseHeader) ==  0 ? true : false;
	return _isCorrectReponse;
}

void ObdScanner::SendCommand(string command)
{
	_command = command;
	_serialPort.Write(command + "\r");
}

void ObdScanner::ReadResponse()
{
	bool continueReading = true;
	string singleMessage;

	_response.clear();
	while(continueReading)
	{
		singleMessage = _serialPort.Read();
		_response += singleMessage;
		//cout << singleMessage << endl;
		if(singleMessage.find_first_of('>') != string::npos)
		{
			_isReady = true;
			continueReading = false;
		}
	}

	_response.erase(std::remove(_response.begin(), _response.end(), ' '), _response.end());

	//while(_response.find_first_of(' ') != string::npos){

	//}
	//cout << "Command response: " << _response << endl;
}

void ObdScanner::ParseATCommandResponse()
{
	string tmp;

	tmp = _response.substr((_response.find('\n')+1),string::npos);
	tmp = tmp.substr(0, tmp.find('\r'));

	//_responseData = tmp;

	//cout << "Data: " << _responseData << endl;
}


#endif /* OBDSCANNER_CPP_ */

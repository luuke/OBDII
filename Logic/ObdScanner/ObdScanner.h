/*
 * ObdScanner.h
 *
 *  Created on: Jun 22, 2014
 *      Author: luuke
 */

#ifndef OBDSCANNER_H_
#define OBDSCANNER_H_

#include "../SerialPort/SerialPort.h"
#include "ATCommands.h"
#include <vector>

using namespace std;
using namespace SerialPortHandler;

namespace ObdScannerHandler
{
	enum CommandType
	{
		AT,
		OBD
	};

	class ObdScanner
	{
	public:
		ObdScanner();
		virtual ~ObdScanner();

//		void Restart();
//		void TurnOffEcho();
//		void TurnOnEcho();
//		void TurnOffHeaders();
//		void TurnOnHeaders();
//		void TurnOnLinefeeds();
//		void TurnOffLinefeeds();
		void PrintDeviceId();

//		int ReadVoltage();
//		int GetVehicleSpeed();
//		int ReadVehicleEngineRevolution();

	private:
		SerialPort _serialPort = SerialPort("/dev/ttyUSB0");
		bool _isReady;
		string _commandResponse;
		string _responseData;
		bool _isResponseForLastCommand;
		CommandType _lastCommandType;
		string _lastCommand;

		void GetData(string command);
		void SendATCommand(string command);
		void SendOBDCommand(string command);
		void SendCommand(string command);
		void SendCarriageReturnToReadyScanner();
		void ReadResponse();
		void ParseResponse();
		void ParseATCommandResponse();
		void ParseOBDCommandResponse();
	};
}



#endif /* OBDSCANNER_H_ */

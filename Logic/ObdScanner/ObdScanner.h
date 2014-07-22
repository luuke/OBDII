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
#include "ObdCommands.h"
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

		static int Speed;
		static int Revolution;
		static float Voltage;

		void Reset();
		void AutoSelectProtocol();

		void ReadVehicleParameters();

		void PrintDeviceId();


	private:
		SerialPort _serialPort = SerialPort("/dev/ttyUSB0");
		bool _isReady;
		string _response;
		string _obdResponseHeader;
		int _responseData;
		bool _isCorrectReponse;
		CommandType _commandType;
		string _command;

		void ReadVehicleSpeed();
		void ReadVehicleRevolution();
		void ReadVehicleVoltage();

		void GetObdData(string command);
		void ParseObdResponse();
		bool IsCorrectObdResponse();

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

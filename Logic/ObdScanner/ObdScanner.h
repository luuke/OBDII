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

using namespace std;
using namespace SerialPortHandler;

namespace ObdScannerHandler
{
	class ObdScanner
	{
	public:
		ObdScanner();
		virtual ~ObdScanner();

		void Restart();
		void TurnOffEcho();
		void TurnOnEcho();
		void TurnOffHeaders();
		void TurnOnHeaders();
		void TurnOnLinefeeds();
		void TurnOffLinefeeds();
		void ReadVoltage();

	private:
		SerialPort _serialPort = SerialPort("/dev/ttyUSB0");

		void SendMessage(string message);
		void ReceiveMessage();
	};
}



#endif /* OBDSCANNER_H_ */

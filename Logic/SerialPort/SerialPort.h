/*
 * SerialPort.h
 *
 *  Created on: Jun 18, 2014
 *      Author: luuke
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

//Serial port settings for ELM 327 OBDII scanner
//Baud rate: 38400
//Parity: none
//Bits: 8
//Stopbits: 1

using namespace std;

namespace SerialPortHandler
{
	class SerialPort
	{
	public:
		SerialPort(string path);
		virtual ~SerialPort();

		void Open();
		void Close();
		string Read();
		void Write(string message);
		void Configure();

	private:
		SerialPort();

		int _fileDescriptor;
		string _connectionString;
		char _receivedChar;
		string _receivedMessage;

		void ReadChar();
		void ReadString();
		void WriteChar(unsigned char c);
		void WriteString(string s);
	};
}

#endif /* SERIALPORT_H_ */

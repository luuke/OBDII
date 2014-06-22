/*
 * main.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: luuke
 */

#include <iostream>
#include <string>
#include "SerialPort/SerialPort.h"

using namespace std;
using namespace SerialPortHandler;

//TODO: Add 'set sysroot' in .gdbinit
//TODO: Why 'Cannot access memory at address 0x0' ?

int main()
{
	SerialPort serial("/dev/ttyUSB0");
	serial.Open();
	serial.Configure();
	serial.Write("ATI\r");
	cout << serial.Read() << endl;
	serial.Write("AT@1\r");
	cout << serial.Read() << endl;
	serial.Write("ATRV\r");
	cout << serial.Read() << endl;
	serial.Close();

	return 0;
}


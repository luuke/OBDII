/*
 * main.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: luuke
 */

#include <iostream>
#include <string>
#include "ObdScanner/ObdScanner.h"

using namespace std;
using namespace ObdScannerHandler;

//TODO: Add 'set sysroot' in .gdbinit
//TODO: Why 'Cannot access memory at address 0x0' ?

int main()
{
	ObdScanner _scanner;
	_scanner.PrintDeviceId();


	return 0;
}


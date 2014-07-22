/*
 * main.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: luuke
 */

#include <iostream>
#include <string>
#include "ObdScanner/ObdScanner.h"
#include "WebService/OBD.nsmap"


using namespace std;
using namespace ObdScannerHandler;

//TODO: Add 'set sysroot' in .gdbinit
//TODO: Why 'Cannot access memory at address 0x0' ?

int main()
{
	ObdScanner obdScanner;
	int master, slave;
	struct soap *soap = soap_new();
	master = soap_bind(soap, "192.168.1.3", 2014, 100);
	if(master < 0)
	{
		soap_print_fault(soap, stderr);
		exit(-1);
	}
	fprintf(stderr, "Socket connection successful: master socket = %d\n", master);
	int count = 0;
	for(;;)
	{
		obdScanner.ReadVehicleParameters();
		slave = soap_accept(soap);
		fprintf(stderr, "Socket connection successful: slave socket = %d\n", slave);
		cout << "Count: " << count++ << endl;
		if(slave < 0)
		{
			cout << "BP:1" << endl;
			soap_print_fault(soap, stderr);
			exit(1);
		}
		soap_serve(soap);
		soap_end(soap);
	}
	soap_done(soap);
	free(soap);

	return 0;
}

int OBD__GetSpeed(struct soap* soap, int& speed)
{
	static int i = 0;
	speed = i;
	i += 10;
	if (i > 200) i = 0;
	cout << "Speed served: " << speed << endl;
	return SOAP_OK;
}

int OBD__GetReadings(struct soap* soap, OBD__Readings& readings)
{
	static int i = 0;
	readings.speed = ObdScanner::Speed;
	readings.revolution = ObdScanner::Revolution;
	readings.voltage = ObdScanner::Voltage;
	cout << ">>> Readings served (" << i++ << ")" << endl;
	cout << "Speed: " << readings.speed << "(" <<  ObdScanner::Speed << ")"<< endl;
	cout << "Revolution: " << readings.revolution << "(" <<  ObdScanner::Revolution << ")"<< endl;
	cout << "Voltage: " << readings.voltage << "(" <<  ObdScanner::Voltage << ")"<< endl;
	return SOAP_OK;
}

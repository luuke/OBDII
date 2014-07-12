/*
 * main.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: luuke
 */

#include <iostream>
#include <string>
#include "ObdScanner/ObdScanner.h"
//#include "WebService/WebService.h"

//#include "WebService/soapH.h"
#include "WebService/OBD.nsmap"

using namespace std;
using namespace ObdScannerHandler;
//using namespace WebServiceHandler;

//TODO: Add 'set sysroot' in .gdbinit
//TODO: Why 'Cannot access memory at address 0x0' ?

int main()
{
	int master, slave;
	struct soap *soap = soap_new();
	master = soap_bind(soap, "192.168.0.4", 2014, 100);
	if(master < 0)
	{
		soap_print_fault(soap, stderr);
		exit(-1);
	}
	fprintf(stderr, "Socket connection successful: master socket = %d\n", master);
	int count = 0;
	for(;;)
	{
		slave = soap_accept(soap);
		fprintf(stderr, "Socket connection successful: slave socket = %d\n", slave);
		cout << "Count: " << count++ << endl;
		if(slave < 0)
		{
			cout << "BP:1" << endl;
			soap_print_fault(soap, stderr);
			exit(1);
		}
		cout << "BP:2" << endl;
		soap_serve(soap);
		cout << "BP:3" << endl;
		soap_end(soap);
	}
	soap_done(soap);
	free(soap);

	return 0;
}

int OBD__GetSpeed(struct soap* soap, int& speed)
{
	speed = 69;
	cout << "GetSpeed OK" << endl;
	return SOAP_OK;
}

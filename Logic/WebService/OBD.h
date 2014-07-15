//gsoap ns service name: OBD
//gsoap ns service encoding: literal

//gsoap ns service namespace: http://192.168.1.3/OBD.wsdl
//gsoap ns service location: http://192.168.1.3:2014

//gsoap ns schema namespace urn:OBD
class OBD__Readings
{
public:
	int speed;
	int revolution;
	int voltage;
};
int OBD__GetSpeed(int& speed);
int OBD__GetReadings(OBD__Readings& readings);

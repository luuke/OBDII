//gsoap ns service name: OBDII readings
//gsoap ns service encoding: literal

//gsoap ns service namespace: http://192.168.0.3/readings.wsdl
//gsoap ns service location: http://192.168.0.3:2014

//gsoap ns schema namespace urn:readings
int ns__getspeed(int& speed);
int ns__getenginerevolution(int& revolution);
int ns__getvoltage(int& voltage);

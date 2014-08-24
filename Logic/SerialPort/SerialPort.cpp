/*
 * SerialPort.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: luuke
 */

#include "SerialPort.h"

using namespace SerialPortHandler;

SerialPort::SerialPort(string path){
	_fileDescriptor = NULL;
	_connectionString = path;
}

SerialPort::~SerialPort(){

}

void SerialPort::Open(){
	try
	{
		_fileDescriptor = open(_connectionString.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
		fcntl (_fileDescriptor, F_SETFL, O_RDWR) ;
	}
	catch(exception &ex)
	{
		cerr << ex.what();
	}
}

void SerialPort::Close(){
	try
	{
		close(_fileDescriptor);
	}
	catch(exception &ex)
	{
		cerr << ex.what();
	}
}

string SerialPort::Read()
{
	try
	{
		ReadString();
	}
	catch(exception &ex)
	{
		cerr << ex.what();
	}
	return _receivedMessage;
}

void SerialPort::Write(string message){
	try
	{
		WriteString(message);
	}
	catch(exception &ex)
	{
		cerr << ex.what();
	}
}

void SerialPort::Configure()
{
	struct termios tty;
	int status;

	memset(&tty,0,sizeof(tty));

	if(tcgetattr(_fileDescriptor,&tty)!=0){
		cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << endl;
	}

	tcgetattr (_fileDescriptor, &tty) ;

	cfmakeraw   (&tty) ;
	cfsetispeed (&tty, (speed_t)B38400) ;
	cfsetospeed (&tty, (speed_t)B38400) ;

	tty.c_cflag |= (CLOCAL | CREAD) ;
	tty.c_cflag &= ~PARENB ;
	tty.c_cflag &= ~CSTOPB ;
	tty.c_cflag &= ~CSIZE ;
	tty.c_cflag |= CS8 ;
	tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;
	tty.c_oflag &= ~OPOST ;

	tty.c_cc [VMIN]  =   0 ;
	tty.c_cc [VTIME] = 10 ;	// One second (10 deciseconds)

	tcsetattr (_fileDescriptor, TCSANOW | TCSAFLUSH, &tty) ;

	ioctl (_fileDescriptor, TIOCMGET, &status);

	status |= TIOCM_DTR ;
	status |= TIOCM_RTS ;

	ioctl (_fileDescriptor, TIOCMSET, &status);

	usleep (10000);
}

void SerialPort::ReadChar()
{
	int n;

	n = read(_fileDescriptor, &_receivedChar, 1);
	//cout << (int)_receivedChar << endl;
	if(n == 0)
	{
		_receivedChar = NULL;
	}
	else if (n < 0)
	{
		_receivedChar = NULL;
		throw ("Error reading char: " + errno);
	}
}

void SerialPort::ReadString()
{
	bool readOneChar = true;
	int attempts = 0;
	_receivedMessage.clear();

	while (readOneChar) {
		ReadChar();
		if (_receivedChar == '\0'){
			attempts++;
			if(attempts == 5)
			{
				readOneChar = false;
			}
		}
		if (_receivedChar == '\n' || _receivedChar == '\r' || _receivedChar == '>')
		{
			readOneChar = false;
		}
		_receivedMessage.push_back(_receivedChar);
	}
}

void SerialPort::WriteChar(unsigned char c)
{
	write(_fileDescriptor, &c, 1);
}

void SerialPort::WriteString(string message)
{
	for (char &c : message){
		WriteChar(c);
	}
}

#include "uart.h"

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>

#ifdef unix
#include <termios.h>
#include <unistd.h>
#endif
#ifdef WIN32
#include <Windows.h>
#endif

/*
 #ifdef WIN32

 #endif
 #ifdef unix

 #endif
 */

Uart::Uart(string portName)
{
    _portName = portName;
}

Uart::~Uart()
{
    closeDevice();
}

int Uart::openDevice()
{
#ifdef WIN32
    std::wstring portname_wstring = std::wstring( _portName.begin(), _portName.end() );
    LPCWSTR portname_cwstring = portname_wstring.c_str();
    _device = CreateFile( portname_cwstring, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if ( _device == INVALID_HANDLE_VALUE)
    {
        if ( GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            _device = NULL;
        }
        _device = NULL;
    }
#endif
#ifdef unix
    int fd = open(_portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd != -1) {
        _device = malloc(sizeof(int));
        *((int*)_device) = fd;
    }
#endif
    return _device != NULL;
}

void Uart::setPortName(string port_name) {
    _portName = port_name;
}

void Uart::send(string data)
{
    string datas = data;
    datas+="\n";
    if ( isDeviceOpen() ) {
#ifdef WIN32
        unsigned long cmpt_read;
        if (!WriteFile( _device, datas.c_str(), datas.size(), &cmpt_read, NULL)) {
        }
#endif
#ifdef unix
        write ( *((int*)(_device)) , datas.c_str(), datas.size());
#endif

    }
}

void Uart::send(int data)
{
#ifdef WIN32
    if (!WriteFile( _device, &data, 1, NULL, NULL)) {

    }

#endif
#ifdef unix
    write ( *(int*)_device , &data, 1);
#endif
}

void Uart::closeDevice()
{
    if ( isDeviceOpen() ) {
#ifdef WIN32
        CloseHandle( (HANDLE)_device );
#endif
#ifdef unix
        close( *(int*)_device );
        free(_device);
#endif
    }
    _device = NULL;
}
bool Uart::isDeviceOpen()
{
    return _device != NULL;
}

bool Uart::readData()
{
    unsigned long cmpt_read = 0;
    char buf[4096] = {0};
    if ( !isDeviceOpen() )
        return false;
#ifdef WIN32
    if (!ReadFile( _device, buf, 4096, &cmpt_read, NULL))
    {
        int LastError = GetLastError() ;
        cerr<<"Error read file : "<<LastError<<endl;
        return false;
    }
#endif
#ifdef unix
    cmpt_read = read (*(int*)_device, buf, 4096);
#endif
    if ( cmpt_read > 0) {
        if ( buf[cmpt_read-1] =='\n' && buf[cmpt_read-2] =='\n' ) {
            buf[cmpt_read-1] ='\0';
            _bufferedData.append( buf );
            return true;
        }
        else {
            _bufferedData.append( buf );
        }
    }
    else {
        return false;
    }
}
string Uart::getData() {
    string data = _bufferedData;
    _bufferedData = "";
    return data;
}

int Uart::uartBaudRate2int( Uart::baud_rate baudrate)
{
#ifdef WIN32
    switch( baudrate )
    {
    case Uart::BR9600 :
        return CBR_9600;
        break;
    case Uart::BR57600 :
        return CBR_57600;
        break;
    case Uart:: BR115200:
        return CBR_115200;
        break;
    default :
        return CBR_9600;
        break;
    }
#endif
#ifdef unix
    switch( baudrate )
    {
    case Uart::BR9600 :
        return B9600;
        break;
    case Uart::BR57600 :
        return B57600;
        break;
    case Uart:: BR115200:
        return B115200;
        break;
    case Uart::BR230400 :
        return B230400;
        break;
    case Uart::BR460800 :
        return B460800;
        break;
    case Uart::BR500000 :
        return B500000;
        break;
    case Uart::BR576000 :
        return B576000;
        break;
    case Uart::BR921600 :
        return B921600;
        break;
    case Uart::BR1000000 :
        return B1000000;
        break;
    case Uart::BR1152000 :
        return B1152000;
        break;
    case Uart::BR1500000 :
        return B1500000;
        break;
    case Uart::BR2000000 :
        return B2000000;
        break;
    case Uart::BR2500000 :
        return B2500000;
        break;
    case Uart::BR3000000 :
        return B3000000;
        break;
    case Uart::BR3500000 :
        return B3500000;
        break;
    case Uart::BR4000000 :
        return B4000000;
        break;
    default :
        return B115200;
        break;
    }
#endif
}

int Uart::setInterfaceAttrib ( Uart::baud_rate speed, int parity )
{

#ifdef WIN32

    DCB dcbSerialParams = {0};
    // set com port settings
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState( _device, &dcbSerialParams))
    {
        cout<<"Error get setting"<<endl;
    }
    dcbSerialParams.BaudRate = uartBaudRate2int(speed);
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = parity;
    if (!SetCommState(_device, &dcbSerialParams))
    {
        cout<<"Error set setting"<<endl;
    }
#endif
#ifdef unix
     struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (*(int*)_device, &tty) != 0)
    {
        return -1;
    }

    cfsetospeed ( &tty, uartBaudRate2int(speed) );
    cfsetispeed ( &tty, uartBaudRate2int(speed) );

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // ignore break signal
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (*(int*)_device, TCSANOW, &tty) != 0)
    {
        return -1;
    }
    return 0;
#endif
    return -1;
}


void Uart::setBlocking ( int should_block )
{
#ifdef WIN32
    COMMTIMEOUTS timeouts={0};
    // set com port timeouts
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(_device, &timeouts))
    {
        cout<<"Error setting timeout"<<endl;
//        msg.setText("Could not set GPS COM port timeouts!");
    }
#endif
#ifdef unix
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (*(int*)_device, &tty) != 0)
    {
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (*(int*)_device, TCSANOW, &tty) != 0)
        return;
#endif
}


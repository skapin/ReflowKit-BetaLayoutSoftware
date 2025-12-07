#ifndef UART_H
#define UART_H
/**
 * @brief The Uart class
 *
 *
 * @url http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
 *
 *
 * The values for speed are B115200, B230400, B9600, B19200, B38400, B57600, B1200, B2400, B4800, etc.
 * The values for parity are 0 (meaning no parity), PARENB|PARODD (enable parity and use odd), PARENB
 * (enable parity and use even), PARENB|PARODD|CMSPAR (mark parity), and PARENB|CMSPAR (space parity).
 * "Blocking" sets whether a read() on the port waits for the specified number of characters to arrive.
 * Setting no blocking means that a read() returns however many characters are available without waiting
 * for more, up to the buffer limit.
 */


#include <errno.h>
#ifdef UNIX
    #include <termios.h>
    #include <unistd.h>
#endif
#ifdef WIN32
    #include <Windows.h>
#endif
#include <cstdlib>
#include <string>
#include <stdio.h>

#include <fcntl.h>

using namespace std;


class Uart
{
public:
    enum baud_rate {
        BR9600, BR57600, BR115200, BR230400, BR460800,  BR500000,  BR576000,  BR921600, BR1000000,
        BR1152000, BR1500000, BR2000000, BR2500000, BR3000000, BR3500000, BR4000000
    };

    Uart( string portName="" );
    ~Uart();

    int openDevice();
    void setPortName( string port_name );
    void closeDevice();
    bool isDeviceOpen();
    int setInterfaceAttrib (Uart::baud_rate speed, int parity );
    void setBlocking ( int should_block );
    int uartBaudRate2int( Uart::baud_rate baudrate);

    void send( string data );
    void send(int data);
    bool readData( );
    string getData();

private:
    string _portName;
    string _bufferedData;
    void* _device = NULL;
    baud_rate _currentBaudRate = Uart::BR115200;
};

#endif // UART_H


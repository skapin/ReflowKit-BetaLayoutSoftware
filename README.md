ReflowKit-BetaLayoutSoftware
============================

Software for beta layout reflow kit. UART interface With simple GUI

Contact
============================
Florian Boudinet
florian.boudinet@gmail.com


Package
============================

This software need :
-Qt > 4.x
    sudo apt-get install qt4-dev-tools libqt4-dev libqt4-core libqt4-gui
    OR 
    sudo apt-get install qtcreator
    OR
    http://qt.digia.com/Try-Qt-Now/
    Note : Qt5 is now available, enjoy :)
    
-Qwt
    http://qwt.sourceforge.net/
    svn checkout svn://svn.code.sf.net/p/qwt/code/branches/qwt-6.0 

Compilation
============================

cd ${ReflowKitSource}/
qmake
make
./ReflowKitController

Troubleshooting with the compilation :
    Perhpase you will to edit ths .pro file, to add and link properly Qwt, and feet 
    with your settings (LD_PATH, QWT source etc...)


Uart
============================
the software use the SR232 Uart protocol to communicate with the device.
    Configuration : 9600 bauds, no parity, 1bit stop
    Path :  For Linux, something like /dev/ttyUSBX 
            For Windows, something like COM4, COM1 ...

Perhapse you will need to add some right to use Uart properly (root privilege, or add the current user to the /dev/tty permission)


#ifndef REFLOWCONTROLLER_H
#define REFLOWCONTROLLER_H

#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <QRegExp>
#include <QStringList>

#include "uart.h"

using namespace std;

class ReflowController
{
public:
    ReflowController();

    string getAllInformation();
    bool openDevice( string path );
    void closeDevice();
    Uart* getUartDevice();

    void parseUart();

    void setPhtTemp( int v );
    void setPhtTime( int v );
    void setPhtPwr( int v );

    void setSoakTemp( int v );
    void setSoakTime( int v );
    void setSoakPwr( int v );

    void setReflowTemp( int v );
    void setReflowTime( int v );
    void setReflowPwr( int v );

    void setDwellTemp( int v );
    void setDwellTime( int v );
    void setDwellPwr( int v );

    void setTempoffset( int v );
    void setTempShow( int v );

    int getPhtTemp(  );
    int getPhtTime(  );
    int getPhtPwr(  );

    int getSoakTemp(  );
    int getSoakTime(  );
    int getSoakPwr(  );

    int getReflowTemp(  );
    int getReflowTime(  );
    int getReflowPwr(  );

    int getDwellTemp( );
    int getDwellTime( );
    int getDwellPwr(  );

    int getTempoffset(  );
    int getTempShow( );

    int getCurrentTemp();

    QStringList* getDatas();

private:
    int _phttemp;
    int _phttime;
    int _phtpwr;

    int _soaktemp;
    int _soaktime;
    int _soakpwr;

    int _reflowtemp;
    int _reflowtime;
    int _reflowpwr;

    int _dwelltemp;
    int _dwelltime;
    int _dwellpwr;

    int _tempoffset;
    int _tempshow;

    int _currentTemp;
    Uart* _uart;
    static int MAX_DATAS_STORED;
    QStringList* _datas;

};

#endif // REFLOWCONTROLLER_H

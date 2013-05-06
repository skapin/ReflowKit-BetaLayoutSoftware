#include "reflowcontroller.h"


int ReflowController::MAX_DATAS_STORED = 16;

ReflowController::ReflowController()
{
    _phttemp=0;
    _phttime=0;
    _phtpwr=0;

    _soaktemp=0;
    _soaktime=0;
    _soakpwr=0;

    _reflowtemp=0;
    _reflowtime=0;
    _reflowpwr=0;

    _dwelltemp=0;
    _dwelltime=0;
    _dwellpwr=0;

    _tempoffset=0;
    _currentTemp=0;
    _tempshow=2;

    _datas = new QStringList();
    _uart = new Uart();
}

bool ReflowController::openDevice(string path) {
    _uart = new Uart( path );
    if ( _uart->openDevice() < 0 )
    {
        return false;
    }
    else
    {
        _uart->setInterfaceAttrib(Uart::BR9600, 0);
        _uart->setBlocking(0);
    }
    return _uart->isDeviceOpen();
}

QStringList* ReflowController::getDatas() {
    return _datas;
}

void ReflowController::parseUart( ) {

    if ( ! _uart->isDeviceOpen() )
    {
        return;
    }
    QRegExp temp_reg("(OFF|ON),\\s*(\\d+),\\s*.(\\d+),\\s*degC");
    QRegExp config_reg("([a-z]{3,})\\s*(\\d{1,})");

    QString d(  (_uart->readData()).c_str() );

    // Is the buffer Full ? (prevent Leak of memory and too much RAM used)
    if ( d.size() > ReflowController::MAX_DATAS_STORED )
        d.remove( 0,5 );
    _datas->append( d );

    //*********TEMP***********

    if (d.contains(temp_reg) ) {
        _currentTemp = temp_reg.cap(1).toInt();
        cout<<temp_reg.cap(3).toInt()<<" ==>CurrentTemp"<<endl;

    }
    else
        cout<<"IsNotTemp"<<endl;

    //********CONFIG**********
    if ( d.contains(config_reg) ) {
        cout<<config_reg.cap(0).toStdString()<<" <-Variable | Value-> "<<config_reg.cap(2).toInt()<<endl;

    }
    else
        cout<<"IsNoConfig"<<endl;


}

Uart* ReflowController::getUartDevice() {
    return _uart;
}

void ReflowController::closeDevice() {
    _uart->closeDevice();
}

string ReflowController::getAllInformation()
{
    return "";
}


//******************** SET/GET***********************************************

int ReflowController::getCurrentTemp() {
    return _currentTemp;
}

void ReflowController::setPhtTemp( int v ) {
    if ( v >= 0 &&  v <= 254 )
        _phttemp = v;
}

void ReflowController::setPhtTime( int v ) {
    if ( v >= 0 &&  v <= 65534 )
        _phttime = v;
}

void ReflowController::setPhtPwr( int v ) {
    if ( v >= 0 &&  v <= 100 )
        _phtpwr = v;
}
void ReflowController::setSoakTemp( int v ) {
    if ( v >= 0 &&  v <= 254 )
        _soaktemp = v;
}
void ReflowController::setSoakTime( int v ) {
    if ( v >= 0 &&  v <= 65534 )
        _soaktime = v;
}
void ReflowController::setSoakPwr( int v ) {
    if ( v >= 0 &&  v <= 100 )
        _soakpwr = v;
}

void ReflowController::setReflowTemp( int v ) {
    if ( v >= 0 &&  v <= 254 )
        _reflowtemp = v;
}
void ReflowController::setReflowTime( int v ) {
    if ( v >= 0 &&  v <= 65534 )
        _reflowtime = v;
}
void ReflowController::setReflowPwr( int v ) {
    if ( v >= 0 &&  v <= 100 )
        _reflowpwr = v;
}

void ReflowController::setDwellTemp( int v ) {
    if ( v >= 0 &&  v <= 254 )
        _dwelltemp = v;
}
void ReflowController::setDwellTime( int v ) {
    if ( v >= 0 &&  v <= 65534 )
        _dwelltime = v;
}
void ReflowController::setDwellPwr( int v ) {
   if ( v >= 0 &&  v <= 100 )
       _dwellpwr = v;
}


void ReflowController::setTempoffset( int v ) {
    if ( v >= -30 &&  v <= 30 )
        _tempoffset = v;
}

void ReflowController::setTempShow( int v ) {
   if ( v >= 0 &&  v <= 1000 )
       _tempshow = v;
}


int ReflowController::getPhtTemp(  ) {
    return _phttemp;
}

int ReflowController::getPhtTime(  ) {
    return _phttime;
}
int ReflowController::getPhtPwr(  ) {
    return _phtpwr;
}

int ReflowController::getSoakTemp(  ) {
    return _soaktemp;
}
int ReflowController::getSoakTime(  ) {
    return _soaktime;
}
int ReflowController::getSoakPwr(  ) {
    return _soakpwr;
}

int ReflowController::getReflowTemp(  ) {
    return _reflowtemp;
}
int ReflowController::getReflowTime(  ) {
    return _reflowtime;
}
int ReflowController::getReflowPwr(  ) {
    return _reflowpwr;
}

int ReflowController::getDwellTemp( ) {
    return _dwelltemp;
}
int ReflowController::getDwellTime( ) {
    return _dwelltime;
}
int ReflowController::getDwellPwr(  ) {
    return _dwellpwr;
}

int ReflowController::getTempoffset(  ) {
    return _tempoffset;
}
int ReflowController::getTempShow( ) {
    return _tempshow;
}

#include "reflowcontroller.h"


int ReflowController::MAX_DATAS_STORED = 32;

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
        _uart->send("showall");
    }
    return _uart->isDeviceOpen();
}

QStringList* ReflowController::getDatas() {
    return _datas;
}

void ReflowController::checkUartDataReady() {
    if ( ! _uart->isDeviceOpen() )
    {
        return;
    }
    // is some UartData ready ?
    if (_uart->readData() ) {
        // Is the buffer Full ? (prevent Leak of memory and too much RAM used)
        if ( _datas->size() > ReflowController::MAX_DATAS_STORED ) {
            for ( int i=5; i>=0 ; i--) {
                _datas->removeAt(i);
            }

        }
        _datas->append( QString(_uart->getData().c_str()) );
        parseUart( _datas->last().toStdString() );
        // Addd uart data ready and delete them from Uart class (see Uart->getData())
    }
}

void ReflowController::parseUart( string data ) {

    QRegExp temp_reg("(OFF|ON),\\s*(\\d+),\\s*.(\\d+),\\s*degC");
    QRegExp config_reg("([a-z]{3,})\\s*(\\d{1,})");

    QString d( data.c_str() ) ;




    //*********TEMP***********

    if (d.contains(temp_reg) ) {
        _currentTemp = temp_reg.cap(3).toInt();
        cout<<temp_reg.cap(3).toInt()<<" ==>CurrentTemp"<<endl;

    }
    //********CONFIG**********
    //if ( d.contains(config_reg) ) {
    int pos = 0;
    while ( (pos=config_reg.indexIn( d , pos )) != -1 ) {
        //cout<<config_reg.cap(1).toStdString()<<"VALUE"<<config_reg.cap(2).toStdString()<<endl;
        pos += config_reg.matchedLength();
        string variable_name = config_reg.cap(1).toStdString();
        int value = config_reg.cap(2).toInt();

        if ( variable_name.compare("phttemp") == 0 )
            _phttemp = value;
        else if ( variable_name.compare("phttime") == 0 )
            _phttime = value;
        else if ( variable_name.compare("phtpwr") == 0 )
            _phtpwr = value;
        else if ( variable_name.compare("soaktemp") == 0 )
            _soaktemp = value;
        else if ( variable_name.compare("soaktime") == 0 )
            _soaktime = value;
        else if ( variable_name.compare("soakpwr") == 0 )
            _soakpwr = value;
        else if ( variable_name.compare("reflowtemp") == 0 )
            _reflowtemp = value;
        else if ( variable_name.compare("reflowtime") == 0 )
            _reflowtime = value;
        else if ( variable_name.compare("reflowpwr") == 0 )
            _reflowpwr = value;
        else if ( variable_name.compare("dwelltemp") == 0 )
            _dwelltemp = value;
        else if ( variable_name.compare("dwelltime") == 0 )
            _dwelltime = value;
        else if ( variable_name.compare("dwellpwr") == 0 )
            _dwellpwr = value;
        else
            cout<<"UNKNOWN"<< variable_name <<endl;
    }

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
    if ( v >= 0 &&  v <= 254 ) {
        _phttemp = v;
        _uart->send("phttemp"+QString::number(v).toStdString());
    }
}

void ReflowController::setPhtTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _phttime = v;
        _uart->send("phttime"+QString::number(v).toStdString());
    }
}

void ReflowController::setPhtPwr( int v ) {
    if ( v >= 0 &&  v <= 100 ) {
        _phtpwr = v;
        _uart->send("phtpwr"+QString::number(v).toStdString());
    }
}
void ReflowController::setSoakTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _soaktemp = v;
        _uart->send("soaktemp"+QString::number(v).toStdString());
    }
}
void ReflowController::setSoakTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _soaktime = v;
        _uart->send("soaktime"+QString::number(v).toStdString());
    }
}
void ReflowController::setSoakPwr( int v ) {
    if ( v >= 0 &&  v <= 100 ) {
        _soakpwr = v;
        _uart->send("soaktpwr"+QString::number(v).toStdString());
    }
}

void ReflowController::setReflowTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _reflowtemp = v;
        _uart->send("reflowtemp"+QString::number(v).toStdString());
    }
}
void ReflowController::setReflowTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _reflowtime = v;
        _uart->send("reflowtime"+QString::number(v).toStdString());
    }
}
void ReflowController::setReflowPwr( int v ) {
    if ( v >= 0 &&  v <= 100 ) {
        _reflowpwr = v;
        _uart->send("reflowpwr"+QString::number(v).toStdString());
    }
}

void ReflowController::setDwellTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _dwelltemp = v;
        _uart->send("dwelltemp"+QString::number(v).toStdString());
    }
}
void ReflowController::setDwellTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _dwelltime = v;
        _uart->send("dwelltime"+QString::number(v).toStdString());
    }
}
void ReflowController::setDwellPwr( int v ) {
   if ( v >= 0 &&  v <= 100 ) {
       _dwellpwr = v;
       _uart->send("dwellpwr"+QString::number(v).toStdString());
   }
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

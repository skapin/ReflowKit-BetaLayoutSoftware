#include "reflowcontroller.h"

int ReflowController::MAX_DATAS_STORED = 16;
int ReflowController::MAX_SIZE_TEMP_LIST=4096;

ReflowController::ReflowController(QObject *parent) : QObject(parent)
{
    _datas = new QStringList();
    _uart = new Uart();
}

void ReflowController::startLearning() {
    _uart->send("learn");
}

void ReflowController::updateInformation() {
    _uart->send("showall");
}

bool ReflowController::openDevice(string path) {
    _uart = new Uart( path );
    if (_uart->openDevice())
    {
        _uart->setInterfaceAttrib(Uart::BR9600, 0);
        _uart->setBlocking(0);
    }
    else
    {
        return false;
    }
    return _uart->isDeviceOpen();
}

void ReflowController::resetTimeTemps() {
    _temps.clear();
    _times.clear();
}

void ReflowController::exportCSV(string path, char separator ) {
    ofstream csv_file( path.c_str(), ios::out | ios::trunc);

    if(csv_file)
    {
        int size = _temps.size();
        if ( size == _times.size() ) {
            for ( int i=0; i < size ; ++i) {
                csv_file << _times.at( i ) << separator << _temps.at(i) <<endl;
            }

        }
        csv_file.close();
    }
    else  // sinon
        cerr << "Error while opening CSV file " << path << endl;
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

void ReflowController::addTemp(double temp, double time) {
    if (_temps.size() >= MAX_SIZE_TEMP_LIST ) {
        _temps.remove(0,1);
        _times.remove(0,1);
    }
    _times.append( time );
    _temps.append( temp );
    if ( _times.first() > time )
        resetTimeTemps();
}

void ReflowController::parseUart( string data ) {
    QRegExp temp_reg("(OFF|ON|Soak|Preheat|Reflow|Dwell|learn|Learn),\\s*(\\d+),\\s*.(\\d+),\\s*(degC|C)");
    QRegExp config_reg("([a-z+-]{3,})\\s*(\\d{1,})");

    QString d( data.c_str() ) ;
    int pos = 0;

    //*********TEMP***********
    pos = 0;
    while ( (pos=temp_reg.indexIn( d , pos )) != -1 ) {
        pos += temp_reg.matchedLength();

        _currentTemp = temp_reg.cap(3).toInt();
        addTemp( (double)(temp_reg.cap(3).toInt()), (double)(temp_reg.cap(2).toInt()) );
        state = temp_reg.cap(1).toStdString();
    }
    //********CONFIG**********
    pos = 0;
    while ( (pos=config_reg.indexIn( d , pos )) != -1 ) {
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
        else if ( variable_name.compare("tempoffset+") == 0 )
            _tempoffset = value;
        else if ( variable_name.compare("tempoffset-") == 0 )
            _tempoffset = -value;
        else if ( variable_name.compare("tempoffset") == 0 )
            _tempoffset = value;
    }
}

void ReflowController::closeDevice() {
    _temps.clear();
    _times.clear();
    _uart->closeDevice();
}

//******************** SET/GET***********************************************

void ReflowController::setPhtTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _phttemp = v;
        _uart->send("phttemp "+QString::number(v).toStdString());
    }
}

void ReflowController::setPhtTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _phttime = v;
        _uart->send("phttime "+QString::number(v).toStdString());
    }
}

void ReflowController::setPhtPwr( int v ) {
    if ( v >= 0 &&  v <= 100 ) {
        _phtpwr = v;
        _uart->send("phtpwr "+QString::number(v).toStdString());
    }
}

void ReflowController::setSoakTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _soaktemp = v;
        _uart->send("soaktemp "+QString::number(v).toStdString());
    }
}

void ReflowController::setSoakTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _soaktime = v;
        _uart->send("soaktime "+QString::number(v).toStdString());
    }
}

void ReflowController::setSoakPwr( int v ) {
    if ( v >= 0 &&  v <= 100 ) {
        _soakpwr = v;
        _uart->send("soaktpwr "+QString::number(v).toStdString());
    }
}

void ReflowController::setReflowTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _reflowtemp = v;
        _uart->send("reflowtemp "+QString::number(v).toStdString());
    }
}

void ReflowController::setReflowTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _reflowtime = v;
        _uart->send("reflowtime "+QString::number(v).toStdString());
    }
}

void ReflowController::setReflowPwr( int v ) {
    if ( v >= 0 &&  v <= 100 ) {
        _reflowpwr = v;
        _uart->send("reflowpwr "+QString::number(v).toStdString());
    }
}

void ReflowController::setDwellTemp( int v ) {
    if ( v >= 0 &&  v <= 254 ) {
        _dwelltemp = v;
        _uart->send("dwelltemp "+QString::number(v).toStdString());
    }
}

void ReflowController::setDwellTime( int v ) {
    if ( v >= 0 &&  v <= 65534 ) {
        _dwelltime = v;
        _uart->send("dwelltime "+QString::number(v).toStdString());
    }
}

void ReflowController::setDwellPwr( int v ) {
   if ( v >= 0 &&  v <= 100 ) {
       _dwellpwr = v;
       _uart->send("dwellpwr "+QString::number(v).toStdString());
   }
}

void ReflowController::setTempoffset( int v ) {
    if ( v >= -30 &&  v <= 30 ) {
        _tempoffset = v;
        _uart->send("tempoffset "+QString::number(v).toStdString());
    }
}

void ReflowController::setTempShow( int v ) {
   if ( v >= 0 &&  v <= 1000 )
       _tempshow = v;
}

QStringList* ReflowController::getDatas() { return _datas; }
QVector<double>* ReflowController::getTemps() { return &_temps; }
QVector<double>* ReflowController::getTimes() { return &_times; }
Uart* ReflowController::getUartDevice() { return _uart; }
int ReflowController::getCurrentTemp() { return _currentTemp; }
int ReflowController::getPhtTemp() const { return _phttemp; }
int ReflowController::getPhtTime() const { return _phttime; }
int ReflowController::getPhtPwr() const { return _phtpwr; }
int ReflowController::getSoakTemp() const { return _soaktemp; }
int ReflowController::getSoakTime() const { return _soaktime; }
int ReflowController::getSoakPwr() const { return _soakpwr; }
int ReflowController::getReflowTemp() const { return _reflowtemp; }
int ReflowController::getReflowTime() const { return _reflowtime; }
int ReflowController::getReflowPwr() const { return _reflowpwr; }
int ReflowController::getDwellTemp() const { return _dwelltemp; }
int ReflowController::getDwellTime() const { return _dwelltime; }
int ReflowController::getDwellPwr() const { return _dwellpwr; }
int ReflowController::getTempoffset() const { return _tempoffset; }
int ReflowController::getTempShow() const { return _tempshow; }

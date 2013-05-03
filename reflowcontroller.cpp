#include "reflowcontroller.h"

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
}

string ReflowController::getAllInformation()
{
    return "";
}

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

void ReflowController::setDwellTemp( int v )
{
    if ( v >= 0 &&  v <= 254 )
        _dwelltemp = v;
}
void ReflowController::setDwellTime( int v )
{
    if ( v >= 0 &&  v <= 65534 )
        _dwelltime = v;
}
void ReflowController::setDwellPwr( int v )
{
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

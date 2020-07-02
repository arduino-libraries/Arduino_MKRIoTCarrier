
#include <Arduino_IOTSK_Qtouch.h>
#include "Arduino_Qtouch.h"


//Individual pad
IOTSKcarrier_Qtouch::IOTSKcarrier_Qtouch(int padIndex, IOTSKcarrier_Qtouch_Manager * pManager){
    _padIndex = padIndex;
    _pManager = pManager;
}


bool IOTSKcarrier_Qtouch::getTouch(){
    bool getState = _pManager->t_state[_padIndex];
    _saveToHistory(getState);
    return(getState);
}

void IOTSKcarrier_Qtouch::_saveToHistory(bool newEntry){
    //Serial.println(_padIndex);
    for (int i = 10; i>0; i--){
        _touches[i]  = _touches[i -1];
       /* Serial.print(i);
        Serial.print(" = ");
        Serial.println( _touches[i]);*/
    }
    _touches[0] = newEntry;
    /*
    Serial.print(0);
    Serial.print(" = ");
    Serial.println( _touches[0]);*/
}

bool IOTSKcarrier_Qtouch::onTouchDown(){
    getTouch();
    //Serial.print(_touches[0]);
    //Serial.print(_touches[1]);
    //Serial.println();
    if(_touches[0] && !_touches[1]){
        return true;
    }else{
        return false;
    }
}
bool IOTSKcarrier_Qtouch::onTouchUp(){
    getTouch();
    //Serial.print(_touches[0]);
    //Serial.print(_touches[1]);
    //Serial.println();
    if(!_touches[0] && _touches[1]){
        return true;
    }else{
        return false;
    }
}
bool IOTSKcarrier_Qtouch::onTouchChange(){
    getTouch();
    //Serial.print(_touches[0]);
    //Serial.print(_touches[1]);
    //Serial.println();
    if(_touches[0] != _touches[1]){
        return true;
    }else{
        return false;
    }
}

void IOTSKcarrier_Qtouch::updateConfig(int newSens){
    TOUCH.setSensorsSensitivity(newSens);
    //TOUCH.setSernsorsHysteresis(newHyst);
}

//Manager
bool IOTSKcarrier_Qtouch_Manager::begin(){
return TOUCH.begin();
}
IOTSKcarrier_Qtouch_Manager::IOTSKcarrier_Qtouch_Manager(){

}
void IOTSKcarrier_Qtouch_Manager::update(){
    TOUCH .poll();
    if(TOUCH.available()){
        t_state[0] = TOUCH.read(0);
        t_state[1] = TOUCH.read(1);
        t_state[2] = TOUCH.read(2);
        t_state[3] = TOUCH.read(3);
        t_state[4] = TOUCH.read(4);
    }
}

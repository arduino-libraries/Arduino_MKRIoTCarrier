
#include <Arduino_IOTSK_Qtouch.h>


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

void IOTSKcarrier_Qtouch::updateConfig(int newSens, int newHyst){
    setSensivity(newSens);
    setHysteresis(newHyst);
}

//Manager
bool IOTSKcarrier_Qtouch_Manager::begin(){
    
   
    if (touch_sensors_init()){
        return(false);
    }

    touch_time.current_time_ms = 0;
    analogReadResolution(10);
   
}

IOTSKcarrier_Qtouch_Manager::IOTSKcarrier_Qtouch_Manager(){

}

void IOTSKcarrier_Qtouch_Manager::update(){
    
    touch_time.time_to_measure_touch = 1;
    touch_time.current_time_ms = touch_time.current_time_ms + millis();

    touch_sensors_measure(); 

    if ((p_selfcap_measure_data->measurement_done_touch == 1u)) {
        p_selfcap_measure_data->measurement_done_touch == 0u;

        t_state[0] = GET_SELFCAP_SENSOR_STATE(0);
        t_state[1] = GET_SELFCAP_SENSOR_STATE(1);
        t_state[2] = GET_SELFCAP_SENSOR_STATE(2);
        t_state[3] = GET_SELFCAP_SENSOR_STATE(3);
        t_state[4] = GET_SELFCAP_SENSOR_STATE(4);
        
        /*
        Serial.print("Botton 1 status: ");
        Serial.println(state1);
        Serial.print("Botton 3 status: ");
        Serial.println(state2);
        Serial.print("Botton 3 status: ");
        Serial.println(state3);
        Serial.print("Botton 4 status: ");
        Serial.println(state4);
        Serial.print("Botton 5 status: ");
        Serial.println(state5);
        Serial.println();
        */
    }

    rtcflag = false;

}
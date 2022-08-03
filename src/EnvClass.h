#ifndef _ENVCLASS_H_INCLUDED
#define _ENVCLASS_H_INCLUDED

#include <Arduino.h>
#include <MKRIoTCarrierDefines.h>


class EnvClass {
  public:
    EnvClass(int (*)(void));
    ~EnvClass();

    int begin();
    void end();

    float readTemperature(int units = CELSIUS);
    float readHumidity();

  private:
    HTS221Class* HTS221;
    //LSM6DS3Class& LSM6DS3 = IMU;
    //LSM6DSOXClass& LSM6DSOX = IMU;

  private:

    int (*board_revision)(void);
    int _revision;
};

#endif //_ENVCLASS_H_INCLUDED
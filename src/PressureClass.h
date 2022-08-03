#ifndef _PRESSURECLASS_H_INCLUDED
#define _PRESSURECLASS_H_INCLUDED

#include <Arduino.h>
#include <MKRIoTCarrierDefines.h>


class PressureClass {
  public:
    PressureClass(int (*)(void));
    ~PressureClass();

    int begin();
    void end();

    float readPressure(int units = KILOPASCAL);
    float readTemperature(void);

  private:
    LPS22HBClass* LPS22HB;
    //LSM6DS3Class& LSM6DS3 = IMU;
    //LSM6DSOXClass& LSM6DSOX = IMU;

  private:

    int (*board_revision)(void);
    int _revision;
};

#endif  //_PRESSURECLASS_H_INCLUDED
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

  protected:
    Bsec* iaqSensor;

  private:
    int checkIaqSensorStatus(void);

    HTS221Class* HTS221;

  private:

    int (*board_revision)(void);
    int _revision;
};

#endif //_ENVCLASS_H_INCLUDED
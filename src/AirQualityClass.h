#ifndef _AIRQUALITYCLASS_H_INCLUDED
#define _AIRQUALITYCLASS_H_INCLUDED

#include <Arduino.h>
#include <MKRIoTCarrierDefines.h>

class AirQualityClass {
  public:
    AirQualityClass(int (*)(void));
    ~AirQualityClass();

    int begin();
    void end();

    float readCO2();
    float readStaticIAQ();
    float readIAQAccuracy();
    float readIAQ();
    float readGasResistor();
    float readVOC();

  protected:
    Bsec* iaqSensor;

  private:
    // Helper functions declarations
    int checkIaqSensorStatus(void);

  private:

    int (*board_revision)(void);
    int _revision;
};

#endif  //_AIRQUALITYCLASS_H_INCLUDED
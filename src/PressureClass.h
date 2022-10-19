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
    float readTemperature(int units = CELSIUS);

  protected:
    Bsec* iaqSensor;

  private:
  // Helper functions declarations
    int checkIaqSensorStatus(void);

    LPS22HBClass* LPS22HB;


  private:

    int (*board_revision)(void);
    int _revision;
};

#endif  //_PRESSURECLASS_H_INCLUDED
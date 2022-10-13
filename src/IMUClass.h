#ifndef _IMUCLASS_H_INCLUDED
#define _IMUCLASS_H_INCLUDED

#include <Arduino.h>
#include <MKRIoTCarrierDefines.h>


class IMUClass {
  public:
    IMUClass(int (*)(void));
    ~IMUClass();

    int begin();
    void end();

    // Accelerometer
    int readAcceleration(float& x, float& y, float& z); // Results are in g (earth gravity).
    float accelerationSampleRate(); // Sampling rate of the sensor.
    int accelerationAvailable(); // Check for available data from accelerometer

    // Gyroscope
    int readGyroscope(float& x, float& y, float& z); // Results are in degrees/second.
    float gyroscopeSampleRate(); // Sampling rate of the sensor.
    int gyroscopeAvailable(); // Check for available data from gyroscope

    

  private:
    LSM6DSOXClass* LSM6DSOX;
    LSM6DS3Class* LSM6DS3;
  private:

    int (*board_revision)(void);
    int _revision;
};

#endif  //_IMUCLASS_H_INCLUDED